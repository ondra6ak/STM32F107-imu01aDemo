/*
Demo with the MLAB module IMU01A
Module is connected to the second i2c bus
Data are transmitted through the second serial bus
This demo reads and print out accelerometr and gyroscope axis and the temperature of the gyroscope chip

Created by Ondra Sestak 2013
*/

#include <ch.h>
#include <hal.h>
#include <IMU01A.h>
#include <chprintf.h>

/*led blinking theard*/
static WORKING_AREA (heartWrkArea, 32);
static msg_t heartBeat (void*Arg)
{
	chprintf ((BaseSequentialStream *)&SD2, "\n\rHello world!\n\r");

    palSetPad (GPIOB, LED_1);
    palClearPad (GPIOB, LED_2);
	while (true)
	{
		palTogglePad (GPIOB, LED_1);
		palTogglePad (GPIOB, LED_2);
		chThdSleepMilliseconds (250);
	}
}

/*main sensor reading and printing out theard*/
static WORKING_AREA (gyroDemoWrkArea, 256);
static msg_t gyroDemo (void*arg)
{
    int16_t acc_x, acc_y, acc_z;
    int16_t gyro_x, gyro_y, gyro_z;
    uint8_t temp;

	/*sensors initializing*/
    gyroInit (&I2CD2, IMU01A_GYRO);
    accInit (&I2CD2, IMU01A_ACC);

    while (true)
    {
    	/*gyroscope and temperature reading*/
        gyroRead (&I2CD2, IMU01A_GYRO, &gyro_x, &gyro_y, &gyro_z);
        tempRead (&I2CD2, IMU01A_GYRO, &temp);
        /*accelerometer reading*/
        accRead (&I2CD2, IMU01A_ACC, &acc_x, &acc_y, &acc_z);
        /*printing out the measured values*/
        chprintf ((BaseSequentialStream *)&SD2, "%d gyroX    ", gyro_x);
        chprintf ((BaseSequentialStream *)&SD2, "%d gyroY    ", gyro_y);
        chprintf ((BaseSequentialStream *)&SD2, "%d gyroZ    ", gyro_z);
        chprintf ((BaseSequentialStream *)&SD2, "%d T    ", temp);
        
        /*printing out the measured values*/
        chprintf ((BaseSequentialStream *)&SD2, "%d accX    ", acc_x);
        chprintf ((BaseSequentialStream *)&SD2, "%d accY    ", acc_y);
        chprintf ((BaseSequentialStream *)&SD2, "%d accZ    ", acc_z);
        chprintf ((BaseSequentialStream *)&SD2, "\n\r");     	
    }
}


int main (void)
{
	halInit();
	chSysInit();

	sdStart (&SD2, NULL);
    i2cStart (&I2CD2, &i2cCfg);

    palSetPadMode(GPIOB, 10, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
    palSetPadMode(GPIOB, 11, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
    chThdSleepMilliseconds(100);  /* Just to be safe. */

	chThdCreateStatic (heartWrkArea, sizeof (heartWrkArea), NORMALPRIO, heartBeat, NULL);
	chThdCreateStatic (gyroDemoWrkArea, sizeof (gyroDemoWrkArea), NORMALPRIO, gyroDemo, NULL);
}