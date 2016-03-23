#include "IMU.h"
#include "mini51series.h"
#include "MPU6050.h"
#include "filter.h"
#include "Timer_Ctrl.h"


#define CONSTANTS_ONE_G					9.80665f		/* m/s^2		*/

#define SENSOR_MAX_G 8.0f		//constant g		// tobe fixed to 8g. but IMU need to  correct at the same time
#define SENSOR_MAX_W 2000.0f	//deg/s
#define ACC_SCALE  (SENSOR_MAX_G/32768.0f)
#define GYRO_SCALE  (SENSOR_MAX_W/32768.0f)

imu_t imu={0};

void ReadIMUSensorHandle(void)
{
	uint8_t i;
		//read raw
		
		MPU6050_getAcceleration(&imu.accADC[0], &imu.accADC[1], &imu.accADC[2]);
		MPU6050_getRotation(&imu.gyroADC[0], &imu.gyroADC[1], &imu.gyroADC[2]);
	
		//turn to physical
		for(i=0;i<3;i++)
		{
				imu.accRaw[i]= (float)imu.accADC[i] *ACC_SCALE * CONSTANTS_ONE_G ;
				imu.gyroRaw[i]=(float)imu.gyroADC[i] * GYRO_SCALE * M_PI_F /180.f;		//deg/s
		}

		imu.accb[0]=LPF2pApply_1(imu.accRaw[0]-imu.accOffset[0]);
		imu.accb[1]=LPF2pApply_2(imu.accRaw[1]-imu.accOffset[1]);
		imu.accb[2]=LPF2pApply_3(imu.accRaw[2]-imu.accOffset[2]);
		#ifdef IMU_SW
		imu.gyro[0]=LPF2pApply_4(imu.gyroRaw[0]);
		imu.gyro[1]=LPF2pApply_5(imu.gyroRaw[1]);
		imu.gyro[2]=LPF2pApply_6(imu.gyroRaw[2]); 
		#else
		imu.gyro[0]=LPF2pApply_4(imu.gyroRaw[0]-imu.gyroOffset[0]);
		imu.gyro[1]=LPF2pApply_5(imu.gyroRaw[1]-imu.gyroOffset[1]);
		imu.gyro[2]=LPF2pApply_6(imu.gyroRaw[2]-imu.gyroOffset[2]); 
		#endif
		//low pass filter.  inertial or digital . tobe tested
		/*
		for(i=0;i<2;i++)	//tobe fixed to digital filter
		{
				accFilted[i] = accFilted[i] * (1.0f - (1.0f / ACC_XY_LPF_FACTOR)) + accRaw[i] * (1.0f /ACC_XY_LPF_FACTOR); 
				
				gyroFilted[i] = gyroFilted[i] * (1.0f - (1.0f / GYRO_XY_LPF_FACTOR)) + gyroRaw[i] * (1.0f/GYRO_XY_LPF_FACTOR);
		}
		accFilted[2]=LPF2pApply_3(accRaw[2]);			// need to set cutoff freq and sample rate before 
		gyroFilted[2] = gyroFilted[2] * (1.0f - (1.0f / GYRO_Z_LPF_FACTOR)) + gyroRaw[2] * (1.0f/GYRO_Z_LPF_FACTOR);
		*/
		
} 
