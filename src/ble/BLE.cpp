#include "BLE.h"
#include "Profiles.h"

namespace ble {

    BLE::BLE() { 
        descripter = new BLE2902();
        serverCallback = new MyServerCallbacks();
        buttonOperarionCharacteristicCallback = new MyCharacteristicCallbacks();
    }

    BLE::~BLE() { 
        delete buttonOperarionCharacteristicCallback;
        delete serverCallback;
        delete descripter;
        delete advertising;
        delete buttonOperarionCharacteristic;
        delete advertising;
        delete buttonService;
        delete server;
    }

    bool BLE::Initialize() {
        BLEDevice::init("M5Stack");
        // create server
        server = BLEDevice::createServer();
        server->setCallbacks(serverCallback);
        // create service
        buttonService = server->createService(profiles::services::Button);
        buttonOperarionCharacteristic = buttonService->createCharacteristic(
            profiles::characteristics::ButtonOperation,
            BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
        // set descripter
        buttonOperarionCharacteristic->addDescriptor(descripter);
        buttonOperarionCharacteristic->setCallbacks(buttonOperarionCharacteristicCallback);
        return true;
    }

    bool BLE::Start() {
        buttonService->start();
        advertising = server->getAdvertising();
        advertising->addServiceUUID(profiles::services::Button);
        advertising->start();
        return true;
    }
}