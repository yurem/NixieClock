//Типы плат часов
#if (BOARD_TYPE == 0) //IN-12 (индикаторы стоят правильно)
volatile uint8_t* anodePort[] = {&DOT_PORT, &ANODE_1_PORT, &ANODE_2_PORT, &ANODE_3_PORT, &ANODE_4_PORT, ANODE_OFF, ANODE_OFF}; //таблица портов анодов ламп
const uint8_t anodeBit[] = {0x01 << DOT_BIT, 0x01 << ANODE_1_BIT, 0x01 << ANODE_2_BIT, 0x01 << ANODE_3_BIT, 0x01 << ANODE_4_BIT, ANODE_OFF, ANODE_OFF}; //таблица бит анодов ламп
const uint8_t digitMask[] = {7, 3, 6, 4, 1, 9, 8, 0, 5, 2, 10};   //маска дешифратора платы in12 (цифры нормальные)(цифра "10" - это пустой символ, должен быть всегда в конце)
const uint8_t cathodeMask[] = {1, 6, 2, 7, 5, 0, 4, 9, 8, 3};     //порядок катодов in12
#elif (BOARD_TYPE == 1) //IN-12 turned (индикаторы перевёрнуты)
volatile uint8_t* anodePort[] = {&DOT_PORT, &ANODE_4_PORT, &ANODE_3_PORT, &ANODE_2_PORT, &ANODE_1_PORT, ANODE_OFF, ANODE_OFF}; //таблица портов анодов ламп
const uint8_t anodeBit[] = {0x01 << DOT_BIT, 0x01 << ANODE_4_BIT, 0x01 << ANODE_3_BIT, 0x01 << ANODE_2_BIT, 0x01 << ANODE_1_BIT, ANODE_OFF, ANODE_OFF}; //таблица бит анодов ламп
const uint8_t digitMask[] = {2, 8, 1, 9, 6, 4, 3, 5, 0, 7, 10};   //маска дешифратора платы in12 turned (цифры вверх ногами)(цифра "10" - это пустой символ, должен быть всегда в конце)
const uint8_t cathodeMask[] = {1, 6, 2, 7, 5, 0, 4, 9, 8, 3};     //порядок катодов in12
#elif (BOARD_TYPE == 2) //IN-14 (обычная и neon dot)
volatile uint8_t* anodePort[] = {&DOT_PORT, &ANODE_4_PORT, &ANODE_3_PORT, &ANODE_2_PORT, &ANODE_1_PORT, ANODE_OFF, ANODE_OFF}; //таблица портов анодов ламп
const uint8_t anodeBit[] = {0x01 << DOT_BIT, 0x01 << ANODE_4_BIT, 0x01 << ANODE_3_BIT, 0x01 << ANODE_2_BIT, 0x01 << ANODE_1_BIT, ANODE_OFF, ANODE_OFF}; //таблица бит анодов ламп
const uint8_t digitMask[] = {9, 8, 0, 5, 4, 7, 3, 6, 2, 1, 10};   //маска дешифратора платы in14(цифра "10" - это пустой символ, должен быть всегда в конце)
const uint8_t cathodeMask[] = {1, 0, 2, 9, 3, 8, 4, 7, 5, 6};     //порядок катодов in14
#elif (BOARD_TYPE == 3) //другие индикаторы(4 лампы)
volatile uint8_t* anodePort[] = {&DOT_PORT, &ANODE_4_PORT, &ANODE_3_PORT, &ANODE_2_PORT, &ANODE_1_PORT, ANODE_OFF, ANODE_OFF}; //таблица портов анодов ламп
const uint8_t anodeBit[] = {0x01 << DOT_BIT, 0x01 << ANODE_4_BIT, 0x01 << ANODE_3_BIT, 0x01 << ANODE_2_BIT, 0x01 << ANODE_1_BIT, ANODE_OFF, ANODE_OFF}; //таблица бит анодов ламп
const uint8_t digitMask[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};   //тут вводим свой порядок пинов лампы(цифра "10" - это пустой символ, должен быть всегда в конце)
const uint8_t cathodeMask[] = {1, 6, 2, 7, 5, 0, 4, 9, 8, 3};     //порядок катодов in12
#elif (BOARD_TYPE == 4) //другие индикаторы(6 ламп)
volatile uint8_t* anodePort[] = {&DOT_PORT, &ANODE_1_PORT, &ANODE_2_PORT, &ANODE_3_PORT, &ANODE_4_PORT, &ANODE_5_PORT, &ANODE_6_PORT}; //таблица портов анодов ламп
const uint8_t anodeBit[] = {0x01 << DOT_BIT, 0x01 << ANODE_1_BIT, 0x01 << ANODE_2_BIT, 0x01 << ANODE_3_BIT, 0x01 << ANODE_4_BIT, 0x01 << ANODE_5_BIT, 0x01 << ANODE_6_BIT}; //таблица бит анодов ламп
const uint8_t digitMask[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};   //тут вводим свой порядок пинов лампы(цифра "10" - это пустой символ, должен быть всегда в конце)
const uint8_t cathodeMask[] = {1, 0, 2, 9, 3, 8, 4, 7, 5, 6};     //порядок катодов in14
#endif

//Мелодии будильника
#define SOUND_PATTERN(ptr) {(uint16_t)&ptr, sizeof(ptr) / 6} //маска для массива мелодий

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
  SOUND_PATTERN(_sound_1),
  SOUND_PATTERN(_sound_2),
  SOUND_PATTERN(_sound_3),
  SOUND_PATTERN(_sound_4)
};

//Технические конфигурации
#define ERROR_SHOW_TIME 3000         //время отображения ошибки(1000...5000)(мс)
#define ERROR_SOUND_FREQ 2000        //частота звука ошибки связи с модулем часов(10..10000)(Гц)
#define ERROR_SOUND_TIME 2000        //длительность звука ошибки связи с модулем часов(500..5000)(мс)

#define DEBUG_RESET_SOUND_FREQ 1000  //частота звука подтверждения сброса настроек отладки(10..10000)(Гц)
#define DEBUG_RESET_SOUND_TIME 1500  //длительность звука подтверждения сброса настроек отладки(500..5000)(мс)

#define DEBUG_PASS 0                 //пароль для входа в отладку(0..9999)
#define DEBUG_TIMEOUT 30             //тайм-аут выхода из ввода пароля отладки по бездействию(5..60)(сек)
#define DEBUG_BLINK_TIME 500         //период мигания активного разряда пароля(100..1000)(мс)

#define SETTINGS_TIMEOUT 30          //тайм-аут выхода из настроек по бездействию(5..60)(сек)
#define SETTINGS_BLINK_TIME 500      //период мигания активного пункта настроек(100..1000)(мс)

#define TIMER_BLINK_TIME 500         //период мигания таймера по окончанию отсчета(100..1000)(мс)

#define SHOW_TIME 3000               //время отображения дополнительной информации(2..65500)(мс)
#define ANIM_TIME 150                //время анимации настроек(2..65500)(мс)

#define FAST_BACKL_TIME 3000         //время отображения настройки режима подсветки(мс)
#define FAST_FLIP_TIME 1500          //время отображения настройки перелистывания цифр(мс)
#define FAST_DOT_TIME 1500           //время отображения настройки режима точек(мс)

#define TEST_SQW_TIME 2000           //время проверки сигнала с пина SQW(1500..5000)(мс)
#define MIN_SQW_TIME 500             //минимальное время сигнала с пина SQW(500..1000)(мс)
#define MAX_SQW_TIME 1500            //максимальное время сигнала с пина SQW(1000..2000)(мс)

#define TEST_LAMP_TIME 500           //время проверки горения цифры(500..5000)(мс)

#define REFERENCE 1.1                //опорное напряжение(1.0..1.2)(в)
#define MAX_VCC 5.5                  //максимальное напряжение питания
#define MIN_VCC 4.5                  //минимальное напряжение питания

#define BTN_GIST_TIME 50             //время для защиты от дребезга(0..250)(мс)
#define BTN_HOLD_TIME 550            //время после которого считается что кнопка зажата(0..5000)(мс)

#define BTN_ANALOG_GIST 25           //гистерезис значения ацп кнопок(5..50)

#define EEPROM_BLOCK_NULL 0          //начальный блок памяти(0..511)
