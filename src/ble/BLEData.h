#ifndef __BLE_BLE_DATA_H
#define __BLE_BLE_DATA_H 

#include<Arduino.h>

namespace ble {

#define BLE_BUTTON_DATA_LEN 4
struct ButtonData {
    uint8_t btnPress;
    uint8_t btnCode;
    uint16_t pressTime;
}; // ButtonData

#define BLE_IMU_DATA_LEN 52
struct IMUData {
    uint32_t accX;
    uint32_t accY;
    uint32_t accZ;
    uint32_t gyroX;
    uint32_t gyroY;
    uint32_t gyroZ;
    uint32_t magX;
    uint32_t magY;
    uint32_t magZ;
    uint32_t quatW;
    uint32_t quatX;
    uint32_t quatY;
    uint32_t quatZ;
}; // IMUData

} // ble
#endif // __BLE_BLE_DATA_H
