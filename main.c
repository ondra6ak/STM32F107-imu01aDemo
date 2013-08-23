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

/*i2c driver configuration*/
static const I2CConfig i2cCfg = {
	OPMODE_I2C,
	400000, /*400 kHz*/
	FAST_DUTY_CYCLE_2,
};

/*led blinking theard*/
static WORKING_AREA (heartWrkArea, 32);
static msg_t heartBeat (void*Arg)
{
	chprintf ((BaseChannel *)&SD2, "\n\r");
	chprintf ((BaseChannel *)&SD2, "Hello world!\n\r");

	while (true)
	{
		palSetPad (GPIOB, GPIOB_LED1);
		palClearPad (GPIOB, GPIOB_LED2);
		chThdSleepMilliseconds (250);
		palClearPad (GPIOB, GPIOB_LED1);
		palSetPad (GPIOB, GPIOB_LED2);
		chThdSleepMilliseconds (250);
	}
}

/*main sensor reading and printing out theard*/
static WORKING_AREA (gyroDemoWrkArea, 256);
static msg_t gyroDemo (void*arg)
{
    int16_t X, Y, Z;
    uint8_t temp;

	/*sensors initializing*/
    gyroInit (&I2CD2, IMU01A_GYRO);
    accInit (&I2CD2, IMU01A_ACC);
    while (true)
    {
    	/*gyroscope and temperature reading*/
        gyroRead (&I2CD2, IMU01A_GYRO, &X, &Y, &Z);
        tempRead (&I2CD2, IMU01A_GYRO, &temp);
        /*printing out the measured values*/
        chprintf ((BaseChannel *)&SD2, "%d gyroX    ", X);
        chprintf ((BaseChannel *)&SD2, "%d gyroY    ", Y);
        chprintf ((BaseChannel *)&SD2, "%d gyroZ    ", Z);
        
        /*accelerometer reading*/
        accRead (&I2CD2, IMU01A_ACC, &X, &Y, &Z);
        /*printing out the measured values*/
        chprintf ((BaseChannel *)&SD2, "%d accX    ", X);
        chprintf ((BaseChannel *)&SD2, "%d accY    ", Y);
        chprintf ((BaseChannel *)&SD2, "%d accZ    ", Z);
        chprintf ((BaseChannel *)&SD2, "%d °C    ", temp);
        chprintf ((BaseChannel *)&SD2, "\n\r");     	
    }
}


int main (void)
{
	halInit();
	chSysInit();

	sdStart (&SD2, NULL);
    i2cStart (&I2CD2, &i2cCfg);


	chThdCreateStatic (heartWrkArea, sizeof (heartWrkArea), NORMALPRIO, heartBeat, NULL);
	chThdCreateStatic (gyroDemoWrkArea, sizeof (gyroDemoWrkArea), NORMALPRIO, gyroDemo, NULL);
}