# <p align="center">Страница проекта [NixieClock](https://community.alexgyver.ru/threads/chasy-na-gri-v2-alternativnaja-proshivka.5843/) на форуме.</p> 

![Sheet_2](https://user-images.githubusercontent.com/71728333/174530369-60ad7431-a8fc-4c99-abe0-559c530fc2a1.png)

Для более точной работы часов желательно подключить пин SQW модуля DS3231 к пину ардуино D2, если у вас модуль DS3231mini, то необходимо найти 3-ю ножку микросхемы и также проводком подпаять к пину D2.

Для настройки прошивки под другую разводку плат, отличающуюся от "Часов на ГРИ v2", необходимо указать пины подключения периферии в "connection.h" и настроить используемую периферию в "userConfig.h", "config.h".

Так-же не забудьте выбрать свою плату в "userConfig.h" - BOARD_TYPE.

Для других ламп(плат) используйте - BOARD_TYPE 3.

Маска дешефратора и порядок катодов указываются в "config.h".

    Для сброса настроек - необходимо зажать среднюю кнопку и подать питание на часы.
    Для запуска меню отладки - необходимо зажать левую кнопку и подать питание на часы.
    Для запуска теста системы(ламп тест) - необходимо зажать правую кнопку и подать питание на часы.

Если по какой-то причине отсутсвует сигнал с SQW, то часы при старте перейдут на внутренний источник тактирования и по возможности будут синхронизироваться с модулем часов. Так-же во время работы сигнал проверяется на длительность, если он выйдет за рамки, то часы перейдут на внутреннее тактирование.

Если возникла какая-то ошибка, то при старте часов будет длинный писк и отобразится код ошибки:

    0001 - Нет связи с модулем DS3231(модуль часов неисправен или проблемы с шиной i2c).
    0002 - Ошибка осциллятора DS3231(батарейка модуля часов разряжена или проблемы с тактированием модуля часов).
    0003 - Ошибка слишком короткий сигнал SQW(во время работы часов были обнаружены помехи или неверный сигнал на SQW).
    0004 - Ошибка слишком длинный сигнала SQW(пропал сигнал SQW во время работы часов или сигнал отсутствовал при запуске).
    0005 - Выбранный датчик температуры не обнаружен(проверить подключение датчика температуры).
    0006 - Слишком низкое или слишком высокое напряжение питания(проверить источник питания).
    0007 - Ошибка памяти еепром(повреждение данных, если ошибка будет повторятся слишком часто - износ еепром).
    0008 - Ошибка софтовой перезагрузки(говорит о нестабильности программы или об аппаратных проблемах с мк).
    0009 - Ошибка сбоя работы преобразователя(регистры таймера были неожиданно изменены).
    0010 - Ошибка переполнения заполнения шим преобразователя(превышен верхний предел заполнения шим).
    0011 - Ошибка переполнения стека(утечка памяти).
    0012 - Ошибка переполнения тиков времени(основная программа не отвечает).
    0013 - Ошибка сбоя работы динамической индикации(регистры таймера были неожиданно изменены или превышен предел регистра сравнения).

Настройка секундных точек:

    NEON_DOT 0 - Обычная светодиодная секундная точка(пин подключения указывается в DOT_PIN)(возможно комбинирование с точками в индикаторах)
    NEON_DOT 1 - Одна неоновая лампа в качестве секундной точки(пин подключения указывается в DOT_PIN)(возможно комбинирование с точками в индикаторах)
    NEON_DOT 2 - Две неоновые лампы в качестве секундных точек(пин подключения указывается в DOT1_PIN и DOT2_PIN)(возможно комбинирование с точками в индикаторах)
    NEON_DOT 3 - Точки в индикаторах в качестве секундных точек(пин подключения указывается в DOTL_PIN и DOTR_PIN)

Пины подключения периферии к сдвиговому регистру указываются в connection.h: ANODE_1_PIN..ANODE_6_PIN, DOTL_PIN, DOTR_PIN, DOT_1_PIN, DOT_2_PIN. Доступные номера пинов 0..7.

    Аноды ламп.
    Разделительные точки в индикаторах.
    Две раздельные неоновые лампы.
    Одну неоновую лампу.

При использовании сдвигового регистра есть ограничения на пины D13-D10, а именно:

    D13 может быть использован только как пин сдвигового регистра - SCK.
    D12 может быть использован для остальной периферии в качестве входа(цифровые кнопки, датчик движения, ИК приёмник, BUSY DF плеера, MISO SD карты).
    D11 может быть использован только как пин сдвигового регистра - DATA.
    D10 может быть использован для остальной периферии в качестве выхода(ВВ преобразователь, секундные точки, подсветка, бузер, управление питанием усилителя, RX DF плеера при использовании софтового UART, MOSI/SCK/CS SD карты, защёлка сдвигового регистра).

    
Протестированные чипы DFPlayer:

    Поддерживаются:
        MH2024K-24
        GD3200B
        YX5200-24

    Не поддерживаются:
        MH2024K-16
        AS21CN27OC
         
Что планируется:

    Добавить поддержку модуля ESP-01 для настройки через веб интерфейс.
    Добавить возможность отображать температуру со второго датчика температуры.
    Добавить анимации перехода подсветки на адресных светодиодах.

    
Что поддерживается:
Периферия:
    
    Датчики температуры DHT11/DHT12/MW33/DHT21/DHT22(AM2301/AM2302), DS18B20/DS18S20/DS1820 - доступные пины подключения(D0..D13) с подтяжкой 4.7-10кОм к +5в.
    Датчик температуры BME280(BMP085/180/280) - доступные пины подключения(A4 и A5) параллельно модулю часов.
    Датчик температуры SHT20(SHT21/SHT25), SHT30(SHT31/SHT35) - доступные пины подключения(A4 и A5) параллельно модулю часов.
    Датчик температуры DS3231 - встроенный в модуль часов реального времени.
    Синхронизация времени по SQW - доступные пины подключения(D2).
    Управление разделительными точками в индикаторах ИН12Б/14/16 - доступные пины подключения(D0..D13), для каждой точки используется свой пин.
    Радиоприёмник RDA5807M - доступные пины подключения(A4 и A5) параллельно модулю часов.
    Неоновая секундная точка(одна или две) - доступные пины подключения(D0..D13), для каждой точки используется свой пин.
    Бузер(Для будильника и оповещений) - доступные пины подключения(D0..D13).
    Подсветка на адресных светодиодах WS2812B - доступные пины подключения(D0..D13).
    Подсветка на обычных светодиодах - доступные пины подключения(D11), с софт. шимом(D0..D13).
    Дополнительная цифровая кнопка для управления таймером - секундомером - доступные пины подключения(D0..D13).
    Преобразователь ВВ напряжения(Затвор мосфета) - доступные пины подключения(D9..D10).
    Аналоговые кнопки(в т.ч. и дополнительная) - доступные пины подключения(A6..A7).
    Обратная связь преобразователя ВВ напряжения на резистивном делителе(АЦП или компаратор) - доступные пины подключения(для АЦП)(A6..A7)(для компаратора)(только пин D7).
    Озвучка на DF player - доступные пины подключения указаны в прошивке.
    Озвучка на SD карте - доступные пины подключения указаны в прошивке.
    Управление питание усилителя - доступные пины подключения(D0..D13).
    Приемник ИК пульта(Пульты только с протоколом NEC) - доступные пины подключения(D0..D13).
    Датчик яркости освещения - доступные пины подключения(A6..A7).
    Датчик движения - доступные пины подключения(D0..D13).
    Сдвиговый регистр для управления анодами ламп и разделительными точками(неоновыми лампами) - доступные пины подключения указаны в прошивке.


Программно:
    
    Поддержка часов на 4/6 ламп.
    12/24 часовой формат времени.
    Будильник(Один или несколько).
    Радиобудильник(При наличии модуля радио).
    Автоматическое определение подключенного датчика температуры.
    Термометр(Гигрометр/Барометр для датчиков BME/BMP/DHT/SHT).
    Авто-показ температуры(Влажности/Давления).
    Отображение текущей даты.
    Меню настройки яркости и др. функций.
    Быстрое меню для смены анимации перелистывания/точек/подсветки.
    Таймер - секундомер(Только при наличии доп. кнопки).
    Радиоприёмник(Только при наличии доп. кнопки).
    Антиотравление ламп(3 варианта анимации, выбор из меню).
    Мелодия смены часа.
    Смена яркости по времени и по датчику освещённости.
    Анимация глюков.
    10 режимов анимации авто-показа температуры(Есть случайный режим).
    10 режимов анимации минут(Есть случайный режим).
    3 режима анимации секунд для 6-ти ламп(Выбор из меню).
    3 режима подсветки для обычных диодов и 15 для адресных WS2812B.
    3 режима работы секундных точек (1 режим для двух неоновых ламп / 4 режима разделительных точек) и доп.режимы для отображения состояния будильника.
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

    01 - Коррекция хода часов DS3231(Коррекция (0..255)(128 = 0))
    02 - Коррекция хода внутреннего осциллятора(Коррекция (+-400)(мкс))
    03 - Минимальное значение шим(Для линейной регулировки)(100..190)
    04 - Максимальное значение шим(Для линейной регулировки)(150..200)
    05 - Коррекция напряжения преобразователя(Для регулировки по обратной связи)(Внимание! Значение может меняться в зависимости от напряжения питания)(+-30)
    06 - Программирование кнопок ИК пульта(Поддерживаются пульты только с протоколом NEC)(1..13)
    07 - Калибровка датчика освещенности(Автоматическое определение диапазона)
    08 - Сброс настроек отладки(0..1)(0 - отмена | 1 - подтверждение)
    
Кнопки пульта:

    1 - Левая клик.
    2 - Левая удержание.
    3 - Правая клик.
    4 - Правая удержание.
    5 - Средняя клик.
    6 - Средняя удержание.
    7 - Доп.кнопка клик.
    8 - Доп.кнопка удержание.
    9 - Вкл/выкл питание радио.
    10 - Прибавить громкость радио.
    11 - Убавить громкость радио.
    12 - Переключить на следующую радиостанцию.
    13 - Переключить на предыдущую радиостанцию.

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
    Удержать "меньше" или "больше" - смена настройки часы/минуты -> режим -> день недели/активация -> громкость(для плеера/радио)/мелодия.
    Удержать "выбор" - возврат к выбору будильника.
    Удержать "доп. кнопку" - переключить режим мелодия/радио.

Настройка одного будильника "ALARM_TYPE 1":

В режиме часов удержание левой клавиши – переход к настройке будильников.
После входа в настройку:

    Средняя кнопка - выбор, остальные "меньше" и "больше".
    Клик по "выбору" - перемещение по индикаторам.
    Клик "меньше" или "больше" - изменение значений.
    Удержать "меньше" или "больше" - смена настройки часы/минуты -> режим -> день недели/активация -> громкость(для плеера/радио)/мелодия.
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
    10 - Настройка интервала и анимации автоматического отображения температуры(время в минутах 0..15 : анимация)(0 - выключить)
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
    Клик по "средней кнопке" - настройка громкости(текущая громкость):
        Клик по "левой/правой кнопке" - изменить громкость.
        Клик по "средней кнопке" - выход к часам(радио останется включенным).
        Клик по "дополнительной кнопке" - вернуться к радио.
    Клик по "левой/правой кнопке" - изменить текущую частоту
    Удержать "дополнительной кнопку" - настройка ячеек памяти радиостанций(запись в ячейке : номер ячейки):
        Клик по "левой/правой кнопке" - выбрать номер ячейки.
        Клик по "дополнительной кнопке" - сохранить текущую частоту в выбранную ячейку.
        Удержать "дополнительной кнопку" - удалить данные из выбранной ячейки.
    Удержать "среднюю кнопку" - выход к часам(радио выключится)
    Удержать "левую/правую кнопку" - авто поиск станций вниз/вверх


Управление кнопками В РЕЖИМЕ ЧАСОВ:

    Клик по "правой" кнопке отображает текущую дату, затем клик по "правой" кнопке переключает дату/год.
    Клик по "средней" кнопке отображает текущий режим подсветки.
        Клик по "правой" кнопке - переключает режим анимации цифр(0 - выкл, 1 - случайная анимация, 2 - плавное угасание и появление , 3 - перемотка по порядку числа, 4 - перемотка по порядку катодов в лампе, 5 - поезд, 6 - резинка, 7 - ворота, 8 - волна, 9 - блики, 10 - испарение | 11 - игровой автомат)
        Клик по "средней" кнопке(для обычных светодиодов) - переключает режим подсветки(0 - выкл | 1 - статичная | 2 - динамичная(дыхание))
        Клик по "средней" кнопке(для адресных светодиодов) - переключает режим подсветки(0 - выкл | 1 - статичная | 2 - дыхание | 3 - дыхание со сменой цвета при затухании | 4 - бегущий огонь | 5 - бегущий огонь со сменой цвета | 6 - бегущий огонь с радугой | 7 - бегущий огонь с конфетти | 8 - волна | 9 - волна со сменой цвета | 10 - волна с радугой | 11 - волна с конфетти | 12 - плавная смена цвета | 13 - радуга | 14 - конфетти)
            Удержание "средней" кнопки во время отображения режима подсветки(для адресных светодиодов) - переводит в режим установки цвета, выбор цвета осуществляется "левой" и "правой" кнопками(войти можно только в режимах поддерживающих смену цвета - статичная, дыхание, бегущий огонь, волна)
        Клик по "левой" кнопке - переключает режим точек(0 - выкл | 1 - статичная | 2 - динамичная(плавно мигает)), (для двух неоновых ламп)(3 - маятник), (для точек в индикаторах)(3 - бегущая | 4 - змейка | 5 - резинка | 6 - маятник(только для 6-ти ламп или если используются левые и правые точки))
    Клик по "левой" кнопке отображает текущую температуру, затем клик по "левой" кнопке переключает температуру/давление/влажность.
