/*
demo s modulem IMU01A
modul I2C2 
seriovka SD2
*/

#include <ch.h>
#include <hal.h>
#include <IMU01A.h>
#include <chprintf.h>


static const I2CConfig i2cCfg = {
	OPMODE_I2C,
	400000, /*400 kHz*/
	FAST_DUTY_CYCLE_2,
};

/*led blinking*/
static WORKING_AREA (heartWrkArea, 32);
static msg_t heartBeat (void*Arg)
{
	chprintf ((BaseChannel *)&SD2, "\n\r");
	chprintf ((BaseChannel *)&SD2, "Hello world!\n\r");

	while (true)
	{
		palSetPad (GPIOB, 8);
		palClearPad (GPIOB, 7);
		chThdSleepMilliseconds (250);
		palClearPad (GPIOB, 8);
		palSetPad (GPIOB, 7);
		chThdSleepMilliseconds (250);
	}
}


static WORKING_AREA (gyroDemoWrkArea, 256);
static msg_t gyroDemo (void*arg)
{
    gyroInit (&I2CD2, IMU01A_GYRO);
    accInit (&I2CD2, IMU01A_ACC);
    while (true)
    {
        int16_t X, Y, Z;
        uint8_t temp;

        gyroRead (&I2CD2, IMU01A_GYRO, &X, &Y, &Z);
        tempRead (&I2CD2, IMU01A_GYRO, &temp);
        chprintf ((BaseChannel *)&SD2, "%d gyroX    ", X);
        chprintf ((BaseChannel *)&SD2, "%d gyroY    ", Y);
        chprintf ((BaseChannel *)&SD2, "%d gyroZ    ", Z);

        accRead (&I2CD2, IMU01A_ACC, &X, &Y, &Z);
        chprintf ((BaseChannel *)&SD2, "%d accX    ", X);
        chprintf ((BaseChannel *)&SD2, "%d accY    ", Y);
        chprintf ((BaseChannel *)&SD2, "%d accZ    ", Z);
        chprintf ((BaseChannel *)&SD2, "%d °C    ", temp);
        chprintf ((BaseChannel *)&SD2, "\n\r");     
        chThdSleepMilliseconds (50);	
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