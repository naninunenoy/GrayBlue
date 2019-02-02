#ifndef __BLE_BLE_H
#define __BLE_BLE_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

namespace ble {

class BLE {
public:
    explicit BLE();
    ~BLE();
    bool Initialize();
    bool Start();
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