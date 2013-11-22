#define IMU01A_ACC 0x1C
#define IMU01A_ACC_AXIS 0x01 

#define IMU01A_GYRO 0x68
#define IMU01A_GYRO_AXIS 0x28
#define IMU01A_GYRO_TEMP 0x26

#define SD_DRV SD2

/*i2c driver configuration*/
static const I2CConfig i2cCfg = {
	OPMODE_I2C,
	400000, /*400 kHz*/
	FAST_DUTY_CYCLE_2,
};