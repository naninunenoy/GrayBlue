#ifndef __IMU_IMU_H // 先頭
#define __IMU_IMU_H 

#include <SparkFunMPU9250-DMP.h>
#include "DMPRawData.h"

namespace imu {
class IMU {
public:
    explicit IMU();
    ~IMU();
    bool Setup();
    bool Update();

    const unsigned long time() const { return dmp.time; }
    const int* rawAcc() const { return rawData.acc; }
    const int* rawGyro() const { return rawData.gyro; }
    const int* rawMag() const { return rawData.mag; }
    const long* rawDMPQuat() const { return rawData.dmpQuat; }
    const float accX() const { return acc[0]; }
    const float accY() const { return acc[1]; }
    const float accZ() const { return acc[2]; }
    const float gyroX() const { return gyro[0]; }
    const float gyroY() const { return gyro[1]; }
    const float gyroZ() const { return gyro[2]; }
    const float magX() const { return mag[0]; }
    const float magY() const { return mag[1]; }
    const float magZ() const { return mag[2]; }
    const float quatW() const { return quat[0]; }
    const float quatX() const { return quat[1]; }
    const float quatY() const { return quat[2]; }
    const float quatZ() const { return quat[3]; }
private:
    MPU9250_DMP dmp;
    DMPRawData rawData;
    float acc[3];    
    float gyro[3];    
    float mag[3];    
    float quat[4];    

}; // IMU

inline void calcAccByDMP(MPU9250_DMP& dmp, float result[]) {
    result[0] = dmp.calcAccel(dmp.ax);
    result[1] = dmp.calcAccel(dmp.ay);
    result[2] = dmp.calcAccel(dmp.az);
}

inline void calcGyroByDMP(MPU9250_DMP& dmp, float result[]) {
    result[0] = dmp.calcGyro(dmp.gx);
    result[1] = dmp.calcGyro(dmp.gy);
    result[2] = dmp.calcGyro(dmp.gz);
}

inline void calcMagByDMP(MPU9250_DMP& dmp, float result[]) {
    result[0] = dmp.calcMag(dmp.mx);
    result[1] = dmp.calcMag(dmp.my);
    result[2] = dmp.calcMag(dmp.mz);
}

inline void calcQuatByDMP(MPU9250_DMP& dmp, float result[]) {
    result[0] = dmp.calcQuat(dmp.qw);
    result[1] = dmp.calcQuat(dmp.qx);
    result[2] = dmp.calcQuat(dmp.qy);
    result[3] = dmp.calcQuat(dmp.qz);
}

} // imu
#endif // __IMU_IMU_H
