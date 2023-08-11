/*
  В "Инструменты -> Управлять библиотеками..." необходимо предварительно установить последние версии библиотек:
  GyverPortal
  GyverNTP
  EEManager

  Подключение к часам производится по шине I2C, так-же необходимо отключить внутреннюю подтяжку шины в часах, а внешнюю подтяжку подключить к 3.3в(подтяжка на шине должна быть строго только в одном месте!)
*/
#include "config.h"

#include <GyverPortal.h>
GyverPortal ui;

#include <GyverNTP.h>
GyverNTP ntp(DEFAULT_GMT, 3600);
// список серверов, если "pool.ntp.org" не работает
//"ntp1.stratum2.ru"
//"ntp2.stratum2.ru"
//"ntp.msk-ix.ru"

struct settingsData {
  int8_t ntpGMT;
  char ssid[20];
  char pass[20];
} settings;

#include <EEManager.h>
EEManager memory(settings);

//переменные
GPdate mainDate;
GPtime mainTime;
GPtime alarmTime;

#include "WIRE.h"
#include "CLOCKBUS.h"

String tempSensList[] = {"DS3231", "SHT20/SHT21/SHT25/SHT30/SHT31/SHT35", "BMP180/BMP085/BMP280/BME280", "DHT11/DHT12/MW33", "DHT21/DHT22(AM2301/AM2302)", "DS18B20/DS18S20/DS1820"};

void build() {
  GP.BUILD_BEGIN(GP_DARK);
  GP.ONLINE_CHECK(); // проверять статус платы

  if (deviceInformation[HARDWARE_VERSION] != HW_VERSION) GP.SPAN("Внимание! Эта версия прошивки не может взаимодействовать с этим устройством!", GP_CENTER, "", "#07b379");
  else {
    GP.UI_MENU("Nixie clock", GP_RED);   // начать меню

    // ссылки меню
    GP.UI_LINK("/", "Основная");
    GP.UI_LINK("/settings", "Настройки");
    if (deviceInformation[RADIO_ENABLE]) GP.UI_LINK("/radio", "Радио");
    GP.UI_LINK("/system_information", "О системе");
    GP.UI_LINK("/update", "Обновление");
    GP.UI_LINK("/network", "Сетевые настройки");

    // кастомный контент
    GP.HR(GP_GRAY);
    if (deviceInformation[LAMP_NUM]) {
      GP.LABEL_BLOCK("Firmware: " + String(deviceInformation[FIRMWARE_VERSION_1]) + "." + String(deviceInformation[FIRMWARE_VERSION_2]) + "." + String(deviceInformation[FIRMWARE_VERSION_3]), "", GP_CYAN_B, 0, 1);
      GP.BREAK();
      GP.LABEL_BLOCK("Clock online", "", GP_GREEN_B, 0, 1);
    }
    else {
      GP.LABEL_BLOCK("Clock offline", "", GP_RED_B, 0, 1);
    }
    GP.BREAK();
    GP.HR(GP_GRAY);

    String backlModeList;

    backlModeList += "Выключена";
    if (deviceInformation[BACKL_TYPE]) {
      backlModeList += ',';
      backlModeList += "Статичная,Дыхание";
    }
    if (deviceInformation[BACKL_TYPE] >= 3) {
      backlModeList += ',';
      backlModeList += "Дыхание со сменой цвета при затухании,Бегущий огонь,Бегущий огонь со сменой цвета,Бегущий огонь с радугой,Бегущий огонь с конфетти,Волна,Волна со сменой цвета,Волна с радугой,Волна с конфетти,Плавная смена цвета,Радуга,Конфетти";
    }

    String dotModeList;

    dotModeList += "Выключены,";
    dotModeList += "Статичные";
    if (deviceInformation[NEON_DOT] != 3) {
      dotModeList += ',';
      dotModeList += "Динамичные(плавно мигают)";
    }
    if (deviceInformation[NEON_DOT] == 2) {
      dotModeList += ',';
      dotModeList += "Маятник(неонки)";
    }
    if (deviceInformation[DOTS_PORT_ENABLE]) {
      dotModeList += ',';
      dotModeList += "Мигающие,";
      dotModeList += "Бегущие,";
      dotModeList += "Змейка,";
      dotModeList += "Резинка";
      if ((deviceInformation[DOTS_NUM] > 4) || (deviceInformation[DOTS_TYPE] == 2)) {
        dotModeList += ',';
        dotModeList += "Одинарный маятник";
      }
      if ((deviceInformation[DOTS_NUM] > 4) && (deviceInformation[DOTS_TYPE] == 2)) {
        dotModeList += ',';
        dotModeList += "Двойной маятник";
      }
    }

    // ОБНОВЛЕНИЯ
    String updateList;

    updateList += "barTime";
    updateList += ',';
    updateList += "barTemp";
    if (sens.hum) {
      updateList += ',';
      updateList += "barHum";
    }
    if (sens.press) {
      updateList += ',';
      updateList += "barPress";
    }
    updateList += ',';

    GP.UI_BODY(); // начать основное окно
    GP.GRID_RESPONSIVE(600); // позволяет "отключить" таблицу при ширине экрана меньше 600px

    M_TABLE(
      "",
      GP_ALS(GP_LEFT, GP_RIGHT),
      M_TR(GP.LABEL(" "); GP.LABEL(" "); GP.LABEL_BLOCK(ui.getSystemTime().encode(), "barTime", GP_WHITE, 18, 1););
      M_TD(
        GP.LABEL_BLOCK(String((sens.temp + mainSettings.tempCorrect) / 10.0, 1) + "°С", "barTemp", GP_GREEN, 18, 1);
        if (sens.hum) GP.LABEL_BLOCK(String(sens.hum) + "%", "barHum", GP_BLUE, 18, 1);
        if (sens.press) GP.LABEL_BLOCK(String(sens.press) + "mm.Hg", "barPress", GP_PINK, 18, 1);
          GP.LABEL(" ");
          GP.LABEL(" ");
        );
      );
    GP.HR(GP_GRAY);

    if (ui.uri("/")) { //Основная страница
      M_GRID(
        M_BLOCK_TAB(
          "Настройка время",
          M_BOX(GP.LABEL("Время"); GP.TIME("time"););
          M_BOX(GP.LABEL("Дата"); GP.DATE("date"););
          M_BOX(GP_JUSTIFY, GP.LABEL("Формат");  M_BOX(GP_RIGHT, GP.LABEL("24ч");  GP.SWITCH("mainTimeFormat", mainSettings.timeFormat); GP.LABEL("12ч");););
          GP.HR();
          M_BOX(GP.LABEL("Часовой пояс"); GP.SELECT("syncGmt", "GMT-12,GMT-11,GMT-10,GMT-9,GMT-8,GMT-7,GMT-6,GMT-5,GMT-4,GMT-3,GMT-2,GMT-1,GMT+0,GMT+1,GMT+2,GMT+3,GMT+4,GMT+5,GMT+6,GMT+7,GMT+8,GMT+9,GMT+10,GMT+11,GMT+12", settings.ntpGMT + 12, 0, (boolean)(WiFi.status() != WL_CONNECTED)););
          GP.BUTTON("syncTime", (WiFi.status() != WL_CONNECTED) ? "Время с устройства" : "Синхронизация с сервером");
        );
        M_BLOCK_TAB(
          "Эффекты",
          M_BOX(GP_JUSTIFY, GP.LABEL("Глюки"); M_BOX(GP_RIGHT, GP.SWITCH("mainGlitch", mainSettings.glitchMode);););
          M_BOX(GP.LABEL("Разделители"); GP.SELECT("fastDot", dotModeList, fastSettings.dotMode););
          M_BOX(GP.LABEL("Минуты"); GP.SELECT("fastFlip", "Без анимации,Случайная смена эффектов,Плавное угасание и появление,Перемотка по порядку числа,Перемотка по порядку катодов в лампе,Поезд,Резинка,Ворота,Волна,Блики,Испарение,Игровой автомат", fastSettings.flipMode););
          M_BOX(GP.LABEL("Секунды"); GP.SELECT("mainSecsFlip", "Без анимации,Плавное угасание и появление,Перемотка по порядку числа,Перемотка по порядку катодов в лампе", mainSettings.secsMode, 0, (boolean)(deviceInformation[LAMP_NUM] < 6)););
          GP.HR();
          M_BOX(GP.LABEL("Подсветка"); GP.SELECT("fastBackl", backlModeList, fastSettings.backlMode, 0, (boolean)!deviceInformation[BACKL_TYPE]););
          M_BOX(GP.LABEL("Цвет"); M_BOX(GP_RIGHT, GP.SLIDER_C("fastColor", (fastSettings.backlColor != 255) ? ((fastSettings.backlColor / 10) + 1) : 0, 0, 26, 1, 0, GP_GREEN, (boolean)!deviceInformation[BACKL_TYPE]); ); );
        );
      );

      if (deviceInformation[ALARM_TYPE]) {
        updateList += "alarmDisable";
        updateList += ',';
        updateList += "alarmVol";
        updateList += ',';
        updateList += "alarmSoundType";
        updateList += ',';
        updateList += "alarmSound";
        updateList += ',';
        updateList += "alarmRadio";
        updateList += ',';
        updateList += "alarmTime";
        updateList += ',';
        updateList += "alarmMode";
        updateList += ',';
        for (uint8_t i = 1; i < 8; i++) {
          updateList += String("alarmDay/") + i;
          updateList += ',';
        }

        String alarmSoundList;
        for (uint8_t i = 0; i < deviceInformation[PLAYER_MAX_SOUND]; i++) {
          if (i) alarmSoundList += ',';
          alarmSoundList += String("№") + (i + 1);
        }

        String alarmRadioList;
        if (deviceInformation[RADIO_ENABLE]) {
          for (uint8_t i = 0; i < 10; i++) {
            if (i) alarmRadioList += ',';
            alarmRadioList += String("CH") + i + String(" ") + String(radioSettings.stationsSave[i] / 10.0, 1);
          }
        }
        else alarmRadioList += "пусто";

        String alarmNumList;
        for (uint8_t i = 0; i < alarm.all ; i++) {
          if (i) alarmNumList += ',';
          alarmNumList += String("№") + (i + 1);
        }

        M_BLOCK_TAB(
          "Будильник",
          M_BOX(M_BOX(GP_LEFT, GP.SELECT("alarmNum", alarmNumList, alarm.now); M_BOX(GP_RIGHT, GP.LABEL("Откл"); GP.SWITCH("alarmDisable", (boolean)alarm.mode); GP.LABEL("Вкл"););););
          M_BOX(GP.LABEL("Громкость"); M_BOX(GP_RIGHT, GP.SLIDER("alarmVol", alarm.volumeNow, 0, 100, 10, 0, GP_GREEN, (boolean)(!deviceInformation[RADIO_ENABLE] && !deviceInformation[PLAYER_TYPE])); ); ); //Ползунки

          GP.HR();
          M_BOX(GP.LABEL("Звук"); GP.SELECT("alarmSoundType", (deviceInformation[RADIO_ENABLE]) ? "Мелодия, Радиостанция" : "Мелодия", (boolean)alarm.radio, 0, (boolean)!deviceInformation[RADIO_ENABLE]););
          M_BOX(GP.LABEL("Мелодия"); GP.SELECT("alarmSound", alarmSoundList, alarm.sound, 0););
          M_BOX(GP.LABEL("Радиостанция"); GP.SELECT("alarmRadio", alarmRadioList, alarm.station, 0, (boolean)!deviceInformation[RADIO_ENABLE]););

          GP.HR();
          M_BOX(GP.LABEL("Время"); GP.TIME("alarmTime", alarmTime););
          M_BOX(GP.LABEL("Повтор"); GP.SELECT("alarmMode", "Однократный,Ежедневно,По будням,Выбрать дни", (alarm.mode) ? (alarm.mode - 1) : 0););

          GP.HR();
          GP.TABLE_BORDER(false);
          GP.TABLE_BEGIN("200px,50px,50px,50px,50px,50px,50px,50px,200px");
          GP.TR(GP_CENTER);
          GP.TD(GP_CENTER);
          GP.LABEL("");
          GP.TD(GP_CENTER);
          GP.LABEL_BLOCK("ПН", "", GP_BLUE, 0, 1);
          GP.TD(GP_CENTER);
          GP.LABEL_BLOCK("ВТ", "", GP_BLUE, 0, 1);
          GP.TD(GP_CENTER);
          GP.LABEL_BLOCK("СР", "", GP_BLUE, 0, 1);
          GP.TD(GP_CENTER);
          GP.LABEL_BLOCK("ЧТ", "", GP_BLUE, 0, 1);
          GP.TD(GP_CENTER);
          GP.LABEL_BLOCK("ПТ", "", GP_BLUE, 0, 1);
          GP.TD(GP_CENTER);
          GP.LABEL_BLOCK("СБ", "", GP_RED, 0, 1);
          GP.TD(GP_CENTER);
          GP.LABEL_BLOCK("ВС", "", GP_RED, 0, 1);
          GP.TD(GP_CENTER);
          GP.LABEL("");

          GP.TR(GP_CENTER);
          GP.TD(GP_CENTER);
          GP.LABEL("");
          GP.TD(GP_CENTER);
          GP.CHECK("alarmDay/1", (boolean)(alarm.days & (0x01 << 1)));
          GP.TD(GP_CENTER);
          GP.CHECK("alarmDay/2", (boolean)(alarm.days & (0x01 << 2)));
          GP.TD(GP_CENTER);
          GP.CHECK("alarmDay/3", (boolean)(alarm.days & (0x01 << 3)));
          GP.TD(GP_CENTER);
          GP.CHECK("alarmDay/4", (boolean)(alarm.days & (0x01 << 4)));
          GP.TD(GP_CENTER);
          GP.CHECK("alarmDay/5", (boolean)(alarm.days & (0x01 << 5)));
          GP.TD(GP_CENTER);
          GP.CHECK("alarmDay/6", (boolean)(alarm.days & (0x01 << 6)));
          GP.TD(GP_CENTER);
          GP.CHECK("alarmDay/7", (boolean)(alarm.days & (0x01 << 7)));
          GP.TD(GP_CENTER);
          GP.LABEL("");
          GP.TABLE_END();

          boolean alarmAddStatus = (boolean)(alarm.all < 7);
          boolean alarmDelStatus = (boolean)(alarm.all > 1);

          GP.HR(GP_GRAY);
          M_BOX(GP_CENTER, M_BOX(GP_CENTER, GP.BUTTON_MINI("alarmAdd", "Добавить", "", (alarmAddStatus) ? GP_BLUE : GP_GRAY, "", !alarmAddStatus, alarmAddStatus); GP.BUTTON_MINI("alarmDel", "Удалить", "", (alarmDelStatus) ? GP_RED : GP_GRAY, "", !alarmDelStatus, alarmDelStatus);););
        );
      }
    }
    else if (ui.uri("/settings")) {//Настройки
      updateList += "mainAutoShow";
      updateList += ',';
      updateList += "mainAutoShowTime";
      updateList += ',';

      M_GRID(
        M_BLOCK_TAB(
          "Автопоказ",
          M_BOX(GP_JUSTIFY, GP.LABEL("Включить"); M_BOX(GP_RIGHT, GP.SWITCH("mainAutoShow", (boolean)mainSettings.autoShowTime);););
          M_BOX(GP_CENTER, GP.LABEL("Интервал, мин");  M_BOX(GP_RIGHT, GP.SPINNER("mainAutoShowTime", mainSettings.autoShowTime, 1, 15, 1);););
          M_BOX(GP.LABEL("Эффект"); GP.SELECT("mainAutoShowFlip", "Основной эффект,Случайная смена эффектов,Плавное угасание и появление,Перемотка по порядку числа,Перемотка по порядку катодов в лампе,Поезд,Резинка,Ворота,Волна,Блики,Испарение,Игровой автомат"););
          GP.HR();
          M_BOX(GP_CENTER, GP.LABEL("Тип данных"););
          M_BOX(GP_CENTER, GP.SPAN("(Источник и время в сек)"););
          M_BOX(GP.LABEL("1"); GP.SELECT("extShowMode/0", "Температура,Влажность,Давление,Температура и влажность,Дата,Год,Дата и год", (extendedSettings.autoShowModes[0]) ? (extendedSettings.autoShowModes[0] - 1) : 0); M_BOX(GP_RIGHT, GP.SPINNER("extShowTime/0", extendedSettings.autoShowTimes[0], 1, 5, 1);););
          M_BOX(GP.LABEL("2"); GP.SELECT("extShowMode/1", "Пусто,Температура,Влажность,Давление,Температура и влажность,Дата,Год,Дата и год", extendedSettings.autoShowModes[1]); M_BOX(GP_RIGHT, GP.SPINNER("extShowTime/1", extendedSettings.autoShowTimes[1], 1, 5, 1);););
          M_BOX(GP.LABEL("3"); GP.SELECT("extShowMode/2", "Пусто,Температура,Влажность,Давление,Температура и влажность,Дата,Год,Дата и год", extendedSettings.autoShowModes[2]); M_BOX(GP_RIGHT, GP.SPINNER("extShowTime/2", extendedSettings.autoShowTimes[2], 1, 5, 1);););
          M_BOX(GP.LABEL("4"); GP.SELECT("extShowMode/3", "Пусто,Температура,Влажность,Давление,Температура и влажность,Дата,Год,Дата и год", extendedSettings.autoShowModes[3]); M_BOX(GP_RIGHT, GP.SPINNER("extShowTime/3", extendedSettings.autoShowTimes[3], 1, 5, 1);););
          M_BOX(GP.LABEL("5"); GP.SELECT("extShowMode/4", "Пусто,Температура,Влажность,Давление,Температура и влажность,Дата,Год,Дата и год", extendedSettings.autoShowModes[4]); M_BOX(GP_RIGHT, GP.SPINNER("extShowTime/4", extendedSettings.autoShowTimes[4], 1, 5, 1);););
          GP.HR();
          M_BOX(GP_CENTER, GP.LABEL("Дополнительно"););
          M_BOX(GP_LEFT, GP.LABEL("Коррекция датчика,°C");  M_BOX(GP_RIGHT, GP.SPINNER("mainTempCorrect", mainSettings.tempCorrect / 10.0, -12.7, 12.7, 0.1, 1);););
          M_BOX(GP_LEFT, GP.LABEL("Тип датчика");  M_BOX(GP_RIGHT, GP.NUMBER("", (sens.err) ? "Ошибка" : tempSensList[sens.type], INT32_MAX, "", true);););
        );
        GP.TABLE_BEGIN();
        GP.TR(GP_CENTER);
        GP.TD(GP_CENTER, 2);
        M_BLOCK_TAB(
          "Индикаторы",
          GP.LABEL("Яркость");
          M_BOX(GP.LABEL("День"); M_BOX(GP_RIGHT, GP.SLIDER_C("mainIndiBrtDay", mainSettings.indiBrightDay, 5, 30, 1); ); );//Ползунки
          M_BOX(GP.LABEL("Ночь"); M_BOX(GP_RIGHT, GP.SLIDER_C("mainIndiBrtNight", mainSettings.indiBrightNight, 5, 30, 1); ); );//Ползунки
          GP.HR();
          M_BOX(GP_CENTER, GP.LABEL("Эффекты"););
          M_BOX(GP_JUSTIFY, GP.LABEL("Глюки"); M_BOX(GP_RIGHT, GP.SWITCH("mainGlitch", mainSettings.glitchMode);););
          M_BOX(GP.LABEL("Минуты"); GP.SELECT("fastFlip", "Без анимации,Случайная смена эффектов,Плавное угасание и появление,Перемотка по порядку числа,Перемотка по порядку катодов в лампе,Поезд,Резинка,Ворота,Волна,Блики,Испарение,Игровой автомат", fastSettings.flipMode););
          M_BOX(GP.LABEL("Секунды"); GP.SELECT("mainSecsFlip", "Без анимации,Плавное угасание и появление,Перемотка по порядку числа,Перемотка по порядку катодов в лампе", mainSettings.secsMode, 0, (boolean)(deviceInformation[LAMP_NUM] < 6)););
          GP.HR();
          M_BOX(GP_CENTER, GP.LABEL("Антиотравление(период,мин./метод)");); GP.BREAK();
          M_BOX(GP.SPINNER("extBurnTime", extendedSettings.burnTime, 10, 180, 1); GP.SELECT("mainBurnFlip", "Перебор всех индикаторов,Перебор одного индикатора,Перебор одного индикатора с отображением времени", mainSettings.burnMode););
          GP.HR();
          GP.LABEL("Время смены яркости");
          M_BOX(GP_CENTER, GP.LABEL(" С"); GP.SPINNER("mainTimeBrightS", mainSettings.timeBrightStart, 0, 23, 1); GP.SPINNER("mainTimeBrightE", mainSettings.timeBrightEnd, 0, 23, 1); GP.LABEL("До"););
          GP.HR();
          GP.LABEL("Режим сна");
          M_BOX(GP_CENTER, GP.LABEL("День"); GP.SPINNER("mainSleepD", mainSettings.timeSleepDay, 0, 90, 15); GP.SPINNER("mainSleepN", mainSettings.timeSleepNight, 0, 30, 5); GP.LABEL("Ночь"););
        );
        M_BLOCK_TAB(
          "Неонки",
          M_BOX(GP.LABEL("Разделители"); GP.SELECT("fastDot", dotModeList, fastSettings.dotMode););
          GP.HR();
          GP.LABEL("Яркость");
          M_BOX(GP.LABEL("День"); M_BOX(GP_RIGHT, GP.SLIDER_C("mainDotBrtDay", mainSettings.dotBrightDay, 5, 30, 1); ); );//Ползунки
          M_BOX(GP.LABEL("Ночь"); M_BOX(GP_RIGHT, GP.SLIDER_C("mainDotBrtNight", mainSettings.dotBrightNight, 5, 30, 1); ); );//Ползунки
        );
        GP.TABLE_END();
      );
      M_GRID(
        M_BLOCK_TAB(
          "Звуки",
          M_BOX(GP_JUSTIFY, GP.LABEL("Включить"); M_BOX(GP_RIGHT, GP.SWITCH("mainSound", mainSettings.knockSound);););
          M_BOX(GP_JUSTIFY, GP.LABEL("Громкость"); M_BOX(GP_RIGHT, GP.SLIDER("mainSoundVol", mainSettings.volumeSound, 0, 30, 1, 0, GP_GREEN, (boolean)!deviceInformation[PLAYER_TYPE]);););
          GP.HR();
          GP.LABEL("Звук смены часа ");
          M_BOX(GP_CENTER, GP.LABEL(" С"); GP.SPINNER("mainHourSoundS", mainSettings.timeHourStart, 0, 23, 1);  GP.SPINNER("mainHourSoundE", mainSettings.timeHourEnd, 0, 23, 1); GP.LABEL("До"););
        );
        GP.TABLE_BEGIN();
        GP.TR(GP_CENTER);
        GP.TD(GP_CENTER, 1);
        M_BLOCK_TAB(
          "Подсветка",
          M_BOX(GP.LABEL("Цвет"); M_BOX(GP_RIGHT, GP.SLIDER_C("fastColor", (fastSettings.backlColor != 255) ? ((fastSettings.backlColor / 10) + 1) : 0, 0, 26, 1, 0, GP_GREEN, (boolean)!deviceInformation[BACKL_TYPE]); ); );
          M_BOX(GP.LABEL("Режим"); GP.SELECT("fastBackl", backlModeList, fastSettings.backlMode, 0, (boolean)!deviceInformation[BACKL_TYPE]););
          GP.HR();
          GP.LABEL("Яркость");
          M_BOX(GP.LABEL("День"); M_BOX(GP_RIGHT, GP.SLIDER_C("mainBacklBrightDay", mainSettings.backlBrightDay / 10, 0, 25, 1, 0, GP_GREEN, (boolean)!deviceInformation[BACKL_TYPE]); ); );//Ползунки
          M_BOX(GP.LABEL("Ночь"); M_BOX(GP_RIGHT, GP.SLIDER_C("mainBacklBrightNight", mainSettings.backlBrightNight / 10, 0, 25, 1, 0, GP_GREEN, (boolean)!deviceInformation[BACKL_TYPE]); ); );//Ползунки

        );
        GP.TABLE_END();
      );

    }
    else if (ui.uri("/radio")) { //Радиоприемник
      updateList += "radioVol";
      updateList += ',';
      updateList += "radioFreq";
      updateList += ',';
      updateList += "radioPower";
      updateList += ',';

      M_BOX(M_BOX(GP_LEFT, GP.BUTTON_MINI("radioMode", "Часы ↻ Радио", "", GP_CYAN);); M_BOX(GP_RIGHT, GP.LABEL("Питание"); GP.SWITCH("radioPower", radioSettings.powerState, GP_RED););)

      M_TABLE(
        "35%",
        GP_ALS(GP_RIGHT, GP_LEFT),
        M_TR(
          GP.LABEL("Громкость"),
          GP.SLIDER_C("radioVol", radioSettings.volume, 0, 15, 1, 0, GP_CYAN)
        );
        M_TR(
          GP.LABEL("Частота"),
          GP.SLIDER_C("radioFreq", radioSettings.stationsFreq / 10.0, 87.5, 108, 0.1, 1, GP_CYAN)
        );
      );
      M_BOX(GP.BUTTON("radioSeekDown", "|◄◄", "", GP_CYAN); GP.BUTTON("radioFreqDown", "◄", "", GP_CYAN); GP.BUTTON("radioFreqUp", "►", "", GP_CYAN); GP.BUTTON("radioSeekUp", "►►|", "", GP_CYAN););
      /*
        //средние кнопки
        GP.BOX_BEGIN(GP_CENTER, "70%", 1);
        GP.BUTTON("radioSeekDown", "|◄◄");
        GP.BUTTON("radioFreqDown", "◄");
        GP.BUTTON("radioFreqUp", "►");
        GP.BUTTON("radioSeekUp", "►►|");
        GP.BOX_END();
        //маленькие кнопки
        GP.BOX_BEGIN(GP_CENTER, "100%", 1);
        GP.BUTTON_MINI("radioSeekDown", "|◄◄");
        GP.BUTTON_MINI("radioFreqDown", " ◄ ");
        GP.BUTTON_MINI("radioFreqUp", " ► ");
        GP.BUTTON_MINI("radioSeekUp", "►►|");
        GP.BOX_END();
      */
      //GP.HR();
      //M_BOX(GP_CENTER, GP.LABEL("Станции"););
      M_BLOCK_THIN_TAB(
        "Станции",
        M_TABLE(
          "20%,30%,20%,30%",
          GP_ALS(GP_RIGHT, GP_LEFT, GP_RIGHT, GP_LEFT),
      for (int i = 0; i < 10; i += 2) {
      M_TR(
        GP.BUTTON_MINI(String("ch/") + i, String("CH") + i, "", GP_CYAN),
        GP.NUMBER_F(String("sta/") + i, "number", radioSettings.stationsSave[i] / 10.0),
        GP.BUTTON_MINI(String("ch/") + (i + 1), String("CH") + (i + 1), "", GP_CYAN),
        GP.NUMBER_F(String("sta/") + (i + 1), "number", radioSettings.stationsSave[i + 1] / 10.0)
      );
      }
        );
      );
    }
    else if (ui.uri("/system_information")) { //Информация о системе
      GP.SYSTEM_INFO(ESP_FIRMWARE_VERSION);
    }
    else if (ui.uri("/update")) { //Обновление ESP
      GP.SPAN("Здесь можно обновить прошивку ESP, формат файла bin. Его можно получить открыв скетч в Arduino IDE-Скетч-Экспорт бинарного файла (сохраняется в папку со скетчем)", GP_CENTER, "", "#07b379");     // + выравнивание (GP_CENTER, GP_LEFT, GP_RIGHT, GP_JUSTIFY), умолч. GP_CENTER

      M_BLOCK(
        M_BOX(GP.LABEL("Экспорт настроек"); GP.FILE_UPLOAD(""); );
        //M_BOX(GP.LABEL("Импорт настроек"); GP.FILE_UPLOAD("file_upl"); );
        M_BOX(GP.LABEL("Обновить прошивку ESP"); GP.OTA_FIRMWARE(""); );
      );
    }
    else if (ui.uri("/network")) { //подключение к роутеру
      if (WiFi.status() != WL_CONNECTED) {
        GP.FORM_BEGIN("/");
        GP.TEXT("login", "Логин", settings.ssid);
        GP.BREAK();
        GP.TEXT("pass", "Пароль", settings.pass);
        GP.HR();
        GP.SUBMIT("Подключиться");
        GP.FORM_END();
      }
      else {
        GP.FORM_BEGIN("/network");
        GP.LABEL("Подключено к \"" + String(settings.ssid) + "\"");
        GP.LABEL("IP адрес \"" + WiFi.localIP().toString() + "\"");
        GP.HR();
        GP.SUBMIT("Отключиться");
        GP.FORM_END();
      }
    }

    GP.UPDATE(updateList);
    GP.UI_END();    // завершить окно панели управления <<<<-------------
  }
  GP.BUILD_END();
}

void action() {
  if (ui.click()) {
    if (ui.clickDate("date", mainDate)) {
      busSetComand(WRITE_DATE);
    }
    if (ui.clickTime("time", mainTime)) {
      busSetComand(WRITE_TIME);
    }
    if (ui.click("syncGmt")) {
      settings.ntpGMT = ui.getInt("syncGmt") - 12;
      ntp.setGMT(settings.ntpGMT); //установить часовой пояс в часах
      memory.update(); //обновить данные в памяти
    }
    if (ui.click("syncTime")) {
      if (WiFi.status() != WL_CONNECTED) {
        mainTime = ui.getSystemTime(); //запросить время браузера
      }
      else {
        updateTime(); //запросить текущее время
      }
      busSetComand(WRITE_TIME);
      busSetComand(WRITE_DATE);
    }
    if (ui.clickBool("mainTimeFormat", mainSettings.timeFormat)) {
      busSetComand(WRITE_MAIN_SET, MAIN_TIME_FORMAT);
    }
    //--------------------------------------------------------------------
    if (ui.clickBool("mainGlitch", mainSettings.glitchMode)) {
      busSetComand(WRITE_MAIN_SET, MAIN_GLITCH_MODE);
    }
    if (ui.clickInt("fastFlip", fastSettings.flipMode)) {
      busSetComand(WRITE_FAST_SET, FAST_FLIP_MODE);
    }
    if (ui.clickInt("fastDot", fastSettings.dotMode)) {
      busSetComand(WRITE_FAST_SET, FAST_DOT_MODE);
    }
    if (ui.clickInt("fastBackl", fastSettings.backlMode)) {
      busSetComand(WRITE_FAST_SET, FAST_BACKL_MODE);
    }
    if (ui.clickInt("mainSecsFlip", mainSettings.secsMode)) {
      busSetComand(WRITE_MAIN_SET, MAIN_SECS_MODE);
    }
    if (ui.click("fastColor")) {
      uint8_t color = constrain(ui.getInt("fastColor"), 0, 26);
      fastSettings.backlColor = (color) ? ((color - 1) * 10) : 255;
      busSetComand(WRITE_FAST_SET, FAST_BACKL_COLOR);
    }
    //--------------------------------------------------------------------
    if (ui.clickInt("mainIndiBrtDay", mainSettings.indiBrightDay)) {
      busSetComand(WRITE_MAIN_SET, MAIN_INDI_BRIGHT_D);
    }
    if (ui.clickInt("mainIndiBrtNight", mainSettings.indiBrightNight)) {
      busSetComand(WRITE_MAIN_SET, MAIN_INDI_BRIGHT_N);
    }
    if (ui.clickInt("mainBurnFlip", mainSettings.burnMode)) {
      busSetComand(WRITE_MAIN_SET, MAIN_BURN_MODE);
    }

    if (ui.click("mainAutoShow")) {
      mainSettings.autoShowTime = ui.getBool("mainAutoShow");
      busSetComand(WRITE_MAIN_SET, MAIN_AUTO_SHOW_TIME);
    }
    if (ui.clickInt("mainAutoShowTime", mainSettings.autoShowTime)) {
      busSetComand(WRITE_MAIN_SET, MAIN_AUTO_SHOW_TIME);
    }

    if (ui.clickInt("mainTimeBrightS", mainSettings.timeBrightStart)) {
      busSetComand(WRITE_MAIN_SET, MAIN_TIME_BRIGHT_S);
    }
    if (ui.clickInt("mainTimeBrightE", mainSettings.timeBrightEnd)) {
      busSetComand(WRITE_MAIN_SET, MAIN_TIME_BRIGHT_E);
    }

    if (ui.clickInt("mainHourSoundS", mainSettings.timeHourStart)) {
      busSetComand(WRITE_MAIN_SET, MAIN_TIME_HOUR_S);
    }
    if (ui.clickInt("mainHourSoundE", mainSettings.timeHourEnd)) {
      busSetComand(WRITE_MAIN_SET, MAIN_TIME_HOUR_E);
    }

    if (ui.clickInt("mainSleepD", mainSettings.timeSleepDay)) {
      busSetComand(WRITE_MAIN_SET, MAIN_TIME_SLEEP_D);
    }
    if (ui.clickInt("mainSleepN", mainSettings.timeSleepNight)) {
      busSetComand(WRITE_MAIN_SET, MAIN_TIME_SLEEP_N);
    }

    if (ui.clickInt("mainDotBrtDay", mainSettings.dotBrightDay)) {
      busSetComand(WRITE_MAIN_SET, MAIN_DOT_BRIGHT_D);
    }
    if (ui.clickInt("mainDotBrtNight", mainSettings.dotBrightNight)) {
      busSetComand(WRITE_MAIN_SET, MAIN_DOT_BRIGHT_N);
    }

    if (ui.click("mainBacklBrightDay")) {
      mainSettings.backlBrightDay = ui.getInt("mainBacklBrightDay") * 10;
      busSetComand(WRITE_MAIN_SET, MAIN_BACKL_BRIGHT_D);
    }
    if (ui.click("mainBacklBrightNight")) {
      mainSettings.backlBrightNight = ui.getInt("mainBacklBrightNight") * 10;
      busSetComand(WRITE_MAIN_SET, MAIN_BACKL_BRIGHT_N);
    }

    if (ui.click("mainSound")) {
      mainSettings.knockSound = ui.getBool("mainSound");
      busSetComand(WRITE_MAIN_SET, MAIN_KNOCK_SOUND);
    }
    if (ui.clickInt("mainSoundVol", mainSettings.volumeSound)) {
      busSetComand(WRITE_MAIN_SET, MAIN_VOLUME_SOUND);
      busSetComand(WRITE_TEST_MAIN_VOL);
    }
    if (ui.click("mainTempCorrect")) {
      mainSettings.tempCorrect = constrain((int16_t)(ui.getFloat("mainTempCorrect") * 10), -127, 127);
      busSetComand(WRITE_MAIN_SET, MAIN_TEMP_CORRECT);
    }
    //--------------------------------------------------------------------
    if (ui.click("alarmDisable")) {
      alarm.mode = ui.getBool("alarmDisable");
      busSetComand(WRITE_SELECT_ALARM, ALARM_MODE);
    }
    if (ui.click("alarmNum")) {
      alarm.now = ui.getInt("alarmNum");
      busSetComand(READ_ALARM_NUM);
      busSetComand(READ_SELECT_ALARM);
    }
    if (ui.click("alarmVol")) {
      alarm.volumeNow = ui.getInt("alarmVol");
      alarm.volumeOld = alarm.volumeNow;
      busSetComand(WRITE_SELECT_ALARM, ALARM_VOLUME);
      if (!alarm.radio && alarm.volumeNow && alarm.mode) busSetComand(WRITE_TEST_ALARM_VOL);
    }
    if (ui.click("alarmSoundType")) {
      alarm.radio = ui.getBool("alarmSoundType");
      busSetComand(WRITE_SELECT_ALARM, ALARM_RADIO);
      busSetComand(WRITE_SELECT_ALARM, ALARM_SOUND);
      busSetComand(WRITE_SELECT_ALARM, ALARM_VOLUME);
    }
    if (ui.click("alarmSound")) {
      if (!alarm.radio) {
        alarm.sound = ui.getInt("alarmSound");
        busSetComand(WRITE_SELECT_ALARM, ALARM_SOUND);
        busSetComand(WRITE_TEST_ALARM_SOUND);
      }
    }
    if (ui.click("alarmRadio")) {
      if (alarm.radio) {
        alarm.station = ui.getInt("alarmRadio");
        busSetComand(WRITE_SELECT_ALARM, ALARM_SOUND);
      }
    }
    if (ui.clickTime("alarmTime", alarmTime)) {
      alarm.hour = alarmTime.hour;
      alarm.minute = alarmTime.minute;
      busSetComand(WRITE_SELECT_ALARM, ALARM_TIME);
    }
    if (ui.click("alarmMode")) {
      if (alarm.mode) {
        alarm.mode = ui.getInt("alarmMode") + 1;
        busSetComand(WRITE_SELECT_ALARM, ALARM_MODE);
      }
    }
    if (ui.clickSub("alarmDay")) {
      uint8_t day = constrain(ui.clickNameSub(1).toInt(), 1, 7);
      if (ui.getBool(String("alarmDay/") + day)) alarm.days |= (0x01 << day);
      else alarm.days &= ~(0x01 << day);
      busSetComand(WRITE_SELECT_ALARM, ALARM_DAYS);
    }
    if (ui.click("alarmAdd")) {
      if (alarm.all < 7) {
        alarm.all++;
        alarm.now = alarm.all - 1;
        busSetComand(NEW_ALARM);
        busSetComand(READ_ALARM_NUM);
        busSetComand(READ_SELECT_ALARM);
      }
    }
    if (ui.click("alarmDel")) {
      if (alarm.all > 1) {
        alarm.all--;
        busSetComand(DEL_ALARM, alarm.now);
        if (alarm.now >= alarm.all) alarm.now = alarm.all - 1;
        busSetComand(READ_ALARM_NUM);
        busSetComand(READ_SELECT_ALARM);
      }
    }
    //--------------------------------------------------------------------
    if (ui.click("radioPower")) {
      radioSettings.powerState = ui.getBool("radioPower");
      busSetComand(WRITE_RADIO_POWER);
    }
    if (radioSettings.powerState) {
      if (ui.click("radioMode")) {
        busSetComand(WRITE_RADIO_MODE);
      }
      if (ui.click("radioSeekDown")) {
        busSetComand(RADIO_SEEK_DOWN);
      }
      if (ui.click("radioSeekUp")) {
        busSetComand(RADIO_SEEK_UP);
      }
      if (ui.click("radioFreqDown")) {
        busSetComand(READ_RADIO_FREQ);
        busSetComand(RADIO_FREQ_DOWN);
      }
      if (ui.click("radioFreqUp")) {
        busSetComand(READ_RADIO_FREQ);
        busSetComand(RADIO_FREQ_UP);
      }
      if (ui.click("radioVol")) {
        radioSettings.volume = constrain(ui.getInt("radioVol"), 0, 15);
        busSetComand(WRITE_RADIO_VOL);
      }
      if (ui.click("radioFreq")) {
        uint16_t stationFreq = (uint16_t)(ui.getFloat("radioFreq") * 10);
        radioSettings.stationsFreq = constrain(stationFreq, 870, 1080);
        busSetComand(WRITE_RADIO_FREQ);
      }
    }
    if (ui.clickSub("ch")) {
      uint8_t stationNum = constrain(ui.clickNameSub(1).toInt(), 0, 9);
      if (radioSettings.stationsSave[stationNum]) {
        radioSettings.stationsFreq = radioSettings.stationsSave[stationNum];
        if (!radioSettings.powerState) {
          radioSettings.powerState = true;
          busSetComand(WRITE_RADIO_POWER);
        }
        busSetComand(WRITE_RADIO_FREQ);
      }
    }
    if (ui.clickSub("sta")) {
      uint8_t stationNum = constrain(ui.clickNameSub(1).toInt(), 0, 9);
      uint16_t stationFreq = (uint16_t)(ui.getFloat(String("sta/") + stationNum) * 10);
      stationFreq = (stationFreq) ? constrain(stationFreq, 870, 1080) : 0;
      if (radioSettings.stationsSave[stationNum] != stationFreq) {
        radioSettings.stationsSave[stationNum] = stationFreq;
        busSetComand(WRITE_RADIO_STA, stationNum);
      }
    }
    //--------------------------------------------------------------------
    if (ui.click("extBurnTime")) {
      extendedSettings.burnTime = ui.getInt("extBurnTime");
      busSetComand(WRITE_EXTENDED_BURN_TIME);
    }
    if (ui.clickSub("extShowMode")) {
      uint8_t pos = ui.clickNameSub(1).toInt();
      uint8_t mode = ui.getInt(String("extShowMode/") + pos);
      extendedSettings.autoShowModes[pos] = (!pos) ? (mode + 1) : mode;
      busSetComand(WRITE_EXTENDED_SHOW_MODE, pos);
    }
    if (ui.clickSub("extShowTime")) {
      uint8_t pos = ui.clickNameSub(1).toInt();
      uint8_t time = ui.getInt(String("extShowTime/") + pos);
      extendedSettings.autoShowTimes[pos] = time;
      busSetComand(WRITE_EXTENDED_SHOW_TIME, pos);
    }
  }
  /**************************************************************************/
  if (ui.form()) {
    //проверяем, была ли это форма "/network"
    if (ui.form("/network")) {
      //отключаем wifi
      WiFi.disconnect();
      //включаем точку доступа
      WiFi.mode(WIFI_AP);
      ntp.end(); //остановили ntp
    }
    else if (ui.form("/")) {
      if (WiFi.status() != WL_CONNECTED) {
        ui.copyStr("login", settings.ssid); // копируем себе
        ui.copyStr("pass", settings.pass);
        memory.update(); //обновить данные в памяти
        ui.stop(); //остановили портал
      }
    }
  }
  /**************************************************************************/
  if (ui.update()) {
    if (ui.update("barTime")) {   //начинается
      ui.answer(ui.getSystemTime().encode());
    }
    if (ui.update("barTemp")) {   //начинается
      ui.answer(String((sens.temp + mainSettings.tempCorrect) / 10.0, 1) + "°С");
      busSetComand(READ_STATUS);
    }
    if (ui.update("barHum")) {   //начинается
      ui.answer(String(sens.hum) + "%");
    }
    if (ui.update("barPress")) {   //начинается
      ui.answer(String(sens.press) + "mm.Hg");
    }
    //--------------------------------------------------------------------
    if (ui.update("alarmDisable")) {
      ui.answer((boolean)alarm.mode);
    }
    if (ui.update("alarmVol")) {
      if (alarm.volumeOld != alarm.volumeNow) {
        alarm.volumeOld = alarm.volumeNow;
        ui.answer(alarm.volumeNow);
      }
    }
    if (ui.update("alarmSoundType")) {
      ui.answer(alarm.radio);
    }
    if (ui.update("alarmSound")) {
      if (!alarm.radio) {
        ui.answer(alarm.sound);
      }
    }
    if (ui.update("alarmRadio")) {
      if (alarm.radio) {
        ui.answer(alarm.station);
      }
    }
    if (ui.update("alarmTime")) {
      if ((alarm.hour != alarmTime.hour) || (alarm.minute != alarmTime.minute)) {
        alarmTime.hour = alarm.hour;
        alarmTime.minute = alarm.minute;
        ui.answer(alarmTime);
      }
    }
    if (ui.update("alarmMode")) {
      ui.answer((alarm.mode) ? (alarm.mode - 1) : 0);
    }
    if (ui.updateSub("alarmDay")) {
      uint8_t day = constrain(ui.updateNameSub(1).toInt(), 1, 7);
      ui.answer((boolean)(alarm.days & (0x01 << day)));
    }
    //--------------------------------------------------------------------
    if (ui.update("mainAutoShow")) {   //начинается
      ui.answer((boolean)mainSettings.autoShowTime);
    }
    if (ui.update("mainAutoShowTime")) {   //начинается
      ui.answer((mainSettings.autoShowTime) ? mainSettings.autoShowTime : 1);
    }
    //--------------------------------------------------------------------
    if (ui.update("radioVol")) {   //начинается
      ui.answer(constrain(radioSettings.volume, 0, 15));
    }
    if (ui.update("radioFreq")) {   //начинается
      ui.answer(constrain(radioSettings.stationsFreq, 870, 1080) / 10.0, 1);
    }
    if (ui.update("radioPower")) {   //начинается
      ui.answer(radioSettings.powerState);
      busSetComand(READ_RADIO_POWER);
    }
  }
}

boolean updateTime(void) {
  if (!ntp.updateNow()) {
    mainTime.second = ntp.second();
    mainTime.minute = ntp.minute();
    mainTime.hour = ntp.hour();
    mainDate.day = ntp.day();
    mainDate.month = ntp.month();
    mainDate.year = ntp.year();
    return true;
  }
  return false;
}

void wifi_config(void) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println F("");
    Serial.print F("Connecting to settings \"");
    Serial.print(settings.ssid);
    Serial.print F("\"...");

    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(settings.ssid, settings.pass);
    for (int8_t i = 50; i > 0; i--) {
      Serial.print F(".");
      delay(500);
      if (WiFi.status() == WL_CONNECTED) {
        Serial.println F("");
        Serial.println F("Wifi connected");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());

        ntp.begin(); //запустить ntp
        ntp.setGMT(settings.ntpGMT); //установить часовой пояс в часах
        updateTime(); //запросить текущее время
        break;
      }
    }
  }

  IPAddress apIP(AP_IP);
  IPAddress subnet(255, 255, 255, 0);
  //если не удалось подключиться запускаем в режиме точки доступа
  Serial.println F("");
  Serial.print F("Access Point ssid: ");
  Serial.println(AP_SSID);
  Serial.print F("Access Point pass: ");
  Serial.println(AP_PASS);
  if (WiFi.status() != WL_CONNECTED) {
    //отключаем wifi
    WiFi.disconnect();
    //включаем точку доступа
    WiFi.mode(WIFI_AP);
  }
  //задаем настройки сети
  WiFi.softAPConfig(apIP, apIP, subnet);
  //включаем wifi в режиме точки доступа с именем и паролем по умолчанию
  WiFi.softAP(AP_SSID, AP_PASS);
}

void setup() {
  twi_init();

  Serial.begin(115200);

  // читаем логин пароль из памяти
  EEPROM.begin(memory.blockSize());
  if (memory.begin(0, 0xA5) == 1) {
    for (uint8_t i = 0; i < 20; i++) {
      settings.ssid[i] = '\0';
      settings.pass[i] = '\0';
    }
    settings.ntpGMT = DEFAULT_GMT; //установить часовой по умолчанию
    memory.update(); //обновить данные в памяти
  }

  deviceInformation[HARDWARE_VERSION] = HW_VERSION;
  alarm.now = 0;

  busSetComand(READ_DEVICE);
  busSetComand(WRITE_CHECK_SENS);
  busSetComand(READ_TIME_DATE);
  busSetComand(READ_FAST_SET);
  busSetComand(READ_MAIN_SET);
  busSetComand(READ_EXTENDED_SET);
  busSetComand(READ_RADIO_VOL);
  busSetComand(READ_RADIO_FREQ);
  busSetComand(READ_RADIO_STA);
  busSetComand(READ_ALARM_NUM);
  busSetComand(READ_SELECT_ALARM);
  busSetComand(READ_SENS_DATA);
  busSetComand(READ_SENS_INFO);
  busTimerSetInterval(5000);
}

void loop() {
  if (!ui.state()) { //если портал не запущен
    //if (!busStatusBuffer()) { //если ничего не отправляется по шине
    //поключаемся к wifi
    wifi_config();
    //подключаем конструктор и запускаем
    ui.attachBuild(build);
    ui.attach(action);
    ui.start();
    ui.enableOTA(); //без пароля
    ui.downloadAuto(true);
    //}
  }

  if (ntp.tick()) {
    if (!ntp.status()) {
      mainTime.second = ntp.second();
      mainTime.minute = ntp.minute();
      mainTime.hour = ntp.hour();
      mainDate.day = ntp.day();
      mainDate.month = ntp.month();
      mainDate.year = ntp.year();
      busSetComand(WRITE_TIME);
      busSetComand(WRITE_DATE);
    }
  }

  ui.tick();

  static uint32_t timer;
  if ((millis() - timer) >= 60000) {
    timer = millis();
    busSetComand(WRITE_CHECK_SENS);
    busSetComand(READ_SENS_DATA);
  }

  if (deviceStatus) {
    for (uint8_t i = 0; i < STATUS_MAX_DATA; i++) { //проверяем все флаги
      if (deviceStatus & 0x01) { //если флаг установлен
        switch (i) { //выбираем действие
          case STATUS_UPDATE_TIME_SET: busSetComand(READ_TIME_DATE); break;
          case STATUS_UPDATE_MAIN_SET: busSetComand(READ_MAIN_SET); break;
          case STATUS_UPDATE_FAST_SET: busSetComand(READ_FAST_SET); break;
          case STATUS_UPDATE_RADIO_SET: busSetComand(READ_RADIO_VOL); busSetComand(READ_RADIO_FREQ); busSetComand(READ_RADIO_STA); break;
          case STATUS_UPDATE_ALARM_SET: busSetComand(READ_ALARM_NUM); busSetComand(READ_SELECT_ALARM); break;
        }
      }
      deviceStatus >>= 1; //сместили буфер флагов
    }
    deviceStatus = 0;
  }

  busUpdate();
  memory.tick();
}
