#ifndef __BLE_BLE_SERVICE_SET_H
#define __BLE_BLE_SERVICE_SET_H

#include <map>
#include <BLEDevice.h>
#include <BLEServer.h>

namespace ble {

class BLEServiceSet {
public:
    explicit BLEServiceSet(BLEServer* bleServer);
    ~BLEServiceSet();
    bool CreateService(const char* serviceProfile, 
                       const char** characteristicProfiles, 
                       int characteristicProfileCount,
                       BLEDescriptor* descripter);
    void StartService() { bleService->start(); }
    void StopService() { bleService->stop(); }
    BLECharacteristic* GetCharacteristicOf(const char* of) const;
private:
    BLEServer& bleServer;
    BLEService* bleService;
    std::map<const char*, BLECharacteristic*> bleCharacteristicMap;
};

}
#endif // __BLE_BLE_SERVICE_SET_H