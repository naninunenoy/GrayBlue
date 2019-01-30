#ifndef __IMU_IMU_H // 先頭
#define __IMU_IMU_H 

#include <SparkFunMPU9250-DMP.h>
#include "DMPRawData.h"

namespace imu {
class IMU {
public:
    explicit IMU();
    ~IMU();
    bool Setup(unsigned short sampleRate);
    bool Update();

    const unsigned long getTime() const { return this->dmp.time; }
    const int* getRawAcc() const { return this->rawData.acc; }
    const int* getRawGyro() const { return this->rawData.gyro; }
    const int* getRawMag() const { return this->rawData.mag; }
    const long* getRawDMPQuat() const { return this->rawData.dmpQuat; }
    const float* getAcc() const { return this->acc; }
    const float* getGyro() const { return this->gyro; }
    const float* getMag() const { return this->mag; }
    const float* getQuat() const { return this->quat; }
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
