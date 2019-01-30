#include "IMU.h"

namespace imu {
    IMU::IMU() {
        for (int i=0; i<3; i++) { this->acc[i] = 0.0F; }
        for (int i=0; i<3; i++) { this->gyro[i] = 0.0F; }
        for (int i=0; i<3; i++) { this->mag[i] = 0.0F; }
        for (int i=0; i<4; i++) { this->quat[i] = (i>0) ? 0.0F : 1.0F; }
    }

    IMU::~IMU() { }

    bool IMU::Setup() {
        if (dmp.begin() != INV_SUCCESS) {
            return false;
        }
        // setup sensor
        dmp.setSensors(INV_XYZ_GYRO | INV_XYZ_ACCEL | INV_XYZ_COMPASS);
        dmp.setGyroFSR(2000);
        dmp.setAccelFSR(2);
        dmp.setLPF(5);
        dmp.setSampleRate(10);
        dmp.setCompassSampleRate(10);
        // setpu dmp
        dmp.dmpBegin(DMP_FEATURE_6X_LP_QUAT |
                     DMP_FEATURE_GYRO_CAL,
                     10);
        return true;
    }

    bool IMU::Update() {
        if (!dmp.fifoAvailable()) {
            return false;
        }
        if (dmp.dmpUpdateFifo() != INV_SUCCESS) {
            return false;
        }
        if (!dmp.dataReady()) {
            return false;
        }
        // update data
        rawData.fromDMP(dmp);
        calcAccByDMP(dmp, acc);
        calcGyroByDMP(dmp, gyro);
        calcMagByDMP(dmp, mag);
        calcQuatByDMP(dmp, quat);
        return true;
    }
} // imu