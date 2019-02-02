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

} // ble
#endif // __BLE_BLE_DATA_H
