//Настройки основной периферии
#define BACKL_TYPE 3              //тип подсветки индикаторов(0 - подсветка не используется | 1 - хардверный шим(обычные светодиоды)(только D11)(только без SD плеера и хардверным UART) | 2 - софтверный шим(обычные светодиоды)(любой пин)(только без IR приемника) | 3 - светодиоды WS2812B(любой пин))
#define BOARD_TYPE 0              //тип платы часов(0 - IN-12 (индикаторы стоят правильно) | 1 - IN-12 turned (индикаторы перевёрнуты) | 2 - IN-14 (обычная и неоновая точка) | 3 - другие индикаторы(платы)(настройка в config.h))
#define NEON_DOT 1                //тип секундных точек(0 - точка светодиодная | 1 - точка неоновая лампа(1 шт) | 2 - точка неоновая лампа(2 шт) | 3 - точка в индикаторе)
#define LAMP_NUM 6                //количесвто используемых ламп в часах(4 или 6)

//Настройки внешней связи
#define ESP_ENABLE 1              //включить поддержку внешнего модуля ESP8266 на шине I2C(0 - модуль не используется(или используется на стороне esp) | 1 - модуль используется)
#define DS3231_ENABLE 2           //включить поддержку модуля часов DS3231(0 - модуль не используется | 1 - используется только модуль часов | 2 - используется модуль часов и встроенный датчик температуры)

//Настройки вывода звука
#define PLAYER_TYPE 1             //тип плеера озвучки(0 - бузер | 1 - DF плеер | 2 - SD плеер)
#define PLAYER_UART_MODE 0        //режим работы UART DF плеера(0 - хардверный UART(только D1) | 1 - софтверный UART(любой пин)(только если адресные светодиоды или софтовый шим подсветки))

//Настройки усилителя
#define AMP_PORT_ENABLE 1         //включить использование порта управления питанием усилителя(0 - порт не используется | 1 - порт используется)
#define AMP_POWER_MODE 0          //режим управления питанием усилителя(0 - низкий уровень | 1 - высокий уровень)
#define AMP_WAIT_TIME 100         //время ожидания активации усилителя(10..150)(мс)

//Настройки индикации
#define INDI_PORT_TYPE 0          //тип подключения анодов индикаторов и разделительных точек(2-х неоновых ламп)(0 - прямое подключение к микроконтроллеру | 1 - подключение через сдвиговый регистр)
#define INDI_DOT_TYPE 0           //тип подключения секундных неоновых ламп при использовании сдвигового регистра(0 - прямое подключение к микроконтроллеру | 1 - подключение через сдвиговый регистр)

//Настройки разделительных точек
#define DOTS_PORT_ENABLE 0        //включить использование порта разделительных точек в индикаторах(0 - порт не используется | 1 - прямое подключение к микроконтроллеру | 2 - подключение через сдвиговый регистр)
#define DOTS_TYPE 0               //тип разделительных точек в индикаторах(0 - только левые точки | 1 - только правые точки | 2 - левые и правые точки)
#define DOTS_NUM 4                //количесвто ламп в которых используются разделительные точки(4 или 6)

#define DOTS_MAIN 2               //выбор расположения основных секундных точек(для режимов - статичная, мигающая, одинарный маятник))(только если используются левые и правые точки)(0 - только левая точка | 1 - только правая точка | 2 - одна левая и одна правая точка(внутри) | 3 - одна левая и одна правая точка(снаружи) | 4 - две левых и две правых точки)
#define DOTS_DIV 0                //выбор расположения разделительных точек(в режимах - температура, дата, радио)(только если используются левые и правые точки)(0 - левая точка | 1 - правая точка)

//Настройки дополнительной периферии
#define SENS_AHT_ENABLE 0         //включить поддержку датчиков температуры AHT1x и AHT2x(0 - датчик не используется(или используется на стороне esp) | 1 - используется датчик AHT10/AHT15/AHT20)
#define SENS_SHT_ENABLE 0         //включить поддержку датчиков температуры SHT2x и SHT3x(0 - датчик не используется(или используется на стороне esp) | 1 - используется датчик SHT2x | 2 - используется датчик SHT3x | 3 - используются датчики SHT2x/SHT3x)
#define SENS_BME_ENABLE 0         //включить поддержку датчиков температуры BMPxxx и BMExxx(0 - датчик не используется(или используется на стороне esp) | 1 - используется датчик BMP085/BMP180 | 2 - используется датчик BMP280/BME280 | 3 - используются датчики BMP085/BMP180/BMP280/BME280)
#define SENS_PORT_ENABLE 1        //включить использование порта датчиков температуры DS18xx и DHTxx(0 - порт не используется | 1 - порт используется для DS18xx | 2 - порт используется для DHTxx | 3 - порт используется для DS18xx/DHTxx)
#define MOV_PORT_ENABLE 0         //включить использование порта датчика движения(0 - порт не используется | 1 - порт используется)
#define SQW_PORT_ENABLE 1         //включить использование порта и синхронизации по SQW(0 - порт и синхронизация не используются | 1 - порт и синхронизация используются)
#define IR_PORT_ENABLE 1          //включить использование порта инфракрасного приемника(0 - порт не используется | 1 - порт используется)
#define PCF8591_ENABLE 1          //включить использование портов PCF8591 (0 - порт не используется | 1 - порт используется)

//Настройки преобразователя
#define GEN_ENABLE 1              //включить генерацию шим для преобразователя высокого напряжения(нужно если используется внешний шим контроллер)(0 - внешний шим преобразователь | 1 - шим на стороне МК(пин D9))
#define GEN_FEEDBACK 1            //разрешить обратную связь вв преобразователя через делитель напряжения(0 - обратная связь не используется | 1 - обратная связь используется на АЦП | 2 - обратная связь используется на компараторе)
#define GEN_HV_VCC 170            //напряжение питания ламп(только для ОС на АЦП)(150..190)(в)
#define GEN_HV_R_HIGH 360         //сопротивление верхнего плеча резисторного делителя(только для ОС на АЦП)(кОм)
#define GEN_HV_R_LOW 4.7          //сопротивление нижнего плеча резисторного делителя(только для ОС на АЦП)(кОм)

#define DEFAULT_MIN_PWM 100       //минимальная скважность(индикаторы выключены, яркость минимальная)(100..190)(шаг 5)
#define DEFAULT_MAX_PWM 180       //максимальная скважность(индикаторы включены, яркость максимальная)(150..200)(шаг 5)

//Настройки сенсора яркости освещения
#define LIGHT_SENS_ENABLE 1       //включить сенсор яркости освещения(0 - сенсор не используется | 1 - сенсор используется)
#define LIGHT_SENS_PULL 0         //тип подтяжки сенсора яркости освещения(0 - сенсор подтянут к земле (LOW_PULL) | 1 - сенсор подтянут к питанию (HIGH_PULL))
#define LIGHT_SENS_TYPE 2         //вид подключения сенсор яркости освещения(1 - сенсор подключён к Arduino | 2 - сенсор подключён к PCF8591)

//Настройки кнопок
#define BTN_TYPE 1                //тип основных кнопок(0 - используются цифровые кнопки | 1 - используются аналоговые кнопки)
#define BTN_PULL 0                //тип подтяжки основных кнопок(0 - кнопки подтянуты к земле (LOW_PULL) | 1 - кнопки подтянуты к питанию (HIGH_PULL))

#define BTN_ADD_TYPE 3            //тип дополнительной кнопки(0 - кнопка не используется | 1 - цифровая кнопка | 2 - аналоговая кнопка(только если основные кнопки аналоговые)) | 3 - цифровая кнопка подключенная ко второму входу PCF8591
#define BTN_ADD_PULL 1            //тип подтяжки цифровой дополнительной кнопки(0 - кнопка подтянута к земле (LOW_PULL) | 1 - кнопка подтянута к питанию (HIGH_PULL))

#define BTN_EASY_MAIN_MODE 0      //режим упрощенного управления в режиме часов(0 - обычный режим управления | 1 - упрощенный режим управления)

//Настройки аналоговых кнопок
#define BTN_R_LOW 10              //сопротивление резистора нижнего плеча клавиш(кОм)
#define BTN_ADD_R_HIGH 57.7       //сопротивление резистора клавиши "ДОП"(полное сопротивление от кнопки до пина)(кОм)
#define BTN_SET_R_HIGH 4.7        //сопротивление резистора клавиши "ОК"(полное сопротивление от кнопки до пина)(кОм)
#define BTN_LEFT_R_HIGH 0         //сопротивление резистора "ЛЕВОЙ" клавиши(полное сопротивление от кнопки до пина)(кОм)
#define BTN_RIGHT_R_HIGH 37.7     //сопротивление резистора "ПРАВОЙ" клавиши(полное сопротивление от кнопки до пина)(кОм)

//Подключение аналоговых кнопок к порту МК (LOW_PULL)
//               __/ __VCC          __/ __VCC         __/ __VCC         __/ __VCC
//              |                  |                 |                 |
//  analog------|------|3.3K|------|------|6.8K|------|------|20K|------|
//              |
//             10K
//              |         
//             GND


//Основные настройки прошивки
#define DEFAULT_TIME_FORMAT 0      //формат времени по умолчанию(0 - 24 часа | 1 - 12 часов)
#define DEFAULT_KNOCK_SOUND 1      //звук нажатия клавиш(озвучки) по умолчанию(для бузера)(0 - звук выключен | 1 - звук включен)(для плеера)(0 - озвучка выключена | 1 - озвучка включена)
#define DEFAULT_VOICE_SOUND 1      //голос озвучки(только для DF и SD плеера)(0 - озвучка Алена | 1 - озвучка Филипп)(2..5 - пользовательская озвучка)
#define DEFAULT_TEMP_CORRECT 0     //коррекция температуры по умолчанию(-127..127)(1ед. - 0.1°c)(поддерживаются датчики - DS3231(встроенный), AHT10/AHT15/AHT20, SHT20/SHT21/SHT25/SHT30/SHT31/SHT35, BMP085/BMP180/BMP280/BME280, DHT11/DHT12/MW33, DHT21/DHT22(AM2301/AM2302), DS18B20/DS18S20/DS1820)
#define DEFAULT_BACKL_MODE 1       //режим подсветки по умолчанию для обычных светодиодов(0 - выкл | 1 - статичная | 2 - дыхание), для светодиодов WS2812B(0 - выкл | 1 - статичная | 2 - дыхание | 3 - дыхание со сменой цвета при затухании | 4 - бегущий огонь | 5 - бегущий огонь со сменой цвета | 6 - бегущий огонь с радугой | 7 - бегущий огонь с конфетти | 8 - волна | 9 - волна со сменой цвета | 10 - волна с радугой | 11 - волна с конфетти | 12 - плавная смена цвета | 13 - радуга | 14 - конфетти)
#define DEFAULT_BACKL_COLOR 0      //цвет подсветки по умолчанию(0..28)(26, 27, 28 - белый цвет)(только для светодиодов WS2812B)
#define DEFAULT_DOT_MODE 2         //режим работы точки по умолчанию(0..9)(описание ниже в таблице)

//Режимы секундных точек
//NEON_DOT 0..1 - (0 - выкл | 1 - статичная | 2 - мигает один раз в секунду | 3 - мигает два раза в секунду | 4 - динамичная(плавно мигает)), (для точек в индикаторах)(5 - мигающая | 6 - бегущая | 7 - змейка | 8 - резинка | 9 - одинарный маятник(только для 6-ти ламп или если используются левые и правые точки) | 10 - двойной маятник(только для 6-ти ламп и если используются левые и правые точки))
//NEON_DOT 2 - (0 - выкл | 1 - статичная | 2 - мигает один раз в секунду | 3 - мигает два раза в секунду | 4 - динамичная(плавно мигает) | 5 - маятник(мигает один раз в секунду) | 6 - маятник(плавно мигает)), (для точек в индикаторах)(7 - мигающая | 8 - бегущая | 9 - змейка | 10 - резинка | 11 - одинарный маятник(только для 6-ти ламп или если используются левые и правые точки) | 12 - двойной маятник(только для 6-ти ламп и если используются левые и правые точки))
//NEON_DOT 3 - (0 - выкл | 1 - статичная | 2 - мигает один раз в секунду | 3 - мигает два раза в секунду | 4 - мигающая | 5 - бегущая | 6 - змейка | 7 - резинка | 8 - одинарный маятник(только для 6-ти ламп или если используются левые и правые точки) | 9 - двойной маятник(только для 6-ти ламп и если используются левые и правые точки))

//Настройки анимации перелистования цифр
#define DEFAULT_SECONDS_ANIM 1     //режим анимации секунд по умолчанию(0 - выкл | 1 - плавное угасание и появление | 2 - перемотка по порядку числа | 3 - перемотка по порядку катодов в лампе)(только для 6-ти ламп)
#define SECONDS_ANIM_1_TIME 450    //период смены яркости эффекта анимации секунд 1(250..450)(мс)(только для 6-ти ламп)
#define SECONDS_ANIM_2_TIME 50     //скорость шага эффекта анимации секунд 2(50..80)(мс)(только для 6-ти ламп)
#define SECONDS_ANIM_3_TIME 50     //скорость шага эффекта анимации секунд 3(50..80)(мс)(только для 6-ти ламп)

#define DEFAULT_FLIP_ANIM 1        //режим анимации минут по умолчанию(0 - выкл | 1 - случайная смена эффектов | 2 - плавное угасание и появление | 3 - перемотка по порядку числа | 4 - перемотка по порядку катодов в лампе | 5 - поезд | 6 - резинка | 7 - ворота | 8 - волна | 9 - блики | 10 - испарение | 11 - игровой автомат)
#define FLIP_MODE_2_TIME 450       //период смены яркости эффекта "плавное угасание и появление"(250..1000)(мс)
#define FLIP_MODE_3_TIME 50        //скорость шага эффекта "перемотка по порядку числа"(50..80)(мс)
#define FLIP_MODE_4_TIME 50        //скорость шага эффекта "перемотка по порядку катодов в лампе"(50..80)(мс)
#define FLIP_MODE_5_TIME 180       //скорость шага эффекта "поезд"(50..200)(мс)
#define FLIP_MODE_5_STEP 1         //количество пустых разрядов эффекта "поезд"(0..4)
#define FLIP_MODE_6_TIME 80        //скорость шага эффекта "резинка"(50..200)(мс)
#define FLIP_MODE_7_TIME 200       //скорость шага эффекта "ворота"(100..300)(мс)
#define FLIP_MODE_8_TIME 200       //скорость шага эффекта "волна"(100..300)(мс)
#define FLIP_MODE_9_TIME 200       //скорость шага эффекта "блики"(100..300)(мс)
#define FLIP_MODE_10_TIME 200      //скорость шага эффекта "испарение"(100..300)(мс)
#define FLIP_MODE_11_TIME 30       //скорость шага эффекта "игровой автомат"(30..80)(мс)
#define FLIP_MODE_11_STEP 15       //увеличение шага эффекта "игровой автомат"(5..40)(мс)

#define FLIP_ANIM_RANDOM 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 //эффекты которые учавствуют в случайном режиме(2..11)
#define FLIP_ANIM_START 1          //режим анимации при запуске часов(0 - выкл | 1 - зависит от основной анимации | 2 - плавное угасание и появление | 3 - перемотка по порядку числа | 4 - перемотка по порядку катодов в лампе | 5 - поезд | 6 - резинка | 7 - ворота | 8 - волна | 9 - блики | 10 - испарение | 11 - игровой автомат)

//Настройки режима сна
#define DEFAULT_SLEEP_WAKE_TIME 0   //время ожидания после выхода из сна днем(0..90)(0 - дневной сон выключен)(шаг 15)(мин)
#define DEFAULT_SLEEP_WAKE_TIME_N 0 //время ожидания после выхода из сна ночью(0..30)(0 - ночной сон выключен)(шаг 5)(сек)

//Настройки часа смены общей яркости
#define DEFAULT_NIGHT_START 20     //час перехода на ночную подсветку по умолчанию(BRIGHT_N)(NIGHT_START = NIGHT_END - только дневная подсветка)
#define DEFAULT_NIGHT_END 8        //час перехода на дневную подсветку по умолчанию(BRIGHT)

//Настройки яркости индикаторов
#define DEFAULT_INDI_BRIGHT 25     //яркость цифр дневная по умолчанию(5..30)
#define DEFAULT_INDI_BRIGHT_N 5    //яркость цифр ночная по умолчанию(5..30)

//Настройки подсветки
#define DEFAULT_BACKL_BRIGHT 150   //яркость подсветки ламп дневная по умолчанию(10..250)(шаг 10)
#define DEFAULT_BACKL_BRIGHT_N 60  //яркость подсветки ламп ночная по умолчанию(0..250)(0 - подсветка выключена)(шаг 10)
#define BACKL_MIN_BRIGHT 20        //минимальная яркость подсветки ламп(10..120)
#define BACKL_REVERSE 0            //реверс порядка светодиодов WS2812B(0 - нормальное отображение | 1 - реверсивное отображение)(только для светодиодов WS2812B)

#define BACKL_MODE_2_TIME 5000     //период эффекта подсветки "дыхание"(1500..12000)(мс)
#define BACKL_MODE_2_PAUSE 200     //пазуа между вспышками подсветки ламп в режиме "дыхание"(100..1000)(мс)
#define BACKL_MODE_2_STEP_TIME 10  //минимальный размер шага яркости подсветки "дыхание"(4..50)(мс)
#define BACKL_MODE_3_COLOR 25      //шаг изменения цвета эффекта подсветки "дыхание со сменой цвета при затухании"(5..50)(только для светодиодов WS2812B)

#define BACKL_MODE_4_TIME 1000     //период эффекта подсветки "бегущий огонь"(1000..5000)(мс)(только для светодиодов WS2812B)
#define BACKL_MODE_4_FADING 5      //количество шагов декркминента яркости эффекта подсветки "бегущий огонь"(5..50)(только для светодиодов WS2812B)
#define BACKL_MODE_4_TAIL 3        //длинна эффекта подсветки "бегущий огонь"(1..4)(только для светодиодов WS2812B)

#define BACKL_MODE_8_TIME 5000     //период эффекта подсветки "волна"(1000..12000)(мс)(только для светодиодов WS2812B)
#define BACKL_MODE_8_STEP_TIME 10  //минимальный размер шага яркости эффекта подсветки "волна"(4..50)(мс)(только для светодиодов WS2812B)

#define BACKL_MODE_12_TIME 30      //скорость шага эффекта подсветки "плавная смена цвета"("бегущий огонь со сменой цвета", "волна со сменой цвета")(4..100)(мс)(только для светодиодов WS2812B)
#define BACKL_MODE_12_COLOR 1      //шаг изменения цвета эффекта подсветки "плавная смена цвета"("бегущий огонь со сменой цвета", "волна со сменой цвета")(1..10)(только для светодиодов WS2812B)

#define BACKL_MODE_13_TIME 80      //скорость шага эффекта подсветки "радуга"(4..100)(мс)(только для светодиодов WS2812B)
#define BACKL_MODE_13_STEP 15      //размер шага эффекта подсветки "радуга"(1..50)(только для светодиодов WS2812B)

#define BACKL_MODE_14_TIME 80      //скорость шага эффекта подсветки "конфетти"(4..100)(мс)(только для светодиодов WS2812B)

#define BACKL_MENU_COLOR_1 255     //цвет активных разрядов меню настроек(0..255)(только для светодиодов WS2812B)
#define BACKL_MENU_COLOR_2 0       //цвет неактивного разрядов меню настроек(0..255)(только для светодиодов WS2812B)

//Настройки секундных точек
#define DEFAULT_DOT_BRIGHT 50      //яркость точки дневная по умолчанию(10..250)(шаг 10)
#define DEFAULT_DOT_BRIGHT_N 20    //яркость точки ночная по умолчанию(0..250)(0 - точки выключены)(шаг 10)

#define DOT_PULS_TIME 250          //время мигания секундной точкии для анимации "динамичная" (100..1000)(мс)
#define DOT_PULS_STEP_TIME 4       //шаг яркости секундной точкии для анимации "динамичная" (4..10)(мс)

#define DOT_PULS_TURN_TIME 450     //время мигания секундной точки для анимации "маятник" двух неоновых ламп(100..1000)(мс)
#define DOT_PULS_TURN_STEP_TIME 4  //шаг яркости секундной точки для анимации "маятник" двух неоновых ламп(4..10)(мс)

#define DOT_BLINK_TIME 500         //время мигания секундных точек в индикаторах(100..500)(0 - один раз в секунду)(мс)(только для разделительных точек)
#define DOT_RUBBER_BAND_TIME 2800  //период анимации "резинка" для точек в индикаторах(1000..5000)(мс)(только для разделительных точек)
#define DOT_RUNNING_TIME 1000      //период анимации "бегущая точка" для точек в индикаторах(250..1000)(мс)(только для разделительных точек)
#define DOT_SNAKE_TIME 900         //период анимации "змейка" для точек в индикаторах(500..1000)(мс)(только для разделительных точек)
#define DOT_TURN_TIME 500          //время переключения точек в индикаторах для анимации "одинарный маятник"(100..500)(0 - один раз в секунду)(мс)(только для разделительных точек)
#define DOT_DUAL_TURN_TIME 500     //время переключения точек в индикаторах для анимации "двойной маятник"(100..500)(0 - один раз в секунду)(мс)(только для разделительных точек)

#define DOT_MAIN_BLINK_TIME 0     //время включения секундной точки для анимации "одиночное мигание"(100..500)(0 - один раз в секунду)(мс)
#define DOT_MAIN_DOOBLE_TIME 150  //время включения секундной точки для анимации "двойное мигание"(100..1000)(мс)

//Настройки глюков
#define DEFAULT_GLITCH_MODE 0      //режим глюков по умолчанию(1 - вкл | 0 - выкл)
#define GLITCH_MIN_TIME 40         //минимальное время между глюками(10..60)(сек)
#define GLITCH_MAX_TIME 160        //максимальное время между глюками(60..240)(сек)
#define GLITCH_TIME 20             //время одного глюка(4..25)(мс)
#define GLITCH_NUM_MIN 2           //минимальное количество глюков(1..4)
#define GLITCH_NUM_MAX 6           //максимальное количество глюков(4..15)
#define GLITCH_PHASE_MIN 10        //минимальная секунда начала отображения глюков(5..55)(сек)
#define GLITCH_PHASE_MAX 50        //максимальная секунда начала отображения глюков(5..55)(сек)

//Настройки анти-отравления
#define DEFAULT_BURN_MODE 2        //режим анимации антиотравления ламп по умолчанию(0 - перебор всех индикаторов | 1 - перебор одного индикатора | 2 - перебор одного индикатора с отображением времени)
#define BURN_PERIOD 30             //период отображения анимации антиотравления(10..180)(мин)
#define BURN_PHASE 0               //фаза отображения анимации антиотравления(необходимо учитывать фазу отображения автоматического показа температуры и анимации смены минут)(0..59)(сек)
#define BURN_TIME 40               //период обхода индикаторов в режиме очистки(10..240)(мс)
#define BURN_LOOPS 4               //количество циклов очистки за каждый период(1..10)
#define BURN_DOTS 1                //включать разделительные точки в индикаторах во время антиотравления(0 - точки выключенв | 1 - точки включены)
#define BURN_BRIGHT 0              //яркость индикаторов в режиме очистки(0..30)(0 - яркость индикаторов в режиме очистки зависит от общей яркости индикаторов)

//Настройки авто-показа
#define DEFAULT_AUTO_SHOW_TIME 1   //интервал автоматического показа температуры по умолчанию(0..15)(0 - выключить автоматический показ)(мин)
#define DEFAULT_AUTO_SHOW_ANIM 0   //режим анимации автоматического показа температуры по умолчанию(0 - режим зависит от основной анимации | 1 - случайная смена эффектов | 2 - плавное угасание и появление | 3 - перемотка по порядку числа | 4 - перемотка по порядку катодов в лампе | 5 - поезд | 6 - резинка | 7 - ворота | 8 - волна | 9 - блики | 10 - испарение | 11 - игровой автомат)
#define AUTO_SHOW_MODES 1, 4, 5, 6 //выбранные режимы отображения данных автоматического показа(указывать через запятую)(0 - пустая ячейка | 1 - дата | 2 - год | 3 - дата и год | 4 - температура | 5 - влажность | 6 - давление | 7 - температура и влажность)(не более 5 пресетов!)
#define AUTO_SHOW_TIMES 5, 5, 5, 5 //задержки выбранных режимов отображения данных автоматического показа(указывать через запятую)(1..5)(сек)(не более 5 пресетов!)
#define AUTO_SHOW_PHASE 30         //фаза отображения автоматического показа температуры(необходимо учитывать фазу отображения антиотравления и анимации смены минут)(0..59)(сек)

#define AUTO_SHOW_SIGN_TIME 300    //время мигания разделительной точки десятых градуса автоматического показа при отрицательной температуре(100..500)(мс)

#define AUTO_SHOW_BACKL_TYPE 1     //режим подсветки во время автоматического показа температуры(0 - всегда выключена | 1 - только когда включена основная подсветка | 2 - всегда включена)(только для светодиодов WS2812B)

//Настройки показа температуры/даты
#define SHOW_DATE_TYPE 3           //формат отображения даты(0 - ДД:ММ | 1 - ММ:ДД) и (2 - ДД:ММ:ГГ | 3 - ММ:ДД:ГГ)(только для 6-ти ламп)
#define SHOW_DATE_TIME 3000        //время отображения даты(1000..15000)(мс)

#define SHOW_DATE_BACKL_TYPE 1     //режим подсветки в меню даты(0 - всегда выключена | 1 - только когда включена основная подсветка | 2 - всегда включена)(только для светодиодов WS2812B)
#define SHOW_DATE_BACKL_NN 0       //цвет незначащих разрядов меню даты(0..255)(только для светодиодов WS2812B)
#define SHOW_DATE_BACKL_DM 210     //цвет меню дня недели и месяца(0..255)(только для светодиодов WS2812B)
#define SHOW_DATE_BACKL_YY 255     //цвет меню года(0..255)(только для светодиодов WS2812B)

#define SHOW_TEMP_TIME 3000        //время отображения температуры(влажности/давления)(1000..15000)(мс)
#define SHOW_SIGN_TIME 300         //время мигания разделительной точки десятых градуса при отрицательной температуре(100..500)(мс)

#define SHOW_TEMP_MAIN_SENS 0      //основной датчик для ручного отображения(только для esp)(0 - датчик в часах | 1 - датчик в есп)
#define SHOW_TEMP_CORRECT_MODE 1   //выбор датчика для коррекции температуры(только для esp)(0 - без коррекции | 1 - датчик в часах | 2 - датчик в есп)

#define SHOW_TEMP_BACKL_TYPE 1     //режим подсветки в меню температуры(0 - всегда выключена | 1 - только когда включена основная подсветка | 2 - всегда включена)(только для светодиодов WS2812B)
#define SHOW_TEMP_COLOR_T 170      //цвет меню температуры(0..255)(только для светодиодов WS2812B)
#define SHOW_TEMP_COLOR_P 0        //цвет меню давления(0..255)(только для светодиодов WS2812B)
#define SHOW_TEMP_COLOR_H 85       //цвет меню влажности(0..255)(только для светодиодов WS2812B)

//Настройки звука смены часа
#define DEFAULT_HOUR_SOUND_START 8 //время начала звука смены часа по умолчанию(0..23)(ч)(DEFAULT_HOUR_SOUND_START = DEFAULT_HOUR_SOUND_END - выключить звук)
#define DEFAULT_HOUR_SOUND_END 23  //время окончания звука смены часа по умолчанию(0..23)(ч)
#define DEFAULT_HOUR_SOUND_TYPE 0  //тип озвучивания текущего часа(0 - мелодия или озвучка(выбирается автоматически общей настройкой озвучки) | 1 - только мелодия | 2 - только озвучка | 3 - мелодия и озвучка)(только для SD/DF плеера)
#define DEFAULT_HOUR_SOUND_TEMP 0  //проговаривать текущую температуру во время озвучивания текущего часа(0 - озвучивается только текущий час | 1 - озвучивается текущий час и температура)(только для SD/DF плеера)

#define HOUR_SOUND_MAIN_SENS 0     //основной датчик для озвучки температуры при смене часа(только для esp)(0 - датчик в часах | 1 - датчик в есп)

//Настройки будильника
#define ALARM_TYPE 0               //тип будильника(0 - будильник не используется | 1 - один будильник | 2 - несколько будильников)

#define DEFAULT_ALARM_TIME_HH 8    //час будильника по умолчанию(0..23)
#define DEFAULT_ALARM_TIME_MM 0    //минута будильника по умолчанию(0..59)
#define DEFAULT_ALARM_MODE 0       //режим будильника по умолчанию(0..4)(0 - выкл, 1 - одиночный, 2 - включен всегда, 3 - по будням, 4 - по дням недели)
#define DEFAULT_ALARM_VOLUME 0     //громкость будильника по умолчанию(0..15)(0 - авто громкость)

#define ALARM_RADIO_CONTINUE 1     //продолжить работу радио после срабатывания радиобудильника(0 - радио перейдет в предыдущее состояние | 1 - радио продолжит работать после отключения тревоги будильника)

#define ALARM_TIMEOUT 15           //таймаут до полного отключения будильника по умолчанию(1..240)(м)
#define ALARM_WAIT_TIME 4          //время ожидание будильника для повторного включения сигнала по умолчанию(0..240)(0 - выкл ожидание по короткому нажатию)(мин)
#define ALARM_SOUND_TIME 1         //длительносить сигнала будильника до перехода в режим ожидания по умолчанию(0..240)(0 - выкл повторное включение сигнала)(мин)

#define ALARM_AUTO_VOL_MIN 0       //минимальная громкость будильника в авто режиме(0..15)
#define ALARM_AUTO_VOL_MAX 15      //максимальная громкость будильника в авто режиме(0..15)
#define ALARM_AUTO_VOL_TIME 30     //время за которое наберется полная громкость будильника(1..60)(сек)

#define ALARM_BLINK_TIME 500       //период мигания времени во время активного будильника(100..1000)(мс)

#define ALARM_ON_BLINK_DOT 3       //режим мигания точек если хоть один будильник включен(0..12)(описание ниже в таблице)
#define ALARM_WAIT_BLINK_DOT 4     //режим мигания точек если ожидаем повторного сигнала(0..12)(описание ниже в таблице)

//Режимы секундных точек
//NEON_DOT 0..1 - (0 - без реакции | 1 - выкл | 2 - статичная  | 3 - мигает один раз в секунду | 4 - мигает два раза в секунду| 5 - динамичная(плавно мигает)), (для точек в индикаторах)(6 - мигающая | 7 - бегущая | 8 - змейка | 9 - резинка | 10 - одинарный маятник(только для 6-ти ламп или если используются левые и правые точки) | 11 - двойной маятник(только для 6-ти ламп и если используются левые и правые точки))
//NEON_DOT 2 - (0 - без реакции | 1 - выкл | 2 - статичная  | 3 - мигает один раз в секунду | 4 - мигает два раза в секунду | 5 - динамичная(плавно мигает) | 6 - маятник(мигает один раз в секунду) | 7 - маятник(плавно мигает)), (для точек в индикаторах)(8 - мигающая | 9 - бегущая | 10 - змейка | 11 - резинка | 12 - одинарный маятник(только для 6-ти ламп или если используются левые и правые точки) | 13 - двойной маятник(только для 6-ти ламп и если используются левые и правые точки))
//NEON_DOT 3 - (0 - без реакции | 1 - выкл | 2 - статичная  | 3 - мигает один раз в секунду | 4 - мигает два раза в секунду | 5 - мигающая | 6 - бегущая | 7 - змейка | 8 - резинка | 9 - одинарный маятник(только для 6-ти ламп или если используются левые и правые точки) | 10 - двойной маятник(только для 6-ти ламп и если используются левые и правые точки))

#define ALARM_BACKL_TYPE 1         //режим подсветки во время тревоги будильника(0 - всегда выключена | 1 - выключена если ночная яркость подсветки ативирована | 2 - всегда включена)(только для светодиодов WS2812B)
#define ALARM_BACKL_COLOR 0        //цвет тревоги будильника(0..255)(только для светодиодов WS2812B)

//Настройки радиоприемника
#define RADIO_ENABLE 1             //включить поддержку радиоприемника(0 - радиоприемник не используется | 1 - радиоприемник используется)
#define RADIO_SLEEP_ENABLE 0       //разрешить работу радио во время сна(0 - всегда выключать | 1 - не выключать только днем | 2 - всегда не выключать)

#define DEFAULT_RADIO_STATIONS 877, 1025, 1057 //радиостанции по умолчанию(указывать через запятую)(не более 10 пресетов)(870..1080)(МГц * 10)

#define DEFAULT_RADIO_VOLUME 15    //громкость радио по умолчанию(0..15)
#define RADIO_MONO 0               //режим работы аудиовыхода(0 - стерео | 1 - моно)
#define RADIO_BASS 1               //усиление низких частот(0 - без усиления | 1 - с усилением)
#define RADIO_SEEK_SNR 8           //пороговое значение SNR для системы автопоиска станций(0..15)

#define RADIO_STATUS_DOT_TYPE 1    //тип индикации устойчивого сигнала радиостанции(0 - отключить индикацию | 1 - неоновая лампа | 2 - точка в индикаторе)

#define RADIO_BACKL_TYPE 1         //режим подсветки в меню радио(0 - всегда выключена | 1 - только когда включена основная подсветка | 2 - всегда включена)(только для светодиодов WS2812B)
#define RADIO_BACKL_COLOR_1 255    //цвет активных разрядов меню радио(0..255)(только для светодиодов WS2812B)
#define RADIO_BACKL_COLOR_2 0      //цвет неактивных разрядов меню радио(0..255)(только для светодиодов WS2812B)
#define RADIO_BACKL_COLOR_3 170    //цвет дополнительных разрядов меню радио(0..255)(только для светодиодов WS2812B)

//Настройки плеера
#define DEFAULT_PLAYER_VOLUME 7    //громкость звуков плеера по умолчанию(0..15)
#define PLAYER_VOICE_MAX 2         //максимум голосов озвучки(1..5)
#define PLAYER_ALARM_MAX 3         //количество треков будильника(1..99)

//Настройки таймера
#define TIMER_ENABLE 0             //включить поддержку таймера/секундомера(0 - таймер/секундомер не используется | 1 - таймер/секундомер используется)
#define TIMER_TIME 60              //значение таймера по умолчанию(1..5999)(с)

#define TIMER_WARN_BACKL_TYPE 1    //режим подсветки во время тревоги таймера(0 - всегда выключена | 1 - выключена если ночная яркость подсветки ативирована | 2 - всегда включена)(только для светодиодов WS2812B)
#define TIMER_WARN_COLOR 255       //цвет тревоги таймера(0..255)(только для светодиодов WS2812B)

#define TIMER_BACKL_TYPE 1         //режим подсветки в меню таймера(0 - всегда выключена | 1 - только когда включена основная подсветка | 2 - всегда включена)(только для светодиодов WS2812B)
#define TIMER_PAUSE_COLOR 40       //цвет паузы таймера/секундомера(0..255)(только для светодиодов WS2812B)
#define TIMER_STOP_COLOR 0         //цвет остановки таймера/секундомера(0..255)(только для светодиодов WS2812B)
#define TIMER_RUN_COLOR_1 170      //цвет активного секундомера(0..255)(только для светодиодов WS2812B)
#define TIMER_RUN_COLOR_2 85       //цвет активного таймера(0..255)(только для светодиодов WS2812B)

#define TIMER_MENU_COLOR_1 255     //цвет активных разрядов меню таймера(0..255)(только для светодиодов WS2812B)
#define TIMER_MENU_COLOR_2 0       //цвет неактивных разрядов меню таймера(0..255)(только для светодиодов WS2812B)

#define DISABLE_SOME_FLIP_EFFECTS 1 // отключает часть эффектов анимации для уменьшения размера прошивки (освобождает 1480 байт)
#define DISABLE_SOME_BACKL_EFFECTS 1// отключает часть эффектов подсветки для уменьшения размера прошивки (освобождает 862 байта)
#define DISABLE_SOME_DOT_EFFECTS 1  // отключает часть эффектов точек для уменьшения размера прошивки (освобождает 44 байта)
