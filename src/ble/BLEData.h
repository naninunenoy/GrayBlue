#ifndef __BLE_BLE_DATA_H
#define __BLE_BLE_DATA_H 

#include<Arduino.h>

namespace ble {

#define BLE_BUTTON_DATA_LEN 4
union ButtonData {
    uint8_t rawData[BLE_BUTTON_DATA_LEN] = { 0 };
    struct {
        uint16_t btnPress : 1;
        uint16_t btnCode : 15;
        uint16_t pressTime;
    } data;
}; // ButtonData

} // ble
#endif // __BLE_BLE_DATA_H
