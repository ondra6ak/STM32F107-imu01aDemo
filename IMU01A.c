#include <ch.h>
#include <hal.h>
#include <chprintf.h>

#include <IMU01A.h>


void accInit(I2CDriver *i2cDrv, uint8_t addr)
{
    uint8_t txData[8]; 
    msg_t msg;
    
    txData[0] = 0x2a;/*registr CTRL_REG1*/
    txData[1] = 0x01;
    i2cAcquireBus (&I2CD2);
    msg = i2cMasterTransmitTimeout (&I2CD2, addr, txData, 2, 0, 0, MS2ST(4));
    i2cReleaseBus (&I2CD2);
    if (msg != RDY_OK) i2cGetErr (i2cDrv);
}


void accRead (I2CDriver *i2cDrv, uint8_t addr, int16_t *accX, int16_t *accY, int16_t *accZ)
{
    uint8_t txData[8]; 
    uint8_t rxData[6];
    msg_t msg;

   	txData[0] = IMU01A_ACC_AXIS;
   	i2cAcquireBus (i2cDrv);
    msg = i2cMasterTransmitTimeout (i2cDrv, addr, txData, 1, rxData, 6, MS2ST(4));
    i2cReleaseBus (i2cDrv);
    if (msg != RDY_OK) i2cGetErr(i2cDrv);
      
    *accX = (rxData[0] << 8) | rxData[1];
    *accY = (rxData[2] << 8) | rxData[3];
    *accZ = (rxData[4] << 8) | rxData[5];
}


void gyroInit(I2CDriver *i2cDrv, uint8_t addr)
{
    uint8_t txData[8]; 
    msg_t msg;
    
    txData[0] = 0x20;/*registr CTRL_REG1*/
    txData[1] = 0xff;
    i2cAcquireBus (&I2CD2);
    msg = i2cMasterTransmitTimeout (&I2CD2, addr, txData, 2, 0, 0, MS2ST(4));
    i2cReleaseBus (&I2CD2);
    if (msg != RDY_OK) i2cGetErr (i2cDrv);

    txData[0] = 0x2e;/*registr FIFO_CTRL_REG*/
    txData[1] = 0x40;
    i2cAcquireBus (&I2CD2);
    msg = i2cMasterTransmitTimeout (&I2CD2, addr, txData, 2, 0, 0, MS2ST(4));
    i2cReleaseBus (&I2CD2);
    if (msg != RDY_OK) i2cGetErr (i2cDrv);
}


void gyroRead (I2CDriver *i2cDrv, uint8_t addr, int16_t *gyroX, int16_t *gyroY, int16_t *gyroZ)
{
    uint8_t txData[8]; 
    uint8_t rxData[6];
    msg_t msg;

    txData[0] = IMU01A_GYRO_AXIS;
    i2cAcquireBus (i2cDrv);
    msg = i2cMasterTransmitTimeout (i2cDrv, addr, txData, 1, rxData, 6, MS2ST(4));
    i2cReleaseBus (i2cDrv);
    if (msg != RDY_OK) i2cGetErr(i2cDrv);
      
    *gyroX = (rxData[0] << 8) | rxData[1];
    *gyroY = (rxData[2] << 8) | rxData[3];
    *gyroZ = (rxData[4] << 8) | rxData[5];
}

tempRead (I2CDriver *i2cDrv, uint8_t addr, uint8_t *temp)
{
    uint8_t txData[8]; 
    uint8_t rxData[6];
    msg_t msg;

    txData[0] = IMU01A_GYRO_TEMP;
    i2cAcquireBus (i2cDrv);
    msg = i2cMasterTransmitTimeout (i2cDrv, addr, txData, 1, rxData, 6, MS2ST(4));
    i2cReleaseBus (i2cDrv);
    if (msg != RDY_OK) i2cGetErr(i2cDrv);
      
    *temp = rxData[0];
}