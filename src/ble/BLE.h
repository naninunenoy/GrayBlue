#ifndef __BLE_BLE_H
#define __BLE_BLE_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include "BLEServiceSet.h"

namespace ble {

class BLE {
public:
    explicit BLE();
    ~BLE();
    bool Initialize();
    bool Start();
    BLECharacteristic& GetButtonCharacteristic() const;
    BLECharacteristic& GetNineAxisCharacteristic() const;
private:
    BLEServer* server;
    BLEServiceSet* buttonSet;
    BLEServiceSet* nineAxisSet;
    BLEAdvertising* advertising;
};

}
#endif // __BLE_BLE_H
