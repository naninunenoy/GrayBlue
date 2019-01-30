#ifndef __IMU_DMP_RAW_DATA_H
#define __IMU_DMP_RAW_DATA_H 

#include<SparkFunMPU9250-DMP.h>

namespace imu {
struct DMPRawData {
    unsigned long time;
    int acc[3];//xyz
    int gyro[3];//xyz
    int mag[3];//xyz
    long dmpQuat[4];//wxyz
    
    explicit DMPRawData() {
        this->time = 0;
        for (int i=0; i<3; i++) { this->acc[i] = 0; }
        for (int i=0; i<3; i++) { this->gyro[i] = 0; }
        for (int i=0; i<3; i++) { this->mag[i] = 0; }
        for (int i=0; i<4; i++) { this->dmpQuat[i] = 0; }
    }
    ~DMPRawData() { }
    void fromDMP(const MPU9250_DMP& dmp) {
        this->time = dmp.time;
        this->acc[0] = dmp.ax;
        this->acc[1] = dmp.ay;
        this->acc[2] = dmp.az;
        this->gyro[0] = dmp.gx;
        this->gyro[1] = dmp.gy;
        this->gyro[2] = dmp.gz;
        this->mag[0] = dmp.mx;
        this->mag[1] = dmp.mx;
        this->mag[2] = dmp.mx;
        this->dmpQuat[0] = dmp.qw;
        this->dmpQuat[1] = dmp.qx;
        this->dmpQuat[2] = dmp.qy;
        this->dmpQuat[3] = dmp.qz;
    }
}; // IMURawData

} // imu

#endif // __IMU_DMP_RAW_DATA_H
