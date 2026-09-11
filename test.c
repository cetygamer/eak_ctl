#include <stdio.h>
#include <unistd.h>

#include "vcfg.h"

struct ConfigDataStruct vConfigData = { .AutoLeavinngMessageyCtr = 1 };

void Act_ExecuteTakeoff(void) { fprintf(stderr, "[test] Act_ExecuteTakeoff called\n"); }

void mqtt_connect(void) {
    fprintf(stderr, "[test] mqtt_connect\n");
}

int main(int argc, char *argv[]) {
    size_t count = 0;

    mqtt_connect();

    while (1) {
        count++;

        if (count % 30 == 0) {
            fprintf(stderr, "[test] Switching SlientState\n");
            vConfigData.SlientState = vConfigData.SlientState ? 0 : 1;
        }

        if (count % 30 == 15) {
            fprintf(stderr, "[test] Switching Autoguard.Enable\n");
            vConfigData.Autoguard.Enable = vConfigData.Autoguard.Enable ? 0 : 1;
        }

        usleep(1000000U);
    }

    return 0;
}
