#include "ButtonCheck.h"

namespace input {
    ButtonCheck::ButtonCheck() {
        buttonStateMap.insert(std::make_pair(BtnA, BtnStateRelease));
        buttonStateMap.insert(std::make_pair(BtnB, BtnStateRelease));
        buttonStateMap.insert(std::make_pair(BtnC, BtnStateRelease));
    }

    ButtonCheck::~ButtonCheck() { }

    bool ButtonCheck::update(M5Stack& runningDevice, uint8_t& updated) {
        updated = 0;
        if (checkButton(BtnA, runningDevice)) {
            updated |= BtnA;
        }
        if (checkButton(BtnB, runningDevice)) {
            updated |= BtnB;
        }
        if (checkButton(BtnC, runningDevice)) {
            updated |= BtnC;
        }
        return updated != 0;
    }

    BtnState ButtonCheck::getBtnState(Btn of) const { 
        auto itr = buttonStateMap.find(of);
        if (itr == buttonStateMap.end()) {
            return BtnStateRelease; /// not found
        }
        return itr->second;
    }

    bool ButtonCheck::checkButton(Btn of, M5Stack& device) {
        BtnState previous = getBtnState(of);
        BtnState current = getCurrentDeviceBtnState(of, device);
        if (previous == current) {
            return false; // not changed
        }
        buttonStateMap[of] = current;
        return true;
    }

    BtnState ButtonCheck::getCurrentDeviceBtnState(Btn of, M5Stack& device) const {
        switch (of) {
        case BtnA: return (device.BtnA.isPressed() == 0) ? BtnStateRelease : BtnStatePress;
        case BtnB: return (device.BtnB.isPressed() == 0) ? BtnStateRelease : BtnStatePress;
        case BtnC: return (device.BtnC.isPressed() == 0) ? BtnStateRelease : BtnStatePress;
        }
        return BtnStateRelease;
    }
} // imu