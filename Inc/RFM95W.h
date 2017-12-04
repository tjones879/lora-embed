#ifndef RFM95W_H
#define RFM95W_H

#include <stdint.h>
#include "stm32f1xx_hal.h"

#define RegFifoIO    0x00 // Base-band FIFO I/O. Cleared upon SLEEP
extern uint8_t FifoIORegister;
void writeFifoIO(uint8_t *buffer);

// LoRa RegOpMode Constants
#define RegOpMode     0x01
#define LoRa_Mode     0x01
#define LowFreqMode   0x08
#define SLEEP_Mode    0x00
#define STDBY_Mode    0x01
#define FSTX_Mode     0x02
#define TX_Mode       0x03
#define FSRX_Mode     0x04
#define RXCont_Mode   0x05
#define RXSingle_Mode 0x06
#define CAD_Mode      0x07
extern uint8_t OpModeRegister;

void writeRegOpMode(SPI_HandleTypeDef *hspi, uint8_t val);
uint8_t readRegOpMode(SPI_HandleTypeDef *hspi);
void setRegOpSleep(SPI_HandleTypeDef *hspi);
void setRegOpLoRa(SPI_HandleTypeDef *hspi);
void setRegOpStandby(SPI_HandleTypeDef *hspi);

// LoRa RegPaConfig
#define RegPaConfig      0x09
#define PA_BOOST_Mode    0x01
#define MaxPower_Mask    0x70
#define OutputPower_Mask 0x08
extern uint8_t PaConfigRegister;
extern uint8_t getPaConfigReg(SPI_HandleTypeDef *hspi);
void selectPAPin(SPI_HandleTypeDef *hspi, uint8_t val);
void setMaxPaPower(SPI_HandleTypeDef *hspi, uint8_t val);
void setOutputPower(SPI_HandleTypeDef *hspi, uint8_t val);


// LoRa RegLna
#define RegLna        0x0C
#define LnaGain_Mask  0xE0
#define LnaBoost_Mode 0x03
extern uint8_t LnaRegister;
void setLnaGain(uint8_t val);
uint8_t getLnaReg(SPI_HandleTypeDef *hspi);

// Fifo Page Registers
#define RegFifoAddrPtr    0x0D
#define RegFifoTxBaseAddr 0x0E
#define RegFifoRxBaseAddr 0x0F
#define RegFifoRxCurrAddr 0x10
extern uint8_t FifoAddrPtrReg;
uint8_t getFifoAddrPtr(SPI_HandleTypeDef *hspi);
extern uint8_t FifoTxAddrReg;
uint8_t getFifoTxAddr(SPI_HandleTypeDef *hspi);
extern uint8_t FifoRxAddrReg;
uint8_t getFifoRxAddr(SPI_HandleTypeDef *hspi);
extern uint8_t FifoRxCurrReg;
uint8_t getFifoRxCurr(SPI_HandleTypeDef *hspi);

// RegIrqFlags
#define RegIrqFlags        0x12
#define RxTimeout_Mask     0x80
#define RxDone_Mask        0x40
#define PayloadCRCErr_Mask 0x20
#define ValidHeader_Mask   0x10
#define TxDone_Mask        0x08
#define CadDone_Mask       0x04
#define FHssChan_Mask      0x02
#define CadDetected_Mask   0x01
extern uint8_t IrqFlagsRegister;
uint8_t getIrqFlags(SPI_HandleTypeDef *hspi);

#define RegRxNumBytes 0x13 // Number of bytes in last payload received
extern uint8_t RxNumBytesRegister;
uint8_t getRxNumBytes(SPI_HandleTypeDef *hspi);

// RegModemStat
#define RegModemStat     0x18
#define ModemStatus_Mask 0x1F
extern uint8_t ModemStatRegister;
uint8_t getModemStat(SPI_HandleTypeDef *hspi);

// RegModemConfig1
#define RegModemConfig1     0x1D
#define Bandwidth_Mask      0xF0
#define CodingRate_Mask     0x0E
#define ImplicitHeader_Mode 0x01
extern uint8_t ModemConfigRegister1;
uint8_t getModemCfg1(SPI_HandleTypeDef *hspi);

// RegModemConfig2
#define RegModemConfig2      0x1E
#define SpreadingFactor_Mask 0xF0
#define TxContinuous_Mode    0x08
#define RxPayloadCrc_Mode    0x04
extern uint8_t ModemConfigRegister2;
uint8_t getModemCfg2(SPI_HandleTypeDef *hspi);


#define RegFifoRxByteAddr 0x25 // Address of the last byte written by receiver
extern uint8_t FifoRxByteAddr;


#endif
