#include "BLE.h"
#include "Profiles.h"

namespace ble {

    BLE::BLE() { }

    BLE::~BLE() { 
        delete descripter;
        delete advertising;
        delete buttonOperarionCharacteristic;
        delete advertising;
        delete buttonService;
        delete server;
    }

    void BLE::Initialize() {
        BLEDevice::init("M5Stack");
        // create server
        server = BLEDevice::createServer();
        // create service
        buttonService = server->createService(profiles::services::Button);
        buttonOperarionCharacteristic = buttonService->createCharacteristic(
            profiles::characteristics::ButtonOperation,
            BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
        // set descripter
        descripter = new BLE2902();
        buttonOperarionCharacteristic->addDescriptor(descripter);
    }

    void BLE::Start() {
        buttonService->start();
        advertising = server->getAdvertising();
        advertising->addServiceUUID(profiles::services::Button);
        advertising->start();
    }
}