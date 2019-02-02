#ifndef __BLE_BLE_H
#define __BLE_BLE_H

#include <M5Stack.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

namespace ble {

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) { /* Do Nothing */ };
    void onDisconnect(BLEServer* pServer) { /* Do Nothing */ }
};

class MyCharacteristicCallbacks: public BLECharacteristicCallbacks {
    void onRead(BLECharacteristic *pCharacteristic) { /* Do Nothing */ }
    void onWrite(BLECharacteristic *pCharacteristic) { /* Do Nothing */ }
};

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
    MyServerCallbacks* serverCallback;
    MyCharacteristicCallbacks* buttonOperarionCharacteristicCallback;
};

}
#endif // __BLE_BLE_H