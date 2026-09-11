#ifndef VCFG_H
#define VCFG_H

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#pragma pack(push, 1)
struct RingPlanTypeStruct {
    uint8_t RingVolArray[4];

    struct {
        uint8_t  reserved0[4];
        uint32_t SetMinute;
        uint32_t SetHour;
        uint8_t  reserved1[32];
    } BeginTimeArray[4];
};

struct AlarmClockStruct {
    uint8_t Enable;
    uint8_t ClockType;
    uint8_t ClockWeekState;
    uint8_t reserved0;

    struct {
        uint8_t  reserved0[4];
        uint32_t SetMinute;
        uint32_t SetHour;
        uint32_t SetDay;
        uint32_t SetMonth;
        uint32_t SetYear;
        uint8_t  reserved1[20];
    } Time;

    uint8_t Volume;
    char    MusicName[128];
    uint8_t reserved1[3];
};

struct DVRTimeSettingStruct {
    uint8_t Enable;
    uint8_t DVRSourceForAnloag;
    uint8_t reserved0[2];

    struct {
        uint8_t  reserved0[4];
        uint32_t SetMinute;
        uint32_t SetHour;
        uint8_t  reserved1[32];
    } BeginTime;

    struct {
        uint8_t  reserved0[4];
        uint32_t SetMinute;
        uint32_t SetHour;
        uint8_t  reserved1[32];
    } EndTime;

    uint8_t reserved1[8];
};

struct ScreenTimeStruct {
    struct {
        uint8_t  reserved0[4];
        uint32_t SetMinute;
        uint32_t SetHour;
        uint8_t  reserved1[32];
    } BeginTime;

    struct {
        uint8_t  reserved0[4];
        uint32_t SetMinute;
        uint32_t SetHour;
        uint8_t  reserved1[32];
    } EndTime;
};

struct AutoguardStruct {
    uint8_t Enable;
    uint8_t Type;
    uint8_t reserved0[2];

    struct {
        uint8_t  reserved0[4];
        uint32_t SetMinute;
        uint32_t SetHour;
        uint8_t  reserved1[32];
    } BeginTime;

    struct {
        uint8_t  reserved0[4];
        uint32_t SetMinute;
        uint32_t SetHour;
        uint8_t  reserved1[32];
    } EndTime;

    uint8_t PanelSelect;
    uint8_t WeekState;
    uint8_t reserved1[2];
};

struct ConfigDataStruct {
    uint8_t reserved0[268];                           //     8         Язык ???
                                                      //    12 -   139 Язык (string, utf-8: "English", Русский)
                                                      //   140 -   147 Ярык Версия (string, utf-8: "V1.00", "V1.01")
    uint16_t Anlog_Unlock1_Time;                      //   268 -   269 Конфигурация устройства - Время открывания (enum: {"0.5 сек.": 500, "1 сек.": 1000, "2 сек.": 2000, "5 сек.": 3000, "10 сек.": 10000, "20 сек.": 20000, "25 сек.": 25000})
    uint16_t Anlog_Unlock2_Time;                      //   270 -   271 Конфигурация устройства - Время открывания ворот (enum: {"0.5 сек.": 500, "1 сек.": 1000, "2 сек.": 2000, "5 сек.": 3000, "10 сек.": 10000, "20 сек.": 20000, "25 сек.": 25000})
    uint8_t reserved1;                                //
    uint8_t Anlog_DeviceAddress;                      //   273         Конфигурация устройства - Адрес устройства (enum: {"Команата 1": 0, "Команата 2": 1, "Команата 3": 2, "Команата 4": 3})
    uint8_t reserved2;                                //
    uint8_t Anlog_Unlock2_Enable;                     //   275         Конфигурация устройства - Статус ворот (bool)
    uint8_t Anlog_Unlock2_Signal;                     //   276         Конфигурация устройства - Режим открывания ворот (enum: {"Открывание через монитор": 0, "Открывание через вызывную панель": 1})
    uint8_t reserved3;                                //
    uint8_t Anlog_RingBackVolume;                     //   278         Конфигурация устройства - Громкость мелодии вызова в вызывной панели (enum: {"Громкость мелодии вызова в вызывной панели 0%": 0, "Громкость мелодии вызова в вызывной панели 20%": 20, "Громкость мелодии вызова в вызывной панели 30%": 30, "Громкость мелодии вызова в вызывной панели 40%": 40, "Громкость мелодии вызова в вызывной панели 50%": 50, "Громкость мелодии вызова в вызывной панели 60%": 60, "Громкость мелодии вызова в вызывной панели 70%": 70, "Громкость мелодии вызова в вызывной панели 80%": 80, "Громкость мелодии вызова в вызывной панели 90%": 90, "Громкость мелодии вызова в вызывной панели 100%": 100})
    uint8_t reserved4[5];                             //
    uint8_t UnlockPromptTone;                         //   284         Конфигурация устройства - Сообщение об открывании двери (bool)
    uint8_t reserved5[516];                           //
    uint8_t RingToneRepeatEnable;                     //   801         Повторять мелодию вызова (bool)
    char Door1MusicName[128];                         //   802 -   929 Мелодия вызывной панели 1 (string)
    char Door2MusicName[128];                         //   930 -  1057 Мелодия вызывной панели 2 (string)
    char IntercomMusicName[128];                      //  1058 -  1185 Мелодия вызова интеркома (string)
    uint8_t reserved6;                                //
    uint8_t DoorRingTime;                             //  1187         Время вызова (enum: {"5С": 5, "10С": 10, "20С": 20, "30С": 30, "40С": 40, "50С": 50, "60С": 60})
    uint8_t reserved7;                                //
    uint8_t SlientState;                              //  1189         Не беспокоить (bool)
    uint8_t KeyboradIndicatorEnabe;                   //  1190         Индикатор (bool)
    uint8_t KeyboradIndicatorForUnReadInfi;           //  1191         Мигание при не просмотренных файлах (bool)
    uint8_t IconNameEnabe;                            //  1192         Имя значка (bool)
    uint8_t ScreensaversEnable;                       //  1193         Отображать дату и время в режиме ожидания - Статус (bool)
    uint8_t AutoLeavinngMessageyCtr;                  //  1194         Автоответчик (bool)
    uint8_t ActionTypeForRing;                        //  1195         Действие при вызове (enum: {"Нет действий": 0, "Сделать фото": 1, "Записать видео": 2, "Сделать фото и записать видео": 3})
    struct RingPlanTypeStruct DoorbellRingVolumePlan; //  1196         Громкость вызова для панели - Громкость вызова 1 (enum: {"Громкость вызова 0%": 0, "Громкость вызова 20%": 20, "Громкость вызова 30%": 30, "Громкость вызова 40%": 40, "Громкость вызова 50%": 50, "Громкость вызова 60%": 60, "Громкость вызова 70%": 70, "Громкость вызова 80%": 80, "Громкость вызова 90%": 90, "Громкость вызова 100%": 100})
                                                      //  1197         Громкость вызова для панели - Громкость вызова 2 (enum: {"Громкость вызова 0%": 0, "Громкость вызова 20%": 20, "Громкость вызова 30%": 30, "Громкость вызова 40%": 40, "Громкость вызова 50%": 50, "Громкость вызова 60%": 60, "Громкость вызова 70%": 70, "Громкость вызова 80%": 80, "Громкость вызова 90%": 90, "Громкость вызова 100%": 100})
                                                      //  1198         Громкость вызова для панели - Громкость вызова 3 (enum: {"Громкость вызова 0%": 0, "Громкость вызова 20%": 20, "Громкость вызова 30%": 30, "Громкость вызова 40%": 40, "Громкость вызова 50%": 50, "Громкость вызова 60%": 60, "Громкость вызова 70%": 70, "Громкость вызова 80%": 80, "Громкость вызова 90%": 90, "Громкость вызова 100%": 100})
                                                      //  1199         Громкость вызова для панели - Громкость вызова 4 (enum: {"Громкость вызова 0%": 0, "Громкость вызова 20%": 20, "Громкость вызова 30%": 30, "Громкость вызова 40%": 40, "Громкость вызова 50%": 50, "Громкость вызова 60%": 60, "Громкость вызова 70%": 70, "Громкость вызова 80%": 80, "Громкость вызова 90%": 90, "Громкость вызова 100%": 100})
                                                      //  1204         Громкость вызова для панели - Время начала 1 - Минуты (range: [0 .. 59])
                                                      //  1208         Громкость вызова для панели - Время начала 1 - Часы (range: [0 .. 23])
                                                      //  1248         Громкость вызова для панели - Время начала 2 - Минуты (range: [0 .. 59])
                                                      //  1252         Громкость вызова для панели - Время начала 2 - Часы (range: [0 .. 23])
                                                      //  1292         Громкость вызова для панели - Время начала 3 - Минуты (range: [0 .. 59])
                                                      //  1296         Громкость вызова для панели - Время начала 3 - Часы (range: [0 .. 23])
                                                      //  1336         Громкость вызова для панели - Время начала 4 - Минуты (range: [0 .. 59])
                                                      //  1340         Громкость вызова для панели - Время начала 4 - Часы (range: [0 .. 23])
    struct RingPlanTypeStruct IntercomRingVolumePlan; //  1376         Громкость вызова для интеркома - Громкость вызова 1 (enum: {"Громкость вызова 0%": 0, "Громкость вызова 20%": 20, "Громкость вызова 30%": 30, "Громкость вызова 40%": 40, "Громкость вызова 50%": 50, "Громкость вызова 60%": 60, "Громкость вызова 70%": 70, "Громкость вызова 80%": 80, "Громкость вызова 90%": 90, "Громкость вызова 100%": 100})
                                                      //  1377         Громкость вызова для интеркома - Громкость вызова 2 (enum: {"Громкость вызова 0%": 0, "Громкость вызова 20%": 20, "Громкость вызова 30%": 30, "Громкость вызова 40%": 40, "Громкость вызова 50%": 50, "Громкость вызова 60%": 60, "Громкость вызова 70%": 70, "Громкость вызова 80%": 80, "Громкость вызова 90%": 90, "Громкость вызова 100%": 100})
                                                      //  1378         Громкость вызова для интеркома - Громкость вызова 3 (enum: {"Громкость вызова 0%": 0, "Громкость вызова 20%": 20, "Громкость вызова 30%": 30, "Громкость вызова 40%": 40, "Громкость вызова 50%": 50, "Громкость вызова 60%": 60, "Громкость вызова 70%": 70, "Громкость вызова 80%": 80, "Громкость вызова 90%": 90, "Громкость вызова 100%": 100})
                                                      //  1379         Громкость вызова для интеркома - Громкость вызова 4 (enum: {"Громкость вызова 0%": 0, "Громкость вызова 20%": 20, "Громкость вызова 30%": 30, "Громкость вызова 40%": 40, "Громкость вызова 50%": 50, "Громкость вызова 60%": 60, "Громкость вызова 70%": 70, "Громкость вызова 80%": 80, "Громкость вызова 90%": 90, "Громкость вызова 100%": 100})
                                                      //  1384         Громкость вызова для интеркома - Время начала 1 - Минуты (range: [0 .. 59])
                                                      //  1388         Громкость вызова для интеркома - Время начала 1 - Часы (range: [0 .. 23])
                                                      //  1428         Громкость вызова для интеркома - Время начала 2 - Минуты (range: [0 .. 59])
                                                      //  1432         Громкость вызова для интеркома - Время начала 2 - Часы (range: [0 .. 23])
                                                      //  1472         Громкость вызова для интеркома - Время начала 3 - Минуты (range: [0 .. 59])
                                                      //  1476         Громкость вызова для интеркома - Время начала 3 - Часы (range: [0 .. 23])
                                                      //  1516         Громкость вызова для интеркома - Время начала 4 - Минуты (range: [0 .. 59])
                                                      //  1520         Громкость вызова для интеркома - Время начала 4 - Часы (range: [0 .. 23])
    uint8_t TFTBrightness;                            //  1556         Яркость - Яркость (enum: {"Ниже": 0, "Средне": 1, "Выше": 2})
    uint8_t TFTBrightnessForStandby;                  //  1557         Яркость - Яркость подсветки в режиме ожидания в течение дня(8:00-20:00) (enum: {"Ниже": 0, "Средне": 1, "Выше": 2})
    uint8_t NightTFTBrightnessForStandby;             //  1558         Яркость - Яркость подсветки в режиме ожидания ночью(20:00-8:00) (enum: {"Ниже" 0:, "Средне": 1, "Выше": 2})
    uint8_t reserved8[5];                             //
    struct AlarmClockStruct AlarmClock[6];            //  1564         Будильник - Будильник 1 - Статус (bool)
                                                      //  1565         Будильник - Будильник 1 - Типа будильника (enum: {"Будильник каждую неделю": 0, "Будульник каждый месяц": 1, "Будильник каждый год": 2, "Будильник однократно": 3})
                                                      //  1566         Будильник - Будильник 1 - По дням недели (bitmap: {"ВС": 0, "ПН": 1, "ВТ": 2, "СР": 3, "ЧТ": 4, "ПТ": 5, "СБ": 6})
                                                      //  1572         Будильник - Будильник 1 - Время - Минуты (range: [0 .. 59])
                                                      //  1576         Будильник - Будильник 1 - Время - Часы (range: [0 .. 23])
                                                      //  1580         Будильник - Будильник 1 - Время - День (range: [1 .. 31])
                                                      //  1584         Будильник - Будильник 1 - Время - Месяц (range: [1 .. 12])
                                                      //  1588         Будильник - Будильник 1 - Время - Год (range: [2000 .. 2200])
                                                      //  1612         Будильник - Будильник 1 - Громкость мелодии будильника (enum: {"Громкость мелодии будильника 0%": 0, "Громкость мелодии будильника 20%": 20, "Громкость мелодии будильника 30%": 30, "Громкость мелодии будильника 40%": 40, "Громкость мелодии будильника 50%": 50, "Громкость мелодии будильника 60%": 60, "Громкость мелодии будильника 70%": 70, "Громкость мелодии будильника 80%": 80, "Громкость мелодии будильника 90%": 90, "Громкость мелодии будильника 100%": 100})
                                                      //  1613 -  1637 Будильник - Будильник 1 - Мелодия будильника (string)
                                                      //  1744         Будильник - Будильник 2 - Статус (bool)
                                                      //  1745         Будильник - Будильник 2 - Типа будильника (enum: {"Будильник каждую неделю": 0, "Будульник каждый месяц": 1, "Будильник каждый год": 2, "Будильник однократно": 3})
                                                      //  1746         Будильник - Будильник 2 - По дням недели (bitmap: {"ВС": 0, "ПН": 1, "ВТ": 2, "СР": 3, "ЧТ": 4, "ПТ": 5, "СБ": 6})
                                                      //  1752         Будильник - Будильник 2 - Время - Минуты (range: [0 .. 59])
                                                      //  1756         Будильник - Будильник 2 - Время - Часы (range: [0 .. 23])
                                                      //  1760         Будильник - Будильник 2 - Время - День (range: [1 .. 31])
                                                      //  1764         Будильник - Будильник 2 - Время - Месяц (range: [1 .. 12])
                                                      //  1768         Будильник - Будильник 2 - Время - Год (range: [2000 .. 2200])
                                                      //  1792         Будильник - Будильник 2 - Громкость мелодии будильника (enum: {"Громкость мелодии будильника 0%": 0, "Громкость мелодии будильника 20%": 20, "Громкость мелодии будильника 30%": 30, "Громкость мелодии будильника 40%": 40, "Громкость мелодии будильника 50%": 50, "Громкость мелодии будильника 60%": 60, "Громкость мелодии будильника 70%": 70, "Громкость мелодии будильника 80%": 80, "Громкость мелодии будильника 90%": 90, "Громкость мелодии будильника 100%": 100})
                                                      //  1793 -  1817 Будильник - Будильник 2 - Мелодия будильника (string)
                                                      //  1924         Будильник - Будильник 3 - Статус (bool)
                                                      //  1925         Будильник - Будильник 3 - Типа будильника (enum: {"Будильник каждую неделю": 0, "Будульник каждый месяц": 1, "Будильник каждый год": 2, "Будильник однократно": 3})
                                                      //  1926         Будильник - Будильник 3 - По дням недели (bitmap: {"ВС": 0, "ПН": 1, "ВТ": 2, "СР": 3, "ЧТ": 4, "ПТ": 5, "СБ": 6})
                                                      //  1932         Будильник - Будильник 3 - Время - Минуты (range: [0 .. 59])
                                                      //  1936         Будильник - Будильник 3 - Время - Часы (range: [0 .. 23])
                                                      //  1940         Будильник - Будильник 3 - Время - День (range: [1 .. 31])
                                                      //  1944         Будильник - Будильник 3 - Время - Месяц (range: [1 .. 12])
                                                      //  1948         Будильник - Будильник 3 - Время - Год (range: [2000 .. 2200])
                                                      //  1972         Будильник - Будильник 3 - Громкость мелодии будильника (enum: {"Громкость мелодии будильника 0%": 0, "Громкость мелодии будильника 20%": 20, "Громкость мелодии будильника 30%": 30, "Громкость мелодии будильника 40%": 40, "Громкость мелодии будильника 50%": 50, "Громкость мелодии будильника 60%": 60, "Громкость мелодии будильника 70%": 70, "Громкость мелодии будильника 80%": 80, "Громкость мелодии будильника 90%": 90, "Громкость мелодии будильника 100%": 100})
                                                      //  1973 -  1997 Будильник - Будильник 3 - Мелодия будильника (string)
                                                      //  2104         Будильник - Будильник 4 - Статус (bool)
                                                      //  2105         Будильник - Будильник 4 - Типа будильника (enum: {"Будильник каждую неделю": 0, "Будульник каждый месяц": 1, "Будильник каждый год": 2, "Будильник однократно": 3})
                                                      //  2106         Будильник - Будильник 4 - По дням недели (bitmap: {"ВС": 0, "ПН": 1, "ВТ": 2, "СР": 3, "ЧТ": 4, "ПТ": 5, "СБ": 6})
                                                      //  2112         Будильник - Будильник 4 - Время - Минуты (range: [0 .. 59])
                                                      //  2116         Будильник - Будильник 4 - Время - Часы (range: [0 .. 23])
                                                      //  2120         Будильник - Будильник 4 - Время - День (range: [1 .. 31])
                                                      //  2124         Будильник - Будильник 4 - Время - Месяц (range: [1 .. 12])
                                                      //  2128         Будильник - Будильник 4 - Время - Год (range: [2000 .. 2200])
                                                      //  2152         Будильник - Будильник 4 - Громкость мелодии будильника (enum: {"Громкость мелодии будильника 0%": 0, "Громкость мелодии будильника 20%": 20, "Громкость мелодии будильника 30%": 30, "Громкость мелодии будильника 40%": 40, "Громкость мелодии будильника 50%": 50, "Громкость мелодии будильника 60%": 60, "Громкость мелодии будильника 70%": 70, "Громкость мелодии будильника 80%": 80, "Громкость мелодии будильника 90%": 90, "Громкость мелодии будильника 100%": 100})
                                                      //  2153 -  2177 Будильник - Будильник 4 - Мелодия будильника (string)
                                                      //  2284         Будильник - Будильник 5 - Статус (bool)
                                                      //  2285         Будильник - Будильник 5 - Типа будильника (enum: {"Будильник каждую неделю": 0, "Будульник каждый месяц": 1, "Будильник каждый год": 2, "Будильник однократно": 3})
                                                      //  2286         Будильник - Будильник 5 - По дням недели (bitmap: {"ВС": 0, "ПН": 1, "ВТ": 2, "СР": 3, "ЧТ": 4, "ПТ": 5, "СБ": 6})
                                                      //  2292         Будильник - Будильник 5 - Время - Минуты (range: [0 .. 59])
                                                      //  2296         Будильник - Будильник 5 - Время - Часы (range: [0 .. 23])
                                                      //  2300         Будильник - Будильник 5 - Время - День (range: [1 .. 31])
                                                      //  2304         Будильник - Будильник 5 - Время - Месяц (range: [1 .. 12])
                                                      //  2308         Будильник - Будильник 5 - Время - Год (range: [2000 .. 2200])
                                                      //  2332         Будильник - Будильник 5 - Громкость мелодии будильника (enum: {"Громкость мелодии будильника 0%": 0, "Громкость мелодии будильника 20%": 20, "Громкость мелодии будильника 30%": 30, "Громкость мелодии будильника 40%": 40, "Громкость мелодии будильника 50%": 50, "Громкость мелодии будильника 60%": 60, "Громкость мелодии будильника 70%": 70, "Громкость мелодии будильника 80%": 80, "Громкость мелодии будильника 90%": 90, "Громкость мелодии будильника 100%": 100})
                                                      //  2333 -  2357 Будильник - Будильник 5 - Мелодия будильника (string)
                                                      //  2464         Будильник - Будильник 6 - Статус (bool)
                                                      //  2465         Будильник - Будильник 6 - Типа будильника (enum: {"Будильник каждую неделю": 0, "Будульник каждый месяц": 1, "Будильник каждый год": 2, "Будильник однократно": 3})
                                                      //  2466         Будильник - Будильник 6 - По дням недели (bitmap: {"ВС": 0, "ПН": 1, "ВТ": 2, "СР": 3, "ЧТ": 4, "ПТ": 5, "СБ": 6})
                                                      //  2472         Будильник - Будильник 6 - Время - Минуты (range: [0 .. 59])
                                                      //  2476         Будильник - Будильник 6 - Время - Часы (range: [0 .. 23])
                                                      //  2480         Будильник - Будильник 6 - Время - День (range: [1 .. 31])
                                                      //  2484         Будильник - Будильник 6 - Время - Месяц (range: [1 .. 12])
                                                      //  2488         Будильник - Будильник 6 - Время - Год (range: [2000 .. 2200])
                                                      //  2512         Будильник - Будильник 6 - Громкость мелодии будильника (enum: {"Громкость мелодии будильника 0%": 0, "Громкость мелодии будильника 20%": 20, "Громкость мелодии будильника 30%": 30, "Громкость мелодии будильника 40%": 40, "Громкость мелодии будильника 50%": 50, "Громкость мелодии будильника 60%": 60, "Громкость мелодии будильника 70%": 70, "Громкость мелодии будильника 80%": 80, "Громкость мелодии будильника 90%": 90, "Громкость мелодии будильника 100%": 100})
                                                      //  2513 -  2537 Будильник - Будильник 6 - Мелодия будильника (string)
    uint8_t ProtectionMode;                           //  2644         Защита паролем - Режим защиты (enum: {"Без защиты": 0, "Частичная защита": 1, "Полная защита": 2})
    uint8_t reserved9[3];                             //
    uint32_t SystemPassword;                          //  2648 -  2651 Защита паролем - Установка пароля (int)
    uint8_t reserved10[20480];                        //
    uint8_t DVRScreensaversTime;                      // 23132         Настройка DVR - Время выключения дисплея (enum: {"1 минута": 1, "2 минуты": 2, "5 минут": 5, "10 минут": 10, "30 минут": 30})
    uint8_t MotionDetectionMode;                      // 23133         Настройка DVR - Обнаружение движения (enum: {"Нет детекции движения": 0, "Низкая чувствительность": 1, "Средняя чувствительность": 2, "Высокая чувствительность": 3})
    uint8_t DVRTrigerLevel;                           // 23134         Тип внешнего датчика (enum: {"Нормально откр.": 0, "Нормально закр.": 1})
    uint8_t DVRActionItem;                            // 23135         Действие при детекции (enum: {"Записать видео": 0, "Сделать фото": 1})
    uint8_t TurnOnTFTWhenDetectMotion;                // 23136         Вкл. экрана при детекции (bool)
    uint8_t TurnOnTFTWhenSensorTriger;                // 23137         Вкл. экрана по внешнему датчику (bool)
    uint8_t reserved11[2];                            //
    struct DVRTimeSettingStruct DVRInf[3];            // 23140         Настройка DVR - Настройка интервалов - Настройка интервалов 1 - Статус (bool)
                                                      // 23141         Настройка DVR - Настройка интервалов - Настройка интервалов 1 - Источник записи (enum: {"Панель 1": 0, "Панель 2": 1, "Камера 1": 2, "Камера 2": 3})
                                                      // 23148         Настройка DVR - Настройка интервалов - Настройка интервалов 1 - Время начала - Минуты (range: [0 .. 59])
                                                      // 23152         Настройка DVR - Настройка интервалов - Настройка интервалов 1 - Время начала - Часы (range: [0 .. 23])
                                                      // 23192         Настройка DVR - Настройка интервалов - Настройка интервалов 1 - Время конца - Минуты (range: [0 .. 59])
                                                      // 23196         Настройка DVR - Настройка интервалов - Настройка интервалов 1 - Время конца - Часы (range: [0 .. 23])
                                                      // 23240         Настройка DVR - Настройка интервалов - Настройка интервалов 2 - Статус (bool)
                                                      // 23241         Настройка DVR - Настройка интервалов - Настройка интервалов 2 - Источник записи (enum: {"Панель 1": 0, "Панель 2": 1, "Камера 1": 2, "Камера 2": 3})
                                                      // 23248         Настройка DVR - Настройка интервалов - Настройка интервалов 2 - Время начала - Минуты (range: [0 .. 59])
                                                      // 23252         Настройка DVR - Настройка интервалов - Настройка интервалов 2 - Время начала - Часы (range: [0 .. 23])
                                                      // 23292         Настройка DVR - Настройка интервалов - Настройка интервалов 2 - Время конца - Минуты (range: [0 .. 59])
                                                      // 23296         Настройка DVR - Настройка интервалов - Настройка интервалов 2 - Время конца - Часы (range: [0 .. 23])
                                                      // 23340         Настройка DVR - Настройка интервалов - Настройка интервалов 3 - Статус (bool)
                                                      // 23341         Настройка DVR - Настройка интервалов - Настройка интервалов 3 - Источник записи (enum: {"Панель 1": 0, "Панель 2": 1, "Камера 1": 2, "Камера 2": 3})
                                                      // 23348         Настройка DVR - Настройка интервалов - Настройка интервалов 3 - Время начала - Минуты (range: [0 .. 59])
                                                      // 23352         Настройка DVR - Настройка интервалов - Настройка интервалов 3 - Время начала - Часы (range: [0 .. 23])
                                                      // 23392         Настройка DVR - Настройка интервалов - Настройка интервалов 3 - Время конца - Минуты (range: [0 .. 59])
                                                      // 23396         Настройка DVR - Настройка интервалов - Настройка интервалов 3 - Время конца - Часы (range: [0 .. 23])
    uint8_t reserved12[3444];                         //
    uint8_t MainMenuButtonEnable[32];                 // 26884         Конфигурация устройства - Настройка главного меню (bool array: {0: "Просмотр", 1: "Фото", 2: "Видео", 3: "Мультимедиа", 4: "Не беспокоить", 5: "Календарь", 6: "Аудио", 7: "DVR", 8: "Запись", 9: "Вызов", 10: "Память", 11: "Настройки", "12": "Автовахтер"})
    uint8_t reserved13[50];                           //
    uint8_t StandbyWallpaperEnable;                   // 26966         Отображать обои в режиме ожидания (bool)
    uint8_t DoorDelayTrigger;                         // 26967         Задержка звонка в интеркоме (enum: {"Выключено": 0, "5С": 5, "15С": 15])
    uint8_t TurnOffSreenDrv;                          // 26968         Настройка DVR - Не включать экран при старте DVR (bool)
    uint8_t PreRecordingEnable;                       // 26969         Настройка DVR - Предзапись (bool)
    uint8_t reserved14[2];                            //
    struct ScreenTimeStruct ScreenTime;               // 26976         Отображать дату и время в режиме ожидания - Время начала - Минуты (range: [0 .. 59])
                                                      // 26980         Отображать дату и время в режиме ожидания - Время начала - Часы (range: [0 .. 23])
                                                      // 27020         Отображать дату и время в режиме ожидания - Время конца - Минуты (range: [0 .. 59])
                                                      // 27024         Отображать дату и время в режиме ожидания - Время конца - Часы (range: [0 .. 23])
    uint8_t VoiceMessageCtr;                          // 27060         Голосовое сообщение (bool)
    uint8_t reserved15[3];                            //
    struct AutoguardStruct Autoguard;                 // 27064         Автоматическое открывание - Статус (bool)
                                                      // 27065         Автоматическое открывание - Тип автоматического открывания (enum: {"Один раз": 0, "По дням недели": 1})
                                                      // 27072         Автоматическое открывание - Время начала - Минуты (range: [0 .. 59])
                                                      // 27076         Автоматическое открывание - Время начала - Часы (range: [0 .. 23])
                                                      // 27116         Автоматическое открывание - Время конца - Минуты (range: [0 .. 59])
                                                      // 27120         Автоматическое открывание - Время конца - Часы (range: [0 .. 23])
                                                      // 27156         Автоматическое открывание - Выбор вызывной панели (enum: {"Панель 1": 0, "Панель 2": 1, "Обе": 2})
                                                      // 27157         Автоматическое открывание - По дням недели (bitmap: {"ВС": 0, "ПН": 1, "ВТ": 2, "СР": 3, "ЧТ": 4, "ПТ": 5, "СБ": 6})
    uint8_t reserved16[132];                          // 27160 - 27171 Wi-Fi точка доступа
};
#pragma pack(pop)

// uint8_t WifiState;         // Wi-Fi - Wi-Fi (bool)
// uint8_t AutoTimeCorrect;   // Wi-Fi - Автоматическая синхронизация времени (bool)
// uint8_t WeatherEnable;     // Wi-Fi - Виджет погоды (bool)
// uint8_t WifeDivertMode;    // Wi-Fi - Переадресация (enum: {"Нет переадресации": , "Немедленая переадресация": , "Переадресация при не ответе 5 сек.": , "Переадресация при не ответе 10 сек.": , "Переадресация при не ответе 20 сек.": , "Переадресация при не ответе 30 сек.": })
// uint8_t PushPicturesState; // Wi-Fi - Отправлять фото при обнаружении движения (bool)

_Static_assert(sizeof(struct ConfigDataStruct) == 27292, "Wrong size");

_Static_assert(offsetof(struct ConfigDataStruct, Anlog_Unlock1_Time) == 268, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, Anlog_Unlock2_Time) == 270, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, Anlog_DeviceAddress) == 273, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, Anlog_Unlock2_Enable) == 275, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, Anlog_Unlock2_Signal) == 276, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, Anlog_RingBackVolume) == 278, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, UnlockPromptTone) == 284, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, RingToneRepeatEnable) == 801, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, Door1MusicName) == 802, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, Door2MusicName) == 930, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, IntercomMusicName) == 1058, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DoorRingTime) == 1187, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, SlientState) == 1189, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, KeyboradIndicatorEnabe) == 1190, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, KeyboradIndicatorForUnReadInfi) == 1191, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, IconNameEnabe) == 1192, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, ScreensaversEnable) == 1193, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AutoLeavinngMessageyCtr) == 1194, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, ActionTypeForRing) == 1195, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DoorbellRingVolumePlan.RingVolArray[0]) == 1196, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DoorbellRingVolumePlan.RingVolArray[1]) == 1197, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DoorbellRingVolumePlan.RingVolArray[2]) == 1198, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DoorbellRingVolumePlan.RingVolArray[3]) == 1199, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DoorbellRingVolumePlan.BeginTimeArray[0].SetMinute) == 1204, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DoorbellRingVolumePlan.BeginTimeArray[0].SetHour) == 1208, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DoorbellRingVolumePlan.BeginTimeArray[1].SetMinute) == 1248, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DoorbellRingVolumePlan.BeginTimeArray[1].SetHour) == 1252, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DoorbellRingVolumePlan.BeginTimeArray[2].SetMinute) == 1292, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DoorbellRingVolumePlan.BeginTimeArray[2].SetHour) == 1296, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DoorbellRingVolumePlan.BeginTimeArray[3].SetMinute) == 1336, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DoorbellRingVolumePlan.BeginTimeArray[3].SetHour) == 1340, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, IntercomRingVolumePlan.RingVolArray[0]) == 1376, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, IntercomRingVolumePlan.RingVolArray[1]) == 1377, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, IntercomRingVolumePlan.RingVolArray[2]) == 1378, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, IntercomRingVolumePlan.RingVolArray[3]) == 1379, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, IntercomRingVolumePlan.BeginTimeArray[0].SetMinute) == 1384, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, IntercomRingVolumePlan.BeginTimeArray[0].SetHour) == 1388, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, IntercomRingVolumePlan.BeginTimeArray[1].SetMinute) == 1428, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, IntercomRingVolumePlan.BeginTimeArray[1].SetHour) == 1432, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, IntercomRingVolumePlan.BeginTimeArray[2].SetMinute) == 1472, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, IntercomRingVolumePlan.BeginTimeArray[2].SetHour) == 1476, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, IntercomRingVolumePlan.BeginTimeArray[3].SetMinute) == 1516, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, IntercomRingVolumePlan.BeginTimeArray[3].SetHour) == 1520, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, TFTBrightness) == 1556, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, TFTBrightnessForStandby) == 1557, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, NightTFTBrightnessForStandby) == 1558, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[0].Enable) == 1564, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[0].ClockType) == 1565, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[0].ClockWeekState) == 1566, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[0].Time.SetMinute) == 1572, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[0].Time.SetHour) == 1576, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[0].Time.SetDay) == 1580, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[0].Time.SetMonth) == 1584, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[0].Time.SetYear) == 1588, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[0].Volume) == 1612, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[0].MusicName) == 1613, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[1].Enable) == 1744, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[1].ClockType) == 1745, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[1].ClockWeekState) == 1746, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[1].Time.SetMinute) == 1752, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[1].Time.SetHour) == 1756, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[1].Time.SetDay) == 1760, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[1].Time.SetMonth) == 1764, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[1].Time.SetYear) == 1768, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[1].Volume) == 1792, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[1].MusicName) == 1793, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[2].Enable) == 1924, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[2].ClockType) == 1925, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[2].ClockWeekState) == 1926, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[2].Time.SetMinute) == 1932, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[2].Time.SetHour) == 1936, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[2].Time.SetDay) == 1940, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[2].Time.SetMonth) == 1944, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[2].Time.SetYear) == 1948, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[2].Volume) == 1972, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[2].MusicName) == 1973, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[3].Enable) == 2104, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[3].ClockType) == 2105, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[3].ClockWeekState) == 2106, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[3].Time.SetMinute) == 2112, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[3].Time.SetHour) == 2116, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[3].Time.SetDay) == 2120, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[3].Time.SetMonth) == 2124, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[3].Time.SetYear) == 2128, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[3].Volume) == 2152, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[3].MusicName) == 2153, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[4].Enable) == 2284, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[4].ClockType) == 2285, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[4].ClockWeekState) == 2286, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[4].Time.SetMinute) == 2292, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[4].Time.SetHour) == 2296, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[4].Time.SetDay) == 2300, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[4].Time.SetMonth) == 2304, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[4].Time.SetYear) == 2308, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[4].Volume) == 2332, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[4].MusicName) == 2333, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[5].Enable) == 2464, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[5].ClockType) == 2465, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[5].ClockWeekState) == 2466, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[5].Time.SetMinute) == 2472, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[5].Time.SetHour) == 2476, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[5].Time.SetDay) == 2480, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[5].Time.SetMonth) == 2484, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[5].Time.SetYear) == 2488, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[5].Volume) == 2512, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, AlarmClock[5].MusicName) == 2513, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, ProtectionMode) == 2644, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, SystemPassword) == 2648, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRScreensaversTime) == 23132, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, MotionDetectionMode) == 23133, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRTrigerLevel) == 23134, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRActionItem) == 23135, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, TurnOnTFTWhenDetectMotion) == 23136, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, TurnOnTFTWhenSensorTriger) == 23137, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRInf[0].Enable) == 23140, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRInf[0].DVRSourceForAnloag) == 23141, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRInf[0].BeginTime.SetMinute) == 23148, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRInf[0].BeginTime.SetHour) == 23152, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRInf[0].EndTime.SetMinute) == 23192, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRInf[0].EndTime.SetHour) == 23196, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRInf[1].Enable) == 23240, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRInf[1].DVRSourceForAnloag) == 23241, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRInf[1].BeginTime.SetMinute) == 23248, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRInf[1].BeginTime.SetHour) == 23252, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRInf[1].EndTime.SetMinute) == 23292, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRInf[1].EndTime.SetHour) == 23296, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRInf[2].Enable) == 23340, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRInf[2].DVRSourceForAnloag) == 23341, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRInf[2].BeginTime.SetMinute) == 23348, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRInf[2].BeginTime.SetHour) == 23352, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRInf[2].EndTime.SetMinute) == 23392, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DVRInf[2].EndTime.SetHour) == 23396, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, MainMenuButtonEnable) == 26884, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, StandbyWallpaperEnable) == 26966, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, DoorDelayTrigger) == 26967, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, TurnOffSreenDrv) == 26968, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, PreRecordingEnable) == 26969, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, ScreenTime.BeginTime.SetMinute) == 26976, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, ScreenTime.BeginTime.SetHour) == 26980, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, ScreenTime.EndTime.SetMinute) == 27020, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, ScreenTime.EndTime.SetHour) == 27024, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, VoiceMessageCtr) == 27060, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, Autoguard.Enable) == 27064, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, Autoguard.Type) == 27065, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, Autoguard.BeginTime.SetMinute) == 27072, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, Autoguard.BeginTime.SetHour) == 27076, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, Autoguard.EndTime.SetMinute) == 27116, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, Autoguard.EndTime.SetHour) == 27120, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, Autoguard.PanelSelect) == 27156, "Wrong field offset");
_Static_assert(offsetof(struct ConfigDataStruct, Autoguard.WeekState) == 27157, "Wrong field offset");

#endif
