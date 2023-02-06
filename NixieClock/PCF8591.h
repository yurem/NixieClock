#define PCF8591_ADDR 0x48       //адрес датчика

#define PCF8591_OUTPUT_MASK             0b01000000
#define PCF8591_INCR_FLAG               0x04

#define LIGTH_VALUE   (((uint8_t *)&analogInputChannelsPCF)[3]) // значени от 0 до 255, где большее значение - выше яркость

// Структура данных для хранения последних прочитанных значений
struct AnalogInputChannelsPCF {
  uint8_t port1;
  uint8_t port2;
  uint8_t port3;
  uint8_t port4;
} analogInputChannelsPCF;

//-------------------------------------- Проверка подключения чтение PCF8591 ----------------------------
bool isConnectedPCF() //проверка подключения чтение PCF8591
{
  if (wireBeginTransmission(PCF8591_ADDR, false)) return false;
  wireEnd(); //конец передачи

  return 1;
}
//-------------------------------------- Чтение значений 4-х портов PCF8591 -----------------------------
bool readAnalogInputChannelsPCF(void) { //чтение аналоговых портов ввода
  uint8_t control = PCF8591_OUTPUT_MASK | PCF8591_INCR_FLAG;

  if (wireBeginTransmission(PCF8591_ADDR)) return 0;
  wireWrite(control);
  wireEnd();
  if (wireRequestFrom(PCF8591_ADDR, (uint8_t) 5)) {
    return 0;
  }

  wireRead();
  for (uint8_t i = 0; i < 4; i++) {
    if (i == 3) {
      ((uint8_t *)&analogInputChannelsPCF)[i] = wireReadEndByte();
    } else {
      ((uint8_t *)&analogInputChannelsPCF)[i] = wireRead();
    }
  }

  return 1;
}
//--------------------------------------  запись значения аналогового вывода PCF8591 --------------------
bool writeAnalogPCF(uint8_t value) { //чтение аналоговых портов ввода
  uint8_t control = PCF8591_OUTPUT_MASK;

  if (wireBeginTransmission(PCF8591_ADDR)) return 0;
  wireWrite(control);
  wireWrite(value);
  wireEnd();

  return 1;
}
