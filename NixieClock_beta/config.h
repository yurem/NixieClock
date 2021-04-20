#define BOARD_TYPE 4  // тип платы часов(0 - IN-12 (индикаторы стоят правильно) | 1 - IN-12 turned (индикаторы перевёрнуты) | 2 - IN-14 (обычная и neon dot) | 3 другие индикаторы)
       
#define DEFAULT_NIGHT_START 20    //час перехода на ночную подсветку(BRIGHT_N)
#define DEFAULT_NIGHT_END 8       //час перехода на дневную подсветку(BRIGHT)

#define DEFAULT_BACKL_BRIGHT 255     //яркость подсветки ламп дневная(1..255)
#define DEFAULT_BACKL_BRIGHT_N 120   //яркость подсветки ламп ночная(0..255)(0 - подсветка выключена)
#define DEFAULT_BACKL_MIN_BRIGHT 32  //минимальная яркость подсветки ламп в режиме дыхание(0..255)
#define DEFAULT_BACKL_PAUSE 200      //пазуа между вспышками подсветки ламп в режиме дыхание(100..1000)(мс)
#define DEFAULT_BACKL_STEP 1        //шаг яркости подсветки(1..255)
#define DEFAULT_BACKL_TIME 12000    //период подсветки(100..12000)(мс)

#define DEFAULT_DOT_BRIGHT 100       //яркость точки дневная(1..255)
#define DEFAULT_DOT_BRIGHT_N 44      //яркость точки ночная(1..255)
#define DEFAULT_DOT_TIMER 4         //шаг яркости точки(4..255)(мс)
#define DEFAULT_DOT_TIME 200        //время мигания точки(100..1000)(мс)

#define MIN_PWM 100 //минимальная скважность(индикаторы выключены, яркость минимальная)
#define MAX_PWM 180 //максимальная скважность(индикаторы включены, яркость максимальная)

#define BTN_GIST_TICK    8    //количество циклов для защиты от дребезга(0..255)(1 цикл -> 4мс)
#define BTN_HOLD_TICK    127   //количество циклов после которого считается что кнопка зажата(0..255)(1 цикл -> 4мс)

const uint16_t _sound_1[][3] PROGMEM = { //массив семплов 1-й мелодии будильника
  {550, 100, 150}, //семпл 0 - частота(10..10000)(Hz) | длительность звука(50..500)(ms) | длительность паузы(50..1000)(ms)
  {550, 100, 150}, //семпл 1 - частота(10..10000)(Hz) | длительность звука(50..500)(ms) | длительность паузы(50..1000)(ms)
  {550, 100, 150}, //семпл 2 - частота(10..10000)(Hz) | длительность звука(50..500)(ms) | длительность паузы(50..1000)(ms)
  {550, 100, 150}, //семпл 3 - частота(10..10000)(Hz) | длительность звука(50..500)(ms) | длительность паузы(50..1000)(ms)
  {1500, 200, 250}, //семпл 4 - частота(10..10000)(Hz) | длительность звука(50..500)(ms) | длительность паузы(50..1000)(ms)
  {1500, 200, 250}, //семпл 5 - частота(10..10000)(Hz) | длительность звука(50..500)(ms) | длительность паузы(50..1000)(ms)
  {550, 100, 150}, //семпл 6 - частота(10..10000)(Hz) | длительность звука(50..500)(ms) | длительность паузы(50..1000)(ms)
  {550, 100, 150}, //семпл 7 - частота(10..10000)(Hz) | длительность звука(50..500)(ms) | длительность паузы(50..1000)(ms)
  {550, 100, 550}  //семпл 8 - частота(10..10000)(Hz) | длительность звука(50..500)(ms) | длительность паузы(50..1000)(ms)
};
const uint16_t alarm_sound[][2] = { //массив мелодий будильника
  {&_sound_1, sizeof(_sound_1) / 6}
};
