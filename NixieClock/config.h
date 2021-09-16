#define BACKL_WS2812B 0         //использовать адрессные светодиоды подсветки вместо обычных(0 - обычные светодиоды | 1 - светодиоды WS2812B)
#define BOARD_TYPE 0            //тип платы часов(0 - IN-12 (индикаторы стоят правильно) | 1 - IN-12 turned (индикаторы перевёрнуты) | 2 - IN-14 (обычная и neon dot) | 3 - другие индикаторы(4 лампы) | 4 - другие индикаторы(6 ламп))
#define LAMP_NUM 4              //количесвто используемых ламп в часах(4 или 6)
#define NEON_DOT 0              //использовать неоновую лампу в качестве секундных точек(0 - точка светодиодная | 1 - точка неоновая лампа)

#define BTN_TYPE 0              //тип кнопок(0 - используются цифровые кнопки | 1 - используются аналоговые кнопки)(доп кнопка в любом режиме цифровая)
#define BTN_PULL 1              //тип подтяжки цифровых кнопок(0 - кнопки подтянуты к земле (LOW_PULL) | 1 - кнопки подтянуты к питанию (HIGH_PULL))
#define BTN_ADD_PULL 1          //тип подтяжки цифровой дополнительной кнопки(0 - кнопка подтянута к земле (LOW_PULL) | 1 - кнопка подтянута к питанию (HIGH_PULL))

#define BURN_INDI_TYPE 0        //тип анимации антиотравления ламп(0 - с отображением времени | 1 - без отображения времени)
#define USE_ONE_ALARM 1         //использовать только один будильник(0 - неограниченое количество будильников(сложное меню будильников) | 1 - один будильник(простое меню будильника))

#define DEFAULT_TIME_FORMAT 0   //формат времени по умолчанию(0 - 24 часа | 1 - 12 часов)
#define DEFAULT_TEMP_SENSOR 0   //датчик температуры по умолчанию(0 - DS3231(встроенный) | 1 - BME/BMP_280(180) | 2 - DHT11/12 | 3 - DHT21/22(AM2301) | 4 - DS18B20)
#define DEFAULT_TEMP_CORRECT 0  //коррекция температуры по умолчанию(-127..127)(0.1°c)
#define DEFAULT_BACKL_MODE 1    //режим подсветки по умолчанию(0 - выкл | 1 - статичная | 2 - динамичная(дыхание)), для WS2812B(0 - выкл | 1..7 - статичные цвета(удержание средней кнопки - вкл/выкл режим дыхания) | 8 - дыхание со сменой цвета при затухании | 9 - плавная смена цвета | 10 - радуга | 11 - рандомные цвета)
#define DEFAULT_DOT_MODE 2      //режим работы точки по умолчанию(0 - выкл | 1 - статичная | 2 - динамичная(плавно мигает))

#define DEFAULT_FLIP_ANIM 2     //режим перелистования цифр по умолчанию(0 - выкл | 1 - рандомная смена эффектов | 2 - плавное угасание и появление | 3 - перемотка по порядку числа | 4 - перемотка по порядку катодов в лампе | 5 - поезд | 6 - резинка | 7 - волна | 8 - блики | 9 - испарение)

#define FLIP_MODE_2_TIME 120    //шаг яркости эффекта номер 2 дневной(100..150)(мс)
#define FLIP_MODE_3_TIME 80     //скорость шага эффекта номер 3(50..80)(мс)
#define FLIP_MODE_4_TIME 80     //скорость шага эффекта номер 4(30..80)(мс)
#define FLIP_MODE_5_TIME 150    //скорость шага эффекта номер 5(50..170)(мс)
#define FLIP_MODE_6_TIME 80     //скорость шага эффекта номер 6(50..150)(мс)
#define FLIP_MODE_7_TIME 200    //скорость шага эффекта номер 7(100..300)(мс)
#define FLIP_MODE_8_TIME 200    //скорость шага эффекта номер 8(100..300)(мс)
#define FLIP_MODE_9_TIME 200    //скорость шага эффекта номер 9(100..300)(мс)

#define DEFAULT_NIGHT_START 20  //час перехода на ночную подсветку по умолчанию(BRIGHT_N)(NIGHT_START = NIGHT_END - только дневная подсветка)
#define DEFAULT_NIGHT_END 8     //час перехода на дневную подсветку по умолчанию(BRIGHT)
#define DEFAULT_INDI_BRIGHT 25  //яркость цифр дневная по умолчанию(0..30)
#define DEFAULT_INDI_BRIGHT_N 5 //яркость цифр ночная по умолчанию(0..30)

#define BACKL_BRIGHT 255        //яркость подсветки ламп дневная(5..255)
#define BACKL_BRIGHT_N 120      //яркость подсветки ламп ночная(0..255)(0 - подсветка выключена)
#define BACKL_MIN_BRIGHT 32     //минимальная яркость подсветки ламп в режиме дыхание(0..255)
#define BACKL_PAUSE 200         //пазуа между вспышками подсветки ламп в режиме дыхание(100..1000)(мс)
#define BACKL_STEP 1            //шаг яркости подсветки(1..255)
#define BACKL_TIME 12000        //период подсветки(100..12000)(мс)

#define BACKL_MODE_9_TIME 30    //скорость шага эффекта подсветки номер 9(мс)
#define BACKL_MODE_10_TIME 80   //скорость шага эффекта подсветки номер 10(мс)
#define BACKL_MODE_10_STEP 15   //размер шага эффекта подсветки номер 10(1..50)
#define BACKL_MODE_11_TIME 80   //скорость шага эффекта подсветки номер 11(мс)

#define DOT_BRIGHT 50           //яркость точки дневная(5..200)
#define DOT_BRIGHT_N 20         //яркость точки ночная(5..200)
#define DOT_TIMER 4             //шаг яркости точки(4..255)(мс)
#define DOT_TIME 250            //время мигания точки(100..1000)(мс)

#define DEFAULT_GLITCH_MODE 1   //режим глюков по умолчанию(1 - вкл | 0 - выкл)
#define GLITCH_MIN 40           //минимальное время между глюками(1..240)(сек)
#define GLITCH_MAX 160          //максимальное время между глюками(1..240)(сек)
#define GLITCH_NUM_MIN 2        //минимальное количество глюков(1..254)
#define GLITCH_NUM_MAX 6        //максимальное количество глюков(2..255)

#define BURN_TIME 40            //период обхода индикаторов в режиме очистки(10..240)(мс)
#define BURN_LOOPS 4            //количество циклов очистки за каждый период(1..10)
#define BURN_PERIOD 12          //период антиотравления(1..180)(мин)
#define BURN_PHASE 25           //смещение фазы периода антиотравления(5..30)(сек)

#define DEFAULT_AUTO_TEMP_TIME 60    //интервал автоматического показа температуры(5..240)(шаг - 5)(0 - выключить автоматический показ)(с)
#define AUTO_TEMP_PAUSE_TIME 5000    //пауза между сменой данных на индикаторе(1000..15000)(мс)
#define AUTO_TEMP_ANIM_TIME 300      //скорость шага анимации(50..500)(мс)

#define DEFAULT_KNOCK_SOUND 1        //запрет звука нажатия клавиш по умолчанию(1 - звук вкл | 0 - звук выкл)
#define KNOCK_SOUND_FREQ 1000        //частота звука клавиш(10..10000)(Гц)
#define KNOCK_SOUND_TIME 30          //длительность звука клавиш(10..500)(мс)

#define DEFAULT_HOUR_SOUND_START 8   //время начала звука смены часа по умолчанию(0..23)(ч)(DEFAULT_HOUR_SOUND_START = DEFAULT_HOUR_SOUND_END - выключить звук)
#define DEFAULT_HOUR_SOUND_END 23    //время окончания звука смены часа по умолчанию(0..23)(ч)
#define HOUR_SOUND_FREQ 1000         //частота звука смены часа(10..10000)(Гц)
#define HOUR_SOUND_TIME 500          //длительность звука смены часа(10..500)(мс)

#define DEFAULT_ALARM_TIME_HH 8      //час будильника по умолчанию(0..23)
#define DEFAULT_ALARM_TIME_MM 0      //минута будильника по умолчанию(0..59)
#define DEFAULT_ALARM_MODE 0         //режим будильника по умолчанию(0..2)(0 - выкл | 2 - одиночный | 1 - вкл)
#define DEFAULT_ALARM_SOUND 0        //мелодия будильника по умолчанию(0..3)

#define ALARM_TIMEOUT_SOUND 1        //таймаут до автоматического включения ожидания будильника по умолчанию(0..240)(0 - выкл повторное включение)(м)
#define ALARM_TIMEOUT 15             //таймаут до полного отключения будильника по умолчанию(1..240)(м)
#define ALARM_WAINT 4                //ожидание будильника для повторного включения по умолчанию(1..240)(0 - выкл ожидание по короткому нажатию)(м)

#define ALM_ON_BLINK_DOT 3           //режим мигания точек если хоть один будильник включен(0 - выкл | 1 - статичная | 2 - без реакции | 3 - мигает один раз в секунду | 4 - мигает два раза в секунду)
#define ALM_WAINT_BLINK_DOT 4        //режим мигания точек если ожидаем повторного сигнала(0 - выкл | 1 - статичная | 2 - без реакции | 3 - мигает один раз в секунду | 4 - мигает два раза в секунду)
#define ALM_BLINK_TIME 500           //период мигания времени во время активного будильника(100..1000)(мс)
#define ALM_OFF_SOUND_FREQ 2000      //частота звука подтверждения отключения будильника(10..10000)(Гц)
#define ALM_OFF_SOUND_TIME 1000      //длительность звука подтверждения отключения будильника(10..2000)(мс)

const uint16_t _sound_1[][3] PROGMEM = { //массив семплов 1-й мелодии будильника || семпл - частота(10..10000)(Hz) | длительность звука(4..10000)(ms) | длительность семпла(4..10000)(ms)
  {2000, 500, 1000}
};
const uint16_t _sound_2[][3] PROGMEM = { //массив семплов 2-й мелодии будильника || семпл - частота(10..10000)(Hz) | длительность звука(4..10000)(ms) | длительность семпла(4..10000)(ms)
  {2000, 100, 170}, {2000, 100, 170}, {2000, 100, 500}
};
const uint16_t _sound_3[][3] PROGMEM = { //массив семплов 3-й мелодии будильника || семпл - частота(10..10000)(Hz) | длительность звука(4..10000)(ms) | длительность семпла(4..10000)(ms)
  {2000, 250, 250}, {1500, 250, 350}, {2000, 250, 250}, {1500, 250, 350},
  {2000, 250, 250}, {1500, 250, 350}, {2000, 250, 250}, {1500, 250, 750}
};
const uint16_t _sound_4[][3] PROGMEM = { //массив семплов 4-й мелодии будильника || семпл - частота(10..10000)(Hz) | длительность звука(4..10000)(ms) | длительность семпла(4..10000)(ms)
  {392, 700, 700}, {392, 700, 700}, {392, 700, 700}, {311, 500, 500}, 
  {466, 200, 200}, {392, 700, 700}, {311, 500, 500}, {466, 200, 200}, 
  {392, 1400, 1400}, {587, 700, 700}, {587, 700, 700}, {587, 700, 700},
  {622, 500, 500}, {466, 200, 200}, {369, 700, 700}, {311, 500, 500},
  {466, 200, 200}, {392, 1400, 1400}, {784, 700, 700}, {392, 500, 500},
  {392, 200, 200}, {784, 700, 700}, {739, 500, 500}, {698, 200, 200},
  {659, 200, 200}, {622, 200, 200}, {659, 900, 900}, {415, 300, 300},
  {554, 700, 700}, {523, 500, 500}, {493, 200, 200}, {466, 200, 200},
  {440, 200, 200}, {466, 900, 900}, {311, 300, 300}, {369, 700, 700},
  {311, 500, 500}, {466, 200, 200}, {392, 1500, 2500}
};
const uint16_t alarm_sound[][2] = {  //массив мелодий будильника
  {(uint16_t)&_sound_1, sizeof(_sound_1) / 6},
  {(uint16_t)&_sound_2, sizeof(_sound_2) / 6},
  {(uint16_t)&_sound_3, sizeof(_sound_3) / 6},
  {(uint16_t)&_sound_4, sizeof(_sound_4) / 6}
};

#define RTC_ERROR_SOUND_FREQ 2000    //частота звука ошибки связи с модулем часов(10..10000)(Гц)
#define RTC_ERROR_SOUND_TIME 2000    //длительность звука ошибки связи с модулем часов(500..5000)(мс)

#define SETTINGS_TIMEOUT 30          //тайм-аут выхода из настройки времени по бездействию(5..60)(сек)
#define SETTINGS_BLINK_TIME 500      //период мигания активного пункта меню(100..1000)(мс)

#define TIMER_BLINK_TIME 500         //период мигания таймера по окончанию отсчета(100..1000)(мс)

#define SHOW_TIME 3000               //время отображения дополнительной информации(мс)
#define ANIM_TIME 150                //время анимации настроек(мс)
#define SWITCH_TIME 1500             //время отображения настроек(мс)

#define FLIP_EFFECT_NUM 9            //максимальное количество эффектов

#define MIN_PWM 100                  //минимальная скважность(индикаторы выключены, яркость минимальная)
#define MAX_PWM 180                  //максимальная скважность(индикаторы включены, яркость максимальная)

#define DEFAULT_TIME_PERIOD 2400     //период тика таймера счета времени(мкс)
#define TIME_PERIOD_MIN 2000         //минимальный период тика таймера счета времени(мкс)
#define TIME_PERIOD_MAX 2800         //максимальный период тика таймера счета времени(мкс)

#define BTN_GIST_TICK 16             //количество циклов для защиты от дребезга(0..255)(1 цикл -> 2мс)
#define BTN_HOLD_TICK 255            //количество циклов после которого считается что кнопка зажата(0..65500)(1 цикл -> 2мс)

#define TEST_SQW_TIME 2000           //время проверки сигнала с пина SQW(1500..5000)(мс)
#define TEST_LAMP_TIME 500           //время проверки горения цифры(500..5000)(мс)

#define BTN_SET_MIN 98               //минимальное значение АЦП для клавиши "ОК"(0..255)
#define BTN_SET_MAX 115              //максимальное значение АЦП для клавиши "ОК"(0..255)
#define BTN_LEFT_MIN 236             //минимальное значение АЦП для "ЛЕВОЙ" клавиши(0..255)
#define BTN_LEFT_MAX 255             //максимальное значение АЦП для "ЛЕВОЙ" клавиши(0..255)
#define BTN_RIGHT_MIN 55             //минимальное значение АЦП для "ПРАВОЙ" клавиши(0..255)
#define BTN_RIGHT_MAX 95             //максимальное значение АЦП для "ПРАВОЙ" клавиши(0..255)

#define EEPROM_BLOCK_NULL 0          //начальный блок памяти
#define EEPROM_BLOCK_CRC 255         //блок памяти контрольной суммы настроек
