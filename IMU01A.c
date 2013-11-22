/*
Library for the MLAB module IMU01A
This library lets you configure the sensors on the direct and fastest data streaming and read out the values

Created by Ondra Sestak 2013
*/

#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include <IMU01A.h>

/*accelerometer configuration*/
void accInit(I2CDriver *i2c_drv, uint8_t addr)
{
    uint8_t tx_data[8]; 
    msg_t msg;
    
    tx_data[0] = 0x2a;/*register CTRL_REG1*/
    tx_data[1] = 0x01;
    i2cAcquireBus (i2c_drv);
    msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 2, 0, 0, MS2ST(4));
    i2cReleaseBus (i2c_drv);
    if (msg != RDY_OK) i2cGetErr (i2c_drv, &SD_DRV);
}

/*accelerometer reading*/
void accRead (I2CDriver *i2c_drv, uint8_t addr, int16_t *acc_x, int16_t *acc_y, int16_t *acc_z)
{
    uint8_t tx_data[8]; 
    uint8_t rx_data[6];
    msg_t msg;

   	tx_data[0] = IMU01A_ACC_AXIS;
   	i2cAcquireBus (i2c_drv);
    msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 1, rx_data, 6, MS2ST(4));
    i2cReleaseBus (i2c_drv);
    if (msg != RDY_OK) i2cGetErr(i2c_drv, &SD_DRV);
      
    *acc_x = (rx_data[0] << 8) | rx_data[1];
    *acc_y = (rx_data[2] << 8) | rx_data[3];
    *acc_z = (rx_data[4] << 8) | rx_data[5];
}

/*gyroscope configuring*/
void gyroInit (I2CDriver *i2c_drv, uint8_t addr)
{
    uint8_t tx_data[8]; 
    msg_t msg;
    
    tx_data[0] = 0x20;/*register CTRL_REG1*/
    tx_data[1] = 0xff;
    i2cAcquireBus (i2c_drv);
    msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 2, 0, 0, MS2ST(4));
    i2cReleaseBus (i2c_drv);
    if (msg != RDY_OK) i2cGetErr (i2c_drv, &SD_DRV);

    tx_data[0] = 0x2e;/*register FIFO_CTRL_REG*/
    tx_data[1] = 0x40;
    i2cAcquireBus (i2c_drv);
    msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 2, 0, 0, MS2ST(4));
    i2cReleaseBus (i2c_drv);
    if (msg != RDY_OK) i2cGetErr (i2c_drv, &SD_DRV);
}

/*gyroscope reading*/
void gyroRead (I2CDriver *i2c_drv, uint8_t addr, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z)
{
    uint8_t tx_data[8]; 
    uint8_t rx_data[6];
    msg_t msg;

    tx_data[0] = IMU01A_GYRO_AXIS;
    i2cAcquireBus (i2c_drv);
    msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 1, rx_data, 6, MS2ST(4));
    i2cReleaseBus (i2c_drv);
    if (msg != RDY_OK) i2cGetErr(i2c_drv, &SD_DRV);
      
    *gyro_x = (rx_data[0] << 8) | rx_data[1];
    *gyro_y = (rx_data[2] << 8) | rx_data[3];
    *gyro_z = (rx_data[4] << 8) | rx_data[5];
}

/*temperature reading*/
tempRead (I2CDriver *i2c_drv, uint8_t addr, uint8_t *temp)
{
    uint8_t tx_data[8]; 
    uint8_t rx_data[6];
    msg_t msg;

    tx_data[0] = IMU01A_GYRO_TEMP;
    i2cAcquireBus (i2c_drv);
    msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 1, rx_data, 6, MS2ST(4));
    i2cReleaseBus (i2c_drv);
    if (msg != RDY_OK) i2cGetErr(i2c_drv, &SD_DRV);
      
    *temp = rx_data[0];
}