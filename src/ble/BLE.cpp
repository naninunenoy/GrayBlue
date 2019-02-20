#include <BLE2902.h>
#include "BLE.h"
#include "Profiles.h"

namespace ble {

    BLE::BLE() { }

    BLE::~BLE() { 
        delete this->descripter;
        delete this->advertising;
        delete this->nineAxisSet;
        delete this->buttonSet;
        delete this->server;
    }

    bool BLE::Initialize() {
        BLEDevice::init("M5Stack");
        // create server
        this->server = BLEDevice::createServer();
        this->descripter = new BLE2902();
        // create service
        this->buttonSet = new BLEServiceSet(this->server);
        this->buttonSet->CreateService(
            profiles::services::Button,
            new const char*[1] { profiles::characteristics::ButtonOperation },
            1,
            this->descripter
        );
        this->nineAxisSet = new BLEServiceSet(this->server);
        this->nineAxisSet->CreateService(
            profiles::services::NineAxis,
            new const char*[1] { profiles::characteristics::NineAxisData },
            1,
            this->descripter
        );
        // create advertising
        this->advertising = this->server->getAdvertising();
        this->advertising->addServiceUUID(profiles::services::Button);
        this->advertising->addServiceUUID(profiles::services::NineAxis);
        return true;
    }

    bool BLE::Start() {
        this->buttonSet->StartService();
        this->nineAxisSet->StartService();
        this->advertising->start();
        return true;
    }

    BLECharacteristic& BLE::GetButtonCharacteristic() const {
        return *(this->buttonSet->GetCharacteristicOf(
            profiles::characteristics::ButtonOperation)); 
    }

    BLECharacteristic& BLE::GetNineAxisCharacteristic() const {
        return *(this->nineAxisSet->GetCharacteristicOf(
            profiles::characteristics::NineAxisData)); 
    }
}
