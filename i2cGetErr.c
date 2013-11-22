/*
i2c troubleshooting library

Created by Ondra Sestak 2013
*/
#include <ch.h>
#include <hal.h>
#include <chprintf.h>

void i2cGetErr(I2CDriver *i2c_drv, SerialDriver *sd_drv)
{
    chprintf ((BaseSequentialStream *)sd_drv, "Well, this is embarassing :'( - something is wrong with i2c...\r\n");
    int err;
    err = i2cGetErrors (i2c_drv);
    
    switch (err)
    {
        case 0x01 :
            chprintf ((BaseSequentialStream *)sd_drv, "Bus error\r\n");
        break;

        case 0x02 :
            chprintf ((BaseSequentialStream *)sd_drv, "Arbitration lost\r\n");
        break;

        case 0x04 :
            chprintf ((BaseSequentialStream *)sd_drv, "Acknowledge failure\r\n");
        break;

        case 0x08 :
            chprintf ((BaseSequentialStream *)sd_drv, "Overrun/Underrun\r\n");
        break;

        case 0x10 :
            chprintf ((BaseSequentialStream *)sd_drv, "PEC error in reception\r\n");
        break;

        case 0x20 :
            chprintf ((BaseSequentialStream *)sd_drv, "Hardware timeout\r\n");
        break;

        case 0x40 :
            chprintf ((BaseSequentialStream *)sd_drv, "SMBus altert\r\n");
        break;

        default :
            chprintf ((BaseSequentialStream *)sd_drv, "WTF?\r\n");
        break;
    }

    chprintf ((BaseSequentialStream *)&SD2, "Do you have everthig connected correctly?\r\n");
    chThdSleepMilliseconds (1000);
    chprintf ((BaseSequentialStream *)&SD2, "Are you sure that you haven't the data and clock pins set as outputs? ;)\r\n");
}