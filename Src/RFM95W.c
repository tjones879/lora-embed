#include "RFM95W.h"
#include "stm32f1xx_hal.h"

uint8_t FifoIORegister = 0x00;
uint8_t OpModeRegister = 0x00;
uint8_t PaConfigRegister = 0x00;
uint8_t LnaRegister = 0x10;
uint8_t FifoAddrPtrReg = 0x00;
uint8_t FifoTxAddrReg = 0x80;
uint8_t FifoRxAddrReg = 0x00;
uint8_t FifoRxCurrReg = 0x00;
uint8_t IrqFlagsRegister = 0x00;
uint8_t RxNumBytesRegister = 0x00;
uint8_t ModemStatRegister = 0x00;
uint8_t ModemConfigRegister1 = 0x00;
uint8_t ModemConfigRegister2 = 0x00;
uint8_t FifoRxByteAddr = 0x00;

void writeRFMIO(SPI_HandleTypeDef *hspi, uint8_t *buff, int buffLen) {
    uint8_t addy = 0x80 | 0x00;
    HAL_SPI_Transmit(hspi, &addy, sizeof(addy), 100);
    HAL_SPI_Transmit(hspi, buff, buffLen, 100);
}

// LoRa RegOpMode Constants
void writeRegOpMode(SPI_HandleTypeDef *hspi, uint8_t val) {
    uint8_t write[2] = {0x80 | RegOpMode, val};
    HAL_SPI_Transmit(hspi, &write, sizeof(write), 100);
}

uint8_t readRegOpMode(SPI_HandleTypeDef *hspi) {
    uint8_t read = 0x00 | RegOpMode;
    HAL_SPI_TransmitReceive(hspi, &read, &OpModeRegister, sizeof(read), 100);
    return OpModeRegister;
}

void setRegOpSleep(SPI_HandleTypeDef *hspi) {
    uint8_t val = (OpModeRegister & ~0x07) | SLEEP_Mode;
    writeRegOpMode(hspi, val);
}

void setRegOpLoRa(SPI_HandleTypeDef *hspi) {
    uint8_t val = (OpModeRegister & ~0x80) | LoRa_Mode;
    writeRegOpMode(hspi, val);
}

void setRegOpStandby(SPI_HandleTypeDef *hspi) {
    uint8_t val = (OpModeRegister & ~0x07) | STDBY_Mode;
    writeRegOpMode(hspi, val);
}

// LoRa RegPaConfig
uint8_t getPaConfigReg(SPI_HandleTypeDef *hspi) {
    uint8_t read = 0x00 | RegPaConfig;
    HAL_SPI_TransmitReceive(hspi, &read, &PaConfigRegister, sizeof(read), 100);
    return PaConfigRegister;
}

void selectPAPin(SPI_HandleTypeDef *hspi, uint8_t val) {
    uint8_t write[2];
    write[0] = 0x80 | RegPaConfig;
    write[1] = (PaConfigRegister & ~PA_BOOST_Mode) | (val & PA_BOOST_Mode);
    HAL_SPI_Transmit(hspi, &write, sizeof(write), 100);
}

void setMaxPaPower(SPI_HandleTypeDef *hspi, uint8_t val) {
    uint8_t write[2];
    write[0] = 0x80 | RegPaConfig;
    write[1] = (PaConfigRegister & ~MaxPower_Mask) | (val & MaxPower_Mask);
    HAL_SPI_Transmit(hspi, &write, sizeof(write), 100);
}

void setOutputPower(SPI_HandleTypeDef *hspi, uint8_t val) {
    uint8_t write[2];
    write[0] = 0x80 | RegPaConfig;
    write[1] = (PaConfigRegister & ~OutputPower_Mask) | (val & OutputPower_Mask);
    HAL_SPI_Transmit(hspi, &write, sizeof(write), 100);
}


// LoRa RegLna
uint8_t getLnaReg(SPI_HandleTypeDef *hspi) {
    uint8_t read = 0x00 | RegLna;
    HAL_SPI_TransmitReceive(hspi, &read, &LnaRegister, sizeof(read), 100);
    return LnaRegister;
}

// Fifo Page Registers
uint8_t getFifoAddrPtr(SPI_HandleTypeDef *hspi) {
    uint8_t read = 0x00 | RegFifoAddrPtr;
    HAL_SPI_TransmitReceive(hspi, &read, &FifoAddrPtrReg, sizeof(read), 100);
    return FifoAddrPtrReg;
}

uint8_t getFifoTxAddr(SPI_HandleTypeDef *hspi) {
    uint8_t read = 0x00 | RegFifoTxBaseAddr;
    HAL_SPI_TransmitReceive(hspi, &read, &FifoTxAddrReg, sizeof(read), 100);
    return FifoTxAddrReg;
}

uint8_t getFifoRxAddr(SPI_HandleTypeDef *hspi) {
    uint8_t read = 0x00 | RegFifoRxBaseAddr;
    HAL_SPI_TransmitReceive(hspi, &read, &FifoRxAddrReg, sizeof(read), 100);
    return FifoRxAddrReg;
}

uint8_t getFifoRxCurr(SPI_HandleTypeDef *hspi) {
    uint8_t read = 0x00 | RegFifoRxCurrAddr;
    HAL_SPI_TransmitReceive(hspi, &read, &FifoRxCurrReg, sizeof(read), 100);
    return FifoRxCurrReg;
}

// RegIrqFlags
uint8_t getIrqFlags(SPI_HandleTypeDef *hspi) {
    uint8_t read = 0x00 | RegIrqFlags;
    HAL_SPI_TransmitReceive(hspi, &read, &IrqFlagsRegister, sizeof(read), 100);
    return IrqFlagsRegister;
}

uint8_t getRxNumBytes(SPI_HandleTypeDef *hspi) {
    uint8_t read = 0x00 | RegRxNumBytes;
    HAL_SPI_TransmitReceive(hspi, &read, &RxNumBytesRegister, sizeof(read), 100);
    return RxNumBytesRegister;
}

// RegModemStat
uint8_t getModemStat(SPI_HandleTypeDef *hspi) {
    uint8_t read = 0x00 | RegModemStat;
    HAL_SPI_TransmitReceive(hspi, &read, &ModemStatRegister, sizeof(read), 100);
    return ModemStatRegister;
}

// RegModemConfig1
uint8_t getModemCfg1(SPI_HandleTypeDef *hspi) {
    uint8_t read = 0x00 | RegModemConfig1;
    HAL_SPI_TransmitReceive(hspi, &read, &ModemConfigRegister1, sizeof(read), 100);
    return ModemConfigRegister1;
}

// RegModemConfig2
uint8_t getModemCfg2(SPI_HandleTypeDef *hspi) {
    uint8_t read = 0x00 | RegModemConfig2;
    HAL_SPI_TransmitReceive(hspi, &read, &ModemConfigRegister2, sizeof(read), 100);
    return ModemConfigRegister2;
}
