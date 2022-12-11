# <p align="center">Страница проекта [NixieClock](https://community.alexgyver.ru/threads/chasy-na-gri-v2-alternativnaja-proshivka.5843/) на форуме.</p> 

![Sheet_2](https://user-images.githubusercontent.com/71728333/174530369-60ad7431-a8fc-4c99-abe0-559c530fc2a1.png)

Для более точной работы часов желательно подключить пин SQW модуля DS3231 к пину ардуино D2, если у вас модуль DS3231mini, то необходимо найти 3-ю ножку микросхемы и также проводком подпаять к пину D2.

Настройка секундных точек:

    NEON_DOT 0 - Обычная светодиодная секундная точка(пин подключения указывается в DOT_PIN)(возможно комбинирование с точками в индикаторах)
    NEON_DOT 1 - Одна неоновая лампа в качестве секундной точки(пин подключения указывается в DOT_PIN)(возможно комбинирование с точками в индикаторах)
    NEON_DOT 2 - Две неоновые лампы в качестве секундных точек(пин подключения указывается в DOTL_PIN и DOTR_PIN)(комбинирование с точками в индикаторах невозможно)
    NEON_DOT 3 - Точки в индикаторах в качестве секундных точек(пин подключения указывается в DOTL_PIN и DOTR_PIN)

Если нет возможности подключить пин SQW, то можно его отключить - в "userConfig.h" - SQW_PORT_ENABLE.

Так-же не забудьте выбрать свою плату - в "userConfig.h" - BOARD_TYPE.
Для других плат на 4 лампы используйте - BOARD_TYPE 3, на 6 ламп - BOARD_TYPE 4.
Маски дешефратора и порядок катодов указываются в "config.h".

Если по какой-то причине нету сигнала от SQW, то часы при старте перейдут на внутренний источник тактирования и по возможности будут синхронизироваться с модулем часов. Так-же во время работы сигнал проверяется на длительность, если он выйдет за рамки, то часы перейдут на внутреннее тактирование.

Для сброса настроек - необходимо зажать среднюю кнопку и подать питание на часы.
Для запуска меню отладки - необходимо зажать левую кнопку и подать питание на часы.
Для запуска теста системы(ламп тест) - необходимо зажать правую кнопку и подать питание на часы.

Если возникла какая-то ошибка, то при старте часов будет длинный писк и отобразится код ошибки:

    0001 - Нет связи с модулем DS3231(модуль часов неисправен или проблемы с шиной i2c).
    0002 - Ошибка осциллятора DS3231(батарейка модуля часов разряжена или проблемы с тактированием модуля часов).
    0003 - Ошибка слишком короткий сигнал SQW(во время работы часов были обнаружены помехи или неверный сигнал на SQW).
    0004 - Ошибка слишком длинный сигнала SQW(пропал сигнал SQW во время работы часов).
    0005 - Выбранный датчик температуры не обнаружен(проверить подключение датчика температуры).
    0006 - Слишком низкое или слишком высокое напряжение питания(проверить источник питания).
    0007 - Ошибка памяти еепром(повреждение данных, если ошибка будет повторятся слишком часто - износ еепром).
    0008 - Ошибка софтовой перезагрузки(говорит о нестабильности программы).
         
Что планируется:

    Добавить поддержку модуля ESP-01 для настройки через веб интерфейс.

    
Что поддерживается:
Периферия:
    
    Датчики температуры DHT11/DHT12/MW33/DHT21/DHT22(AM2301/AM2302), DS18B20/DS18S20/DS1820 - по умолчанию подключаются к пину D1 с подтяжкой 4.7-10кОм к +5в.
    Датчик температуры BME280(BMP085/180/280) - подключается к пинам A4 и A5 параллельно модулю часов.
    Датчик температуры SHT20(SHT21/SHT25), SHT30(SHT31/SHT35) - подключается к пинам A4 и A5 параллельно модулю часов.
    Датчик температуры DS3231 - встроеный в модуль часов реального времени.
    Синхронизация времени по SQW - подключается к пину D2.
    Управление разделительными точками в индикаторах ИН12Б/14 - по умолчанию левые(основные) подключаются к пину D0, правые(дополнительные) к пину D1.
    Радиоприёмник RDA5807M - подключается к пинам A4 и A5 параллельно модулю часов.
    Неоновая секундная точка(одна или две) - по умолчанию подключается к пину D10(для каждой точки используется свой пин).
    Бузер(Для будильника и оповещений) - по умолчанию подключается к пину D13.
    Подсветка на адресных светодиодах WS2812B - по умолчания подключается к D11.
    Подсветка на обычных светодиодах - по умолчания подключается к D11(С софт. шимом можно выбрать любой пин).
    Дополнительная цифровая кнопка для управления таймером - секундомером - по умолчанию подключается к D0.
    Преобразователь ВВ напряжения(Затвор мосфета) - подключается к пину D9.
    Аналоговые кнопки(в т.ч. и дополнительная) - по умолчанию подключаются к A7.
    Обратная связь преобразователя ВВ напряжения на резистивном делителе - по умолчанию подключается к A6.
    Озвучка на DF player - по умолчанию подключается к D1/D0.
    Озвучка на SD карте - по умолчанию подключается к D13/D12/D11/D9 и пин D10 для вывода звука.
    Управление питание усилителя - по умолчанию подключается к D8.
    Приемник ИК пульта(Пульты только с протоколом NEC) - по умолчанию подключается к D7.
    Датчик яркости освещения - по умолчанию подключаются к A7.
    Датчик движения - по умолчанию подключается к D8.


Программно:
    
    Поддержка часов на 4/6 ламп.
    12/24 часовой формат времени.
    Будильник(Один или несколько).
    Радиобудильник(При наличии модуля радио).
    Автоматическое определение подключенного датчика температуры.
    Термометр(Гигрометр/Барометр для датчиков BME/BMP/DHT/SHT).
    Авто-показ температуры.
    Отображение текущей даты.
    Меню настройки яркости и др. функций.
    Быстрое меню для смены анимации перелистывания/точек/подсветки.
    Таймер - секундомер(Только при наличии доп. кнопки).
    Радиоприёмник(Только при наличии доп. кнопки).
    Антиотравление ламп(3 варианта анимации, выбор из меню).
    Мелодия смены часа.
    Смена яркости по времени и по датчику освещённости.
    Анимация глюков.
    10 режимов анимации минут(Есть случайный режим).
    3 режима анимации секунд для 6-ти ламп(Выбор из меню).
    3 режима подсветки для обычных диодов и 15 для адресных WS2812B.
    3 режима работы секундных точек и доп.режимы для отображения состояния будильника.
    Возможность создания собственных мелодий будильника.
    Система контроля основных параметров часов(Ошибки).
    Меню отладки(Для опытных пользователей).
    Озвучка пунктов меню, времени и температуры.
    Программирование кнопок ИК пульта из меню отладки.
    Режим сна(Октлючение ламп через заданное время)


Отладка: Удерживать "левую" кнопку при включении питания

    Клик по "средней кнопке" - выбор пункта отладки
    Клик по "левой кнопке" - уменьшить значение
    Клик по "правой кнопке" - увеличить значение
    Удержать "среднюю кнопку" - выход к часам

Пункты отладки:

    01 - Коррекция хода часов DS3231(0..255)(128 = 0)
    02 - Коррекция хода внутреннего осциллятора(Коррекция (2000..4000)(мкс))
    03 - Минимальное значение шим(Для линейной регулировки)(100..150)
    04 - Максимальное значение шим(Для линейной регулировки)(150..200)
    05 - Коррекция напряжения преобразователя(Для регулировки по обратной связи)(Внимание! Значение может меняться в зависимости от напряжения питания)(+-30)
    06 - Программирование кнопок ИК пульта(Поддерживаются пульты только с протоколом NEC)(1..8)
    07 - Калибровка датчика освещенности(Автоматическое определение диапазона)
    08 - Сброс настроек отладки(0..1)(0 - отмена | 1 - подтверждение)

Ввод пароля:

    Клик по "средней кнопке" - переход между разрядами
    Клик по "левой кнопке" - уменьшить значение
    Клик по "правой кнопке" - увеличить значение
    Удержать "среднюю кнопку" - подтвердить ввод пароля

Управление:
Настройка времени: Удерживать "правую" кнопку

    Средняя кнопка - выбор, остальные "меньше" и "больше"
    Клик по "выбору" - смена настройки часы/минуты | месяц/дата | год
    Клик "меньше" или "больше" - изменение времени/даты
    Удержать "выбор" - возврат к режиму часов
    
Настройка будильника:  Удерживать "левую" кнопку
Настройка нескольких будильников "ALARM_TYPE 2":

В режиме часов удержание левой клавиши – переход к настройке будильников.
После входа в настройку:

    В левых двух разрядах отображается текущий номер будильника (0 – нет будильников).
    В четвёртом разряде отображается текущий режим будильника (если будильников нет – ничего не отображается).

Экран «Выбор номера будильника»
Нажатие на:

    Правую клавишу – увеличивает значение.
    Левую клавишу – уменьшает значение.
    Среднюю клавишу - переход к настройке выбранного будильника.

Удержание:

    Правой клавиши – добавить новый будильник.
    Левой клавиши – удалить текущий будильник.
    Средней клавиши – выход к режиму часов.

После перехода к настройке будильника:

    Средняя кнопка - выбор, остальные "меньше" и "больше".
    Клик по "выбору" - перемещение по индикаторам.
    Клик "меньше" или "больше" - изменение значений.
    Удержать "меньше" или "больше" - смена настройки часы/минуты -> режим -> день недели/активация -> громкость(для плеера)/мелодия.
    Удержать "выбор" - возврат к выбору будильника.
    Удержать "доп. кнопку" - переключить режим мелодия/радио.

Настройка одного будильника "ALARM_TYPE 1":

В режиме часов удержание левой клавиши – переход к настройке будильников.
После входа в настройку:

    Средняя кнопка - выбор, остальные "меньше" и "больше".
    Клик по "выбору" - перемещение по индикаторам.
    Клик "меньше" или "больше" - изменение значений.
    Удержать "меньше" или "больше" - смена настройки часы/минуты -> режим -> день недели/активация -> громкость(для плеера)/мелодия.
    Удержать "выбор" - возврат к режиму часов.
    Удержать "доп. кнопку" - переключить режим мелодия/радио.
    
Режимы будильника:

    00 - выключен
    01 - однократный
    02 - каждый день
    03 - по будням
    04 - выбор по дням недели

Как добавить свои мелодии будильника:

Для начала нужно создать новый массив мелодии и прописать его в основном массиве всех мелодий:

    const uint16_t _sound_2[][3] PROGMEM = { //массив семплов 2-й мелодии будильника || семпл - частота(10..10000)(Hz) | длительность звука(50..500)(ms) | длительность паузы(50..1000)(ms)
    };

    const uint16_t alarm_sound[][2] = {  //массив мелодий будильника
      SOUND_PATTERN(_sound_1),
      SOUND_PATTERN(_sound_2)
    };

Затем в массив добавить патерны:

    const uint16_t _sound_2[][3] PROGMEM = { //массив семплов 2-й мелодии будильника || семпл - частота(10..10000)(Hz) | длительность звука(50..500)(ms) | длительность паузы(50..1000)(ms)
       {392, 700, 700}, //можно добавлять n-е количество
    };

Патерн состоит из 3-х значений:

    const uint16_t _sound_2[][3] PROGMEM = { //массив семплов 2-й мелодии будильника || семпл - частота(10..10000)(Hz) | длительность звука(50..500)(ms) | длительность паузы(50..1000)(ms)
    {/*Частота звука*/, /*Длительность звука*/, /*Пауза звука*/},
    };

    Частота звука(в герцах)
    Длительность звука(в мс)
    Пауза звука между патернами(в мс):
    Если равно длительности звука: паузы не будет.
    Если больше: пауза звука = (пауза звука - длительность звука).
    
Основные настройки: Удерживать "среднюю" кнопку

    Средняя кнопка - выбор, остальные "меньше" и "больше"
    Клик по "выбору" - переход в пункт меню для настройки/выход к выбору пункта меню
    Клик "меньше" или "больше" - выбор пункта меню
    Удержать "выбор" - возврат к режиму часов
    Удержать "меньше" или "больше" - выбор подпункта меню.

Пункты меню:
    
    01 - Формат времени (12ч | 24ч)
    02 - Глюки вкл/выкл (0 - выкл | 1 - вкл)
    03 - Звук кнопок вкл/выкл (0 - выкл | 1 - вкл : Громкость озвучки)
    04 - Время звука смены часа(Начало : Конец)
    05 - Время смены подсветки(Ночь : День)
    06 - Яркость индикаторов(Ночь : День)
    07 - Яркость подсветки(Ночь : День)
    08 - Яркость секундных точек(Ночь : День)
    09 - Настройка датчика температуры(Коррекция : Сенсор)
    10 - Настройка интервала автоматического отображения температуры(время в секундах 0..240)
    11 - Выбор анимации антиотравления индикаторов(антиотравление : анимация секунд)
    12 - Установка времени ожидания после выхода из сна(Ночь : День)

Таймер/секундомер: Клик по "дополнительной" кнопке

    Клик по "дополнительной кнопке" - пуск/пауза
    Клик по "средней кнопке" - вход в настройку таймера(только в режиме таймера)
    Клик по "левой кнопке" или Удержать "левую кнопку" - режим секундомера
    Клик по "правой кнопке" или Удержать "правую кнопку" - режим таймера
    Удержать "дополнительной кнопку" - сброс таймера/секундомера
    Удержать "среднюю кнопку" - возврат к режиму часов(таймер продолжает работать в фоне, секундомер ставится на паузу)

Настройка таймера: В режиме таймера - Клик по "средней кнопке"

    Клик по "средней кнопке" - переключение разрядов ММ:СС(максимум 99:59)
    Клик по "левой кнопке" - уменьшить значение
    Клик по "правой кнопке" - увеличить значение
    Удержать "среднюю кнопку" или Удержать "дополнительной кнопку" - выход к таймеру

Радиоприёмник: Удерживать "дополнительную" кнопку
    
    Клик по "дополнительной кнопке" - переключить ячейку памяти радиостанций
    Клик по "средней кнопке" - настройка громкости(повторный клик по "средней кнопке" - выход к часам(радио останется включенным))
    Клик по "левой/правой кнопке" - изменить текущую частоту
    Удержать "дополнительной кнопку" - записать в текущую ячейку памяти текущую частоту
    Удержать "среднюю кнопку" - выход к часам(радио выключится)
    Удержать "левую/правую кнопку" - авто поиск станций вниз/вверх


Управление кнопками В РЕЖИМЕ ЧАСОВ:

Клик по "правой" кнопке отображает текущую дату, затем клик по "правой" кнопке переключает дату/год.

Клик по "средней" кнопке отображает текущий режим подсветки.

    Клик по "правой" кнопке - переключает режим анимации цифр(0 - выкл, 1 - случайная анимация, 2 - плавное угасание и появление , 3 - перемотка по порядку числа, 4 - перемотка по порядку катодов в лампе, 5 - поезд, 6 - резинка, 7 - ворота, 8 - волна, 9 - блики, 10 - испарение | 11 - игровой автомат)
    Клик по "средней" кнопке(для обычных светодиодов) - переключает режим подсветки(0 - выкл | 1 - статичная | 2 - динамичная(дыхание))
    Клик по "средней" кнопке(для адресных светодиодов) - переключает режим подсветки(0 - выкл | 1 - статичная | 2 - дыхание | 3 - дыхание со сменой цвета при затухании | 4 - бегущий огонь | 5 - бегущий огонь со сменой цвета | 6 - бегущий огонь с радугой | 7 - бегущий огонь с конфетти | 8 - волна | 9 - волна со сменой цвета | 10 - волна с радугой | 11 - волна с конфетти | 12 - плавная смена цвета | 13 - радуга | 14 - конфетти)
    Удержание "средней" кнопки во время отображения режима подсветки(для адресных светодиодов) - переводит в режим установки цвета, выбор цвета осуществляется "левой" и "правой" кнопками(войти можно только в режимах поддерживающих смену цвета - статичная, дыхание, бегущий огонь, волна)
    Клик по "левой" кнопке - переключает режим точек(0 - выкл | 1 - статичная | 2 - динамичная(плавно мигает))(только для точек в индикаторах)(3 - бегущая | 4 - маятник)

Клик по "левой" кнопке отображает текущую температуру, затем клик по "левой" кнопке переключает температуру/давление/влажность.
