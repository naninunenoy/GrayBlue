#include "BLEServiceSet.h"

namespace ble {

    BLEServiceSet::BLEServiceSet(BLEServer* bleServer) : bleServer(*bleServer) { }

    BLEServiceSet::~BLEServiceSet() { 
        delete this->bleService;
        for (auto itr : this->bleCharacteristicMap) {
            delete itr.second;
        }
    }
    
    bool BLEServiceSet::CreateService(const char* serviceProfile, 
                                      const char** characteristicProfiles, 
                                      int characteristicProfileCount,
                                      BLEDescriptor* descripter) {                                  
        this->bleService = this->bleServer.createService(serviceProfile);
        for (int i = 0; i < characteristicProfileCount; i++) {
            const char* profile = characteristicProfiles[i];
            BLECharacteristic* characteristic = this->bleService->createCharacteristic(
                profile,
                BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
            );
            characteristic->addDescriptor(descripter);
            this->bleCharacteristicMap.insert(std::make_pair(profile, characteristic));
        }
        return true;
    }

    BLECharacteristic* BLEServiceSet::GetCharacteristicOf(const char* of) const {
        const auto itr = this->bleCharacteristicMap.find(of);
        if (itr == this->bleCharacteristicMap.end()) {
            return nullptr;
        }
        return itr->second;
    }
}
