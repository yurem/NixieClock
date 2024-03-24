# <p align="center">Страница проекта [NixieClock](https://community.alexgyver.ru/threads/chasy-na-gri-v2-alternativnaja-proshivka.5843/) на форуме.</p> 

![Schematic_NixieСlock](https://github.com/radon-lab/NixieClock/assets/71728333/0fd17f4a-4493-4aa0-ae5f-4ccfabf28b5b)

Модуль ESP8266 подключается к шине I2C, пины которые модуль ESP8266 использует в качестве SCL/SDA нужно указать в прошивке модуля ESP8266. При использовании модуля ESP8266 подтяжка шины I2C должна быть организована к источнику 3.3в!
Питать модуль ESP8266 от вывода 3v3 ардуино нельзя! Нужно использовать линейный стабилизатор или DC-DC преобразователь на 3.3в!
Инструкцию по загрузке прошивки и файловой системы смотрите в шапке прошивки веб интерфейса. 

Для синхронизации хода секунд желательно подключить пин SQW модуля DS3231 к пину ардуино D2, если у вас модуль DS3231mini, то необходимо найти 3-ю ножку микросхемы и также проводком подпаять к пину D2.

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
    0002 - Сбой осциллятора DS3231(батарейка модуля часов разряжена или проблемы с тактированием модуля часов).
    0003 - Слишком короткий сигнал SQW(во время работы часов были обнаружены помехи или неверный сигнал на SQW).
    0004 - Слишком длинный сигнала SQW(пропал сигнал SQW во время работы часов или сигнал отсутствовал при запуске).
    0005 - Выбранный датчик температуры не обнаружен(проверить подключение датчика температуры).
    0006 - Слишком низкое или слишком высокое напряжение питания(проверить источник питания).
    0007 - Сбой памяти EEPROM(повреждение данных, если ошибка будет повторятся слишком часто - износ EEPROM).
    0008 - Софтовая перезагрузка(говорит о нестабильности программы или об аппаратных проблемах с мк).
    0009 - Сбой работы преобразователя(регистры таймера были неожиданно изменены).
    0010 - Переполнение заполнения шим преобразователя(превышен верхний предел заполнения шим).
    0011 - Переполнение стека(утечка памяти).
    0012 - Переполнение тиков времени(основная программа не отвечает).
    0013 - Сбой работы динамической индикации(регистры таймера были неожиданно изменены или превышен предел регистра сравнения).


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


Порядок записи нового загрузчика(потребуется isp программатор):

    1. Настраиваем фьюзы(установив загрузчик для "Arduino UNO" или выставить вручную по картинке в папке загрузчика).
    2. Записываем кастомный загрузчик который идёт с прошивкой(i2c_bootloader_v2.hex).
    3. Загружаем прошивку в есп(по UART).
    4. Компилируем прошивку часов(нужно выбрать плату "Arduino UNO").
    5. Экспортируем прошивку часов в hex(скетч -> экспорт бинарного файла).
    6. Заходим в веб интерфейс, вкладка "Обновление", загружаем файл прошивки часов(поддерживаемые расширения файла - .hex).
    7. Зажимаем кнопку ресет на мк часов(нужно только при первой загрузке прошивке или при нештатной ситуации).
    8. Ждём появления окна о начале загрузки прошивки(появится надпись "Подключение...").
    9. Отпускаем кнопку ресет на мк часов(появится надпись "Загрузка...").
    10. Ждём окончания загрузки(появится надпись "Загрузка прошивки завершена").

Как подключить часы к wifi роутеру:

    1. После включения питания часов автоматически создаётся точка доступа "NixieClockAP"(после подключения к роутеру отключится через 5 мин).
    2. С любого устройства(Смартфон, ПК и пр.) ищем сеть "NixieClockAP" и подключаемся к ней(Пароль по умолчанию 1234567890).
    3. Далее с этого же устройства в браузере пишем в адресной строке: http://192.168.4.4/
    4. Далее переходим во вкладку «Сетевые настройки» и в блоке «Локальная сеть WIFI» выбираем свой роутер из списка и вводим пароль(если нужной сети нет или ваша сеть скрыта, необходимо нажать на ссылку "Ручной режим").
    5. При успешном соединении с роутером будет выдан IP адрес для доступа к веб интерфейсу по локальной сети(Далее всё управление в локальной сети будет именно по этому адресу).

    
Протестированные чипы DFPlayer:

    Поддерживаются:
        MH2024K-24
        GD3200B
        YX5200-24
        AB23A797393.1-74
        AB23A795250.1-74
        AA19HFF859-94

    Не поддерживаются:
        MH2024K-16
        AS21CN27OC
         
Что планируется:

    Добавить выбор основного датчика(при разделении двух датчиков) в веб интерфейсе.
    Добавить вывод температуры с двух датчиков(при разделении двух датчиков) для ручного отображения.
    Добавить возможность выбора перехода на зимнее/летнее время в часах.
    Добавить возможность воспроизводить музыку.
    Добавить анимации перехода подсветки на адресных светодиодах.
    Добавить беспроводной датчик температуры на esp8266.
    Добавить поддержку подключения двух дешефраторов к сдвиговому регистру.

    
Что поддерживается:
Периферия:
    
    Датчики температуры DHT11/DHT12/MW33/DHT21/DHT22(AM2301/AM2302), DS18B20/DS18S20/DS1820 - доступные пины подключения(D0..D13) с подтяжкой 4.7-10кОм к +5в.
    Датчик температуры BME280(BMP085/180/280) - доступные пины подключения(A4 и A5) параллельно модулю часов.
    Датчик температуры SHT20(SHT21/SHT25), SHT30(SHT31/SHT35) - доступные пины подключения(A4 и A5) параллельно модулю часов.
    Датчик температуры AHT10(AHT15), AHT20 - доступные пины подключения(A4 и A5) параллельно модулю часов.
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
    Модуль ESP8266 - доступные пины подключения(A4 и A5) параллельно модулю часов.


Программно:
    
    Поддержка часов на 4/6 ламп.
    12/24 часовой формат времени.
    Переход на летнее/зимнее время(Только при использовании есп).
    Будильник(Один или несколько).
    Радиобудильник(При наличии модуля радио).
    Автоматическое определение подключенного датчика температуры(Если выбрано несколько датчиков).
    Авто-показ температуры(Влажности/Давления).
    Авто-показ даты/года.
    Отображение текущей температуры/давления/влажности.
    Отображение текущей даты/года.
    Меню настройки яркости и др. функций.
    Быстрое меню для выбора анимации смены минут(секунд)/точек/подсветки.
    Таймер - секундомер(Только при наличии доп. кнопки).
    Радиоприёмник(Только при наличии доп. кнопки или есп).
    Антиотравление ламп(3 варианта анимации, выбор из меню).
    Мелодия смены часа(Или озвучка при использовании плеера).
    Смена яркости по времени и по датчику освещённости.
    Анимация глюков.
    10 режимов анимации авто-показа(Есть случайный режим).
    10 режимов анимации минут(Есть случайный режим).
    3 режима анимации секунд для 6-ти ламп(Выбор из меню).
    3 режима подсветки для обычных диодов и 15 для адресных WS2812B.
    3 режима работы секундных точек (1 режим для двух неоновых ламп / 6 режимов разделительных точек) и доп.режимы для отображения состояния будильника.
    Возможность создания собственных мелодий будильника.
    Система контроля основных параметров часов(Ошибки).
    Меню отладки(Для опытных пользователей).
    Озвучка пунктов меню, времени и температуры.
    Программирование кнопок ИК пульта из меню отладки.
    Режим сна(Отключение ламп через заданное время).
    Веб-интерфейс для настройки и мониторинга.
    Обновление прошивки часов через веб интерфейс.
    Второй датчик температуры(DHTxx или DS18x20) для "Улицы"(Требуется наличие есп).


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
    
Настройка кнопок пульта:

    Управление:

    Клик по "средней кнопке" - выйти из режима программирования кнопок ИК пульта
    Клик по "левой кнопке" - уменьшить значение номера кнопки ИК пульта
    Клик по "правой кнопке" - увеличить значение номера кнопки ИК пульта
    Удержать "среднюю кнопку" - сбросить текущую кнопку ИК пульта


    Нумерация кнопок:

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
    14..23 - Переключить на ячейку памяти радиостанции 0..9
    

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
    
    01 - Бузер(Формат времени(12ч | 24ч)), Плеер(Формат времени(12ч | 24ч) : Глюки(0 - выкл | 1 - вкл))
    02 - Бузер(Глюки(0 - выкл | 1 - вкл)), Плеер(Громкость озвучки : Глюки(0 - выкл | 1 - вкл))
    03 - Бузер(Звук кнопок(0 - выкл | 1 - вкл)), Плеер(Озвучка часа(Температура/Новый час) : Озвучка действий(0 - выкл | 1 - вкл))
    04 - Время звука смены часа(Начало : Конец)(Выключить звук смены часа: начало = конец)
    05 - Время смены подсветки(Ночь : День)(Выключить смену яркости(включить датчик освещения): ночь = день)
    06 - Яркость индикаторов(Ночь : День)
    07 - Яркость подсветки(Ночь : День)
    08 - Яркость секундных точек(Ночь : День)
    09 - Коррекция датчика температуры(Коррекция : Сенсор(только отображение))
    10 - Настройка интервала и анимации автоматического отображения(Время в минутах(0 - выключить) : Анимация)
    11 - Настройка интервала и анимации антиотравления индикаторов(Время в минутах : Анимация)
    12 - Установка времени ожидания после выхода из сна(Ночь : День)(0 - выключить)

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
    Клик по "средней" кнопке отображает текущий режим точек, затем:
        Клик по "правой" кнопке - переключает режим анимации смены минут(0 - выкл, 1 - случайная анимация, 2 - плавное угасание и появление , 3 - перемотка по порядку числа, 4 - перемотка по порядку катодов в лампе, 5 - поезд, 6 - резинка, 7 - ворота, 8 - волна, 9 - блики, 10 - испарение | 11 - игровой автомат)
        Удержание "правой" кнопки во время отображения режима анимации смены минут(если нет дополнительной кнопки) - переводит в режим установки анимации смены секунд, выбор анимации осуществляется "левой" кнопкой.
        Клик по "левой" кнопке переключает режим подсветки -
            Для обычных светодиодов: (0 - выкл | 1 - статичная | 2 - динамичная(дыхание))
            Для адресных светодиодов: (0 - выкл | 1 - статичная | 2 - дыхание | 3 - дыхание со сменой цвета при затухании | 4 - бегущий огонь | 5 - бегущий огонь со сменой цвета | 6 - бегущий огонь с радугой | 7 - бегущий огонь с конфетти | 8 - волна | 9 - волна со сменой цвета | 10 - волна с радугой | 11 - волна с конфетти | 12 - плавная смена цвета | 13 - радуга | 14 - конфетти)
        Удержание "левой" кнопки во время отображения режима подсветки(для адресных светодиодов) - переводит в режим установки цвета, выбор цвета осуществляется "левой" кнопкой(войти можно только в режимах поддерживающих смену цвета - статичная, дыхание, бегущий огонь, волна)
        Клик по "средней" кнопке - переключает режим точек(0 - выкл | 1 - статичная | 2 - динамичная(плавно мигает)), (для двух неоновых ламп)(3 - маятник), (для точек в индикаторах)(3 - мигающая | 4 - бегущая | 5 - змейка | 6 - резинка | 7 - одинарный маятник(только для 6-ти ламп или если используются левые и правые точки) | 8 - двойной маятник(только для 6-ти ламп и если используются левые и правые точки))
        Клик по "дополнительной" кнопке - переключает режим анимации смены секунд(0 - выкл, 1 - плавное угасание и появление , 2 - перемотка по порядку числа, 3 - перемотка по порядку катодов в лампе)
    Клик по "левой" кнопке отображает текущую температуру, затем клик по "левой" кнопке переключает температуру/давление/влажность.
