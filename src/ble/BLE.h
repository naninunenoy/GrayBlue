#ifndef __BLE_BLE_H
#define __BLE_BLE_H

#include <M5Stack.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

namespace ble {
class BLE {
public:
    explicit BLE();
    ~BLE();
    void Initialize();
    void Start();
    BLECharacteristic& GetButtonCharacteristic() const { return *buttonOperarionCharacteristic; }
private:
    BLEServer* server;
    BLEService* buttonService;
    BLECharacteristic* buttonOperarionCharacteristic;
    BLEAdvertising* advertising;
    BLEDescriptor* descripter;
};

}
#endif // __BLE_BLE_H