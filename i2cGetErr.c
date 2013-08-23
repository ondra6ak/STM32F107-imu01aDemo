#include <ch.h>
#include <hal.h>
#include <chprintf.h>

void i2cGetErr(I2CDriver *i2cDrv)
{
    chprintf ((BaseChannel *)&SD2, "Well, this is embarassing :'(\r\n");
    int err;
    err = i2cGetErrors (i2cDrv);
    
    switch (err)
    {
        case 0x01 :
            chprintf ((BaseChannel *)&SD2, "Bus error\r\n");
        break;

        case 0x02 :
            chprintf ((BaseChannel *)&SD2, "Arbitration lost\r\n");
        break;

        case 0x04 :
            chprintf ((BaseChannel *)&SD2, "Acknowledge failure\r\n");
        break;

        case 0x08 :
            chprintf ((BaseChannel *)&SD2, "Overrun/Underrun\r\n");
        break;

        case 0x10 :
            chprintf ((BaseChannel *)&SD2, "PEC error in reception\r\n");
        break;

        case 0x20 :
            chprintf ((BaseChannel *)&SD2, "Hardware timeout\r\n");
        break;

        case 0x40 :
            chprintf ((BaseChannel *)&SD2, "SMBus altert\r\n");
        break;

        default :
            chprintf ((BaseChannel *)&SD2, "WTF?\r\n");
        break;
    }

    chprintf ((BaseChannel *)&SD2, "Do you have everthig connected correctly?\r\n");
    chThdSleepMilliseconds (1000);
    chprintf ((BaseChannel *)&SD2, "Are you sure that you haven't the data and clock pins set as outputs? :)\r\n");

    while(true){}
}