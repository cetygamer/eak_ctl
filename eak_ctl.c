#include <ctype.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <netdb.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "mqtt.h"
#include "vcfg.h"

#define DEVICE_NAME                 "EAK Control Shim"
#define DEVICE_MANUFACTURER         "Tantos"
#define DEVICE_MODEL                "Neo HD SE Tuya"
#define DEVICE_FIRMWARE             "eak_ctl v1.0"

#define MQTT_DEVICE_NAME            "eak_ctl"

#define WILL_TOPIC                  MQTT_DEVICE_NAME "/status"
#define WILL_MESSAGE_OFFLINE        "offline"
#define WILL_MESSAGE_ONLINE         "online"

#define ENTITY_RO                   "\"stat_t\":\"~/state\","
#define ENTITY_WO                   "\"cmd_t\":\"~/set\","
#define ENTITY_RW                   ENTITY_RO ENTITY_WO

#define BUILD_ENTITY_TOPIC(cls, id) "homeassistant/" cls "/" MQTT_DEVICE_NAME "/" id
#define BUILD_ENTITY_CONFIG(cls, id, name, icon, extra)    \
    "{"                                                    \
    "\"~\":\""                                             \
    "homeassistant/" cls "/" MQTT_DEVICE_NAME "/" id "\"," \
    "\"name\":\"" name "\","                               \
    "\"obj_id\":\"" MQTT_DEVICE_NAME "_" id "\","          \
    "\"uniq_id\":\"" MQTT_DEVICE_NAME "_" id "\","         \
    "\"avty_t\":\"" WILL_TOPIC "\","                       \
    "\"ic\":\"" icon "\"," extra "\"dev\":{"               \
    "\"name\":\"" DEVICE_NAME "\","                        \
    "\"mf\":\"" DEVICE_MANUFACTURER "\","                  \
    "\"mdl\":\"" DEVICE_MODEL "\","                        \
    "\"sw\":\"" DEVICE_FIRMWARE "\","                      \
    "\"ids\":\"000000000000\""                             \
    "}"                                                    \
    "}"
// Hardcoded and tied to BUILD_ENTITY_CONFIG
#define ENTITY_CONFIG_IDS_ROFF 15

#define BUTTON_HANGUP_CLS      "button"
#define BUTTON_HANGUP_ID       "hangup"
#define BUTTON_HANGUP_NAME     "Сбросить вызов"
#define BUTTON_HANGUP_ICON     "mdi:phone-hangup"
#define BUTTON_HANGUP_TOPIC    BUILD_ENTITY_TOPIC(BUTTON_HANGUP_CLS, BUTTON_HANGUP_ID)
#define BUTTON_HANGUP_CONFIG \
    BUILD_ENTITY_CONFIG(BUTTON_HANGUP_CLS, BUTTON_HANGUP_ID, BUTTON_HANGUP_NAME, BUTTON_HANGUP_ICON, ENTITY_WO)

#define SWITCH_SILENT_CLS   "switch"
#define SWITCH_SILENT_ID    "silent"
#define SWITCH_SILENT_NAME  "Не беспокоить"
#define SWITCH_SILENT_ICON  "mdi:volume-off"
#define SWITCH_SILENT_TOPIC BUILD_ENTITY_TOPIC(SWITCH_SILENT_CLS, SWITCH_SILENT_ID)
#define SWITCH_SILENT_CONFIG \
    BUILD_ENTITY_CONFIG(SWITCH_SILENT_CLS, SWITCH_SILENT_ID, SWITCH_SILENT_NAME, SWITCH_SILENT_ICON, ENTITY_RW)

#define SWITCH_AUTOOPEN_CLS   "switch"
#define SWITCH_AUTOOPEN_ID    "autoopen"
#define SWITCH_AUTOOPEN_NAME  "Автоматическое открывание"
#define SWITCH_AUTOOPEN_ICON  "mdi:auto-mode"
#define SWITCH_AUTOOPEN_TOPIC BUILD_ENTITY_TOPIC(SWITCH_AUTOOPEN_CLS, SWITCH_AUTOOPEN_ID)
#define SWITCH_AUTOOPEN_CONFIG \
    BUILD_ENTITY_CONFIG(SWITCH_AUTOOPEN_CLS, SWITCH_AUTOOPEN_ID, SWITCH_AUTOOPEN_NAME, SWITCH_AUTOOPEN_ICON, ENTITY_RW)

#define NUMBER_OFFSET_CLS   "number"
#define NUMBER_OFFSET_ID    "offset"
#define NUMBER_OFFSET_NAME  "Смещение байта в конфиге"
#define NUMBER_OFFSET_ICON  "mdi:test-tube"
#define NUMBER_OFFSET_TOPIC BUILD_ENTITY_TOPIC(NUMBER_OFFSET_CLS, NUMBER_OFFSET_ID)
#define NUMBER_OFFSET_CONFIG                                                                         \
    BUILD_ENTITY_CONFIG(NUMBER_OFFSET_CLS, NUMBER_OFFSET_ID, NUMBER_OFFSET_NAME, NUMBER_OFFSET_ICON, \
                        ENTITY_RW "\"min\":0,\"max\":27291,\"ent_cat\":\"diagnostic\",")

#define NUMBER_VALUE_CLS   "number"
#define NUMBER_VALUE_ID    "value"
#define NUMBER_VALUE_NAME  "Значение байта в конфиге"
#define NUMBER_VALUE_ICON  "mdi:numeric"
#define NUMBER_VALUE_TOPIC BUILD_ENTITY_TOPIC(NUMBER_VALUE_CLS, NUMBER_VALUE_ID)
#define NUMBER_VALUE_CONFIG                                                                      \
    BUILD_ENTITY_CONFIG(NUMBER_VALUE_CLS, NUMBER_VALUE_ID, NUMBER_VALUE_NAME, NUMBER_VALUE_ICON, \
                        ENTITY_RW "\"min\":0,\"max\":255,\"ent_cat\":\"diagnostic\",")

static char                              device_id[12] = { '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' };
static volatile struct ConfigDataStruct *p_vConfigData = NULL;
static uint8_t                           SlientState   = 255;
static uint8_t                           AutoLeavinngMessageyCtr = 255;
static uint8_t                           AutoGuard_Enable        = 255;
static uint8_t                           AutoGuard_Type          = 255;
static uint8_t                           AutoGuard_PanelSelect   = 255;
static int                               prev_config_offset      = -1;
static int                               config_offset           = 0;
static volatile int                      config_value            = 0;

struct reconnect_state_t {
    char    *hostname;
    char    *port;
    char    *username;
    char    *password;
    uint8_t *sendbuf;
    size_t   sendbufsz;
    uint8_t *recvbuf;
    size_t   recvbufsz;
};

static int open_nb_socket(const char *addr, const char *port) {
    struct addrinfo hints = { 0 };

    hints.ai_family         = AF_UNSPEC;
    hints.ai_socktype       = SOCK_STREAM;
    int              sockfd = -1;
    int              rv;
    struct addrinfo *p, *servinfo;

    rv = getaddrinfo(addr, port, &hints, &servinfo);
    if (rv != 0) {
        fprintf(stderr, "[eak_ctl] Failed to open socket (getaddrinfo): %s\n", gai_strerror(rv));
        return -1;
    }

    for (p = servinfo; p != NULL; p = p->ai_next) {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1)
            continue;

        rv = connect(sockfd, p->ai_addr, p->ai_addrlen);
        if (rv == -1) {
            close(sockfd);
            sockfd = -1;
            continue;
        }
        break;
    }

    freeaddrinfo(servinfo);

    if (sockfd != -1)
        fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL) | O_NONBLOCK);

    return sockfd;
}

static void reconnect_client(struct mqtt_client *client, void **reconnect_state_vptr) {
    struct reconnect_state_t *reconnect_state = *((struct reconnect_state_t **) reconnect_state_vptr);

    if (client->error != MQTT_ERROR_INITIAL_RECONNECT)
        close(client->socketfd);

    int sockfd = open_nb_socket(reconnect_state->hostname, reconnect_state->port);
    if (sockfd == -1)
        return;

    mqtt_reinit(client, sockfd, reconnect_state->sendbuf, reconnect_state->sendbufsz, reconnect_state->recvbuf,
                reconnect_state->recvbufsz);

    mqtt_connect(client, NULL, WILL_TOPIC, WILL_MESSAGE_OFFLINE, sizeof(WILL_MESSAGE_OFFLINE) - 1,
                 reconnect_state->username, reconnect_state->password,
                 MQTT_CONNECT_CLEAN_SESSION | MQTT_CONNECT_WILL_QOS_0 | MQTT_CONNECT_WILL_RETAIN, 400);

    if (client->error != MQTT_OK) {
        fprintf(stderr, "[eak_ctl] Failed to connect: %s\n", mqtt_error_str(client->error));
        return;
    }

    char *config;

#define PUBLISH_SENSOR_CONFIG(entity)                                                           \
    do {                                                                                        \
        config = strdup(entity##_CONFIG);                                                       \
        if (!config)                                                                            \
            return;                                                                             \
        memcpy(config + strlen(config) - ENTITY_CONFIG_IDS_ROFF, device_id, sizeof(device_id)); \
        mqtt_publish(client, entity##_TOPIC "/config", config, strlen(config),                  \
                     MQTT_PUBLISH_QOS_0 | MQTT_PUBLISH_RETAIN);                                 \
        free(config);                                                                           \
    } while (0)
#define PUBLISH_CONTROL_CONFIG(entity)                    \
    do {                                                  \
        PUBLISH_SENSOR_CONFIG(entity);                    \
        mqtt_subscribe(client, entity##_TOPIC "/set", 0); \
    } while (0)

    PUBLISH_CONTROL_CONFIG(BUTTON_HANGUP);
    PUBLISH_CONTROL_CONFIG(SWITCH_SILENT);
    PUBLISH_CONTROL_CONFIG(SWITCH_AUTOOPEN);
    PUBLISH_CONTROL_CONFIG(NUMBER_OFFSET);
    PUBLISH_CONTROL_CONFIG(NUMBER_VALUE);

#undef PUBLISH_SENSOR_CONFIG
#undef PUBLISH_CONTROL_CONFIG

    mqtt_publish(client, WILL_TOPIC, WILL_MESSAGE_ONLINE, sizeof(WILL_MESSAGE_ONLINE) - 1,
                 MQTT_PUBLISH_QOS_0 | MQTT_PUBLISH_RETAIN);

    fprintf(stderr, "[eak_ctl] MQTT client connected\n");
}

static void *get_symbol(const char *name) { return dlsym(RTLD_DEFAULT, name); }

typedef void (*func_void_void_t)(void);

static void call_symbol_void_void(const char *name) {
    func_void_void_t func = get_symbol(name);

    if (!func) {
        fprintf(stderr, "[eak_ctl] Symbol not found: %s\n", name);
        return;
    }

    func();
}

static int strntoi(const char *str, size_t n) {
    const char *s    = str;
    int         sign = 1;
    int         i    = 0;

    while (((size_t) (s - str) < n) && isspace(*s))
        s++;

    if (((size_t) (s - str) < n) && (*s == '-' || *s == '+')) {
        if (*s == '-')
            sign = -1;
        s++;
    }

    while (((size_t) (s - str) < n) && isdigit(*s)) {
        i = 10 * i + (*s - '0');
        s++;
    }

    return sign * i;
}

static void publish_callback(void **state, struct mqtt_response_publish *published) {
    size_t len;

    // fprintf(stderr, "[eak_ctl] Received publish('%.*s'): %.*s\n", published->topic_name_size,
    //         (char *) published->topic_name, published->application_message_size,
    //         (char *) published->application_message);

#define IS_TOPIC(topic)                                              \
    (((len = strlen(topic "/set")) <= published->topic_name_size) && \
     (strncmp(topic "/set", published->topic_name, len) == 0))

    if (IS_TOPIC(BUTTON_HANGUP_TOPIC)) {
        fprintf(stderr, "[eak_ctl] Executing hang up\n");
        call_symbol_void_void("Act_ExecuteTakeoff");
    } else if (IS_TOPIC(SWITCH_SILENT_TOPIC)) {
        fprintf(stderr, "[eak_ctl] Setting silent = %.*s\n", published->application_message_size,
                (char *) published->application_message);
        p_vConfigData->SlientState =
                (published->application_message_size >= 2 && strncmp(published->application_message, "ON", 2) == 0) ? 1
                                                                                                                    : 0;
    } else if (IS_TOPIC(SWITCH_AUTOOPEN_TOPIC)) {
        fprintf(stderr, "[eak_ctl] Setting autoopen = %.*s\n", published->application_message_size,
                (char *) published->application_message);
        if (published->application_message_size >= 2 && strncmp(published->application_message, "ON", 2) == 0) {
            p_vConfigData->AutoLeavinngMessageyCtr = 1;
            p_vConfigData->Autoguard.Enable        = 1;
            p_vConfigData->Autoguard.Type          = 0;
            p_vConfigData->Autoguard.PanelSelect   = 0;
        } else {
            p_vConfigData->Autoguard.Enable = 0;
        }
    } else if (IS_TOPIC(NUMBER_OFFSET_TOPIC)) {
        config_offset = strntoi(published->application_message, published->application_message_size);
        if (config_offset >= 0 && config_offset < (ssize_t) sizeof(struct ConfigDataStruct)) {
            config_value = *((volatile char *) p_vConfigData + config_offset);
            fprintf(stderr, "[eak_ctl] Reading config at %d = %d\n", config_offset, config_value);
        } else {
            fprintf(stderr, "[eak_ctl] Malformed config read request: [%d]\n", config_offset);
        }
    } else if (IS_TOPIC(NUMBER_VALUE_TOPIC)) {
        config_value = strntoi(published->application_message, published->application_message_size);
        if (config_value >= 0 && config_value <= 255 && config_offset >= 0 &&
            config_offset < (ssize_t) sizeof(struct ConfigDataStruct)) {
            *((volatile char *) p_vConfigData + config_offset) = config_value;
            fprintf(stderr, "[eak_ctl] Writing config at %d = %d\n", config_offset, config_value);
        } else {
            fprintf(stderr, "[eak_ctl] Malformed config write request: [%d] = %d\n", config_offset, config_value);
        }
    }

#undef IS_TOPIC
}

static void *client_refresher(void *client) {
    while (1) {
        mqtt_sync((struct mqtt_client *) client);
        usleep(500000U);
    }
    return NULL;
}

static void *eak_ctl_main(void *arg) {
    char *disable_timer = getenv("EAK_CTL_DISABLE_TIMER");
    if (disable_timer == NULL || strcmp(disable_timer, "1") != 0) {
        sleep(120);
    }

    int fd = open("/sys/class/net/wlan0/address", O_RDONLY);

    if (fd >= 0) {
        char address[17];

        ssize_t off = 0;
        while (off < 17) {
            ssize_t n = read(fd, address + off, 17 - off);
            if (n <= 0)
                break;
            off += n;
        }

        if (off >= 17) {
            device_id[0]  = toupper(address[0]);
            device_id[1]  = toupper(address[1]);
            device_id[2]  = toupper(address[3]);
            device_id[3]  = toupper(address[4]);
            device_id[4]  = toupper(address[6]);
            device_id[5]  = toupper(address[7]);
            device_id[6]  = toupper(address[9]);
            device_id[7]  = toupper(address[10]);
            device_id[8]  = toupper(address[12]);
            device_id[9]  = toupper(address[13]);
            device_id[10] = toupper(address[15]);
            device_id[11] = toupper(address[16]);
        }

        close(fd);
    }

    struct reconnect_state_t reconnect_state;

    reconnect_state.hostname = getenv("EAK_CTL_MQTT_HOST");
    if (!reconnect_state.hostname)
        reconnect_state.hostname = "localhost";
    reconnect_state.port = getenv("EAK_CTL_MQTT_PORT");
    if (!reconnect_state.port)
        reconnect_state.port = "1883";
    reconnect_state.username = getenv("EAK_CTL_MQTT_USER");
    reconnect_state.password = getenv("EAK_CTL_MQTT_PASS");
    uint8_t sendbuf[8192];
    uint8_t recvbuf[8192];
    reconnect_state.sendbuf   = sendbuf;
    reconnect_state.sendbufsz = sizeof(sendbuf);
    reconnect_state.recvbuf   = recvbuf;
    reconnect_state.recvbufsz = sizeof(recvbuf);

    struct mqtt_client client;

    mqtt_init_reconnect(&client, reconnect_client, &reconnect_state, publish_callback);

    pthread_t client_daemon;
    pthread_create(&client_daemon, NULL, client_refresher, &client);

    while (1) {
        if (client.error == MQTT_OK) {
            if (p_vConfigData->SlientState != SlientState) {
                SlientState           = p_vConfigData->SlientState;
                const char *state_str = SlientState ? "ON" : "OFF";
                fprintf(stderr, "[eak_ctl] Publishing silent = %s\n", state_str);
                mqtt_publish(&client, SWITCH_SILENT_TOPIC "/state", state_str, strlen(state_str),
                             MQTT_PUBLISH_QOS_0 | MQTT_PUBLISH_RETAIN);
            }
            if (p_vConfigData->AutoLeavinngMessageyCtr != AutoLeavinngMessageyCtr ||
                p_vConfigData->Autoguard.Enable != AutoGuard_Enable ||
                p_vConfigData->Autoguard.Type != AutoGuard_Type ||
                p_vConfigData->Autoguard.PanelSelect != AutoGuard_PanelSelect) {
                AutoLeavinngMessageyCtr = p_vConfigData->AutoLeavinngMessageyCtr;
                AutoGuard_Enable        = p_vConfigData->Autoguard.Enable;
                AutoGuard_Type          = p_vConfigData->Autoguard.Type;
                AutoGuard_PanelSelect   = p_vConfigData->Autoguard.PanelSelect;
                const char *state_str = (AutoLeavinngMessageyCtr == 1 && AutoGuard_Enable == 1 && AutoGuard_Type == 0 &&
                                         AutoGuard_PanelSelect == 0)
                                                ? "ON"
                                                : "OFF";
                fprintf(stderr, "[eak_ctl] Publishing autoopen = %s\n", state_str);
                mqtt_publish(&client, SWITCH_AUTOOPEN_TOPIC "/state", state_str, strlen(state_str),
                             MQTT_PUBLISH_QOS_0 | MQTT_PUBLISH_RETAIN);
            }
            if (config_offset != prev_config_offset) {
                char state_str[12];
                snprintf(state_str, sizeof(state_str), "%d", config_offset);
                prev_config_offset = config_offset;
                fprintf(stderr, "[eak_ctl] Publishing offset = %s\n", state_str);
                mqtt_publish(&client, NUMBER_OFFSET_TOPIC "/state", state_str, strlen(state_str),
                             MQTT_PUBLISH_QOS_0 | MQTT_PUBLISH_RETAIN);
            }
            if (config_value >= 0) {
                char state_str[12];
                snprintf(state_str, sizeof(state_str), "%d", config_value);
                config_value = -1;
                fprintf(stderr, "[eak_ctl] Publishing value = %s\n", state_str);
                mqtt_publish(&client, NUMBER_VALUE_TOPIC "/state", state_str, strlen(state_str),
                             MQTT_PUBLISH_QOS_0 | MQTT_PUBLISH_RETAIN);
            }
        }

        usleep(500000U);
    }

    return NULL;
}

__attribute__((constructor)) static void eak_ctl_init(void) {
    if (!(p_vConfigData = get_symbol("vConfigData")))
        return;

    pthread_t t;
    pthread_create(&t, NULL, eak_ctl_main, NULL);
    pthread_detach(t);
    fprintf(stderr, "[eak_ctl] Control shim loaded\n");
}
