#include "ButtonCheck.h"

namespace input {
    ButtonCheck::ButtonCheck() {
        updateFlag = 0;
        for(int i = 0; i < INPUT_BTN_NUM; i++) {
            buttonStateMap.insert(std::make_pair(AllBtns[i], BtnStateRelease));
            buttonPressStartTimeMap.insert(std::make_pair(AllBtns[i], 0));
            buttonPressTimeMap.insert(std::make_pair(AllBtns[i], 0));
        }
    }

    ButtonCheck::~ButtonCheck() { }

    bool ButtonCheck::containsUpdate(M5Stack& runningDevice) {
        uint32_t curretnTime = millis();
        updateFlag = 0;
        for(int i = 0; i < INPUT_BTN_NUM; i++) {
            const Btn btn = AllBtns[i];
            const BtnState ithink = getBtnState(btn);
            if (isButtonStateChanged(btn, ithink, runningDevice)) {
                updateFlag |= btn;
                // release to press
                if (ithink == BtnStateRelease) {
                    buttonPressStartTimeMap[btn] = curretnTime;
                    buttonPressTimeMap[btn] = 0;
                }
                // press to release
                if (ithink == BtnStatePress) {
                    const auto pressStartItr = buttonPressStartTimeMap.find(btn);
                    if (pressStartItr != buttonPressStartTimeMap.end()) {
                        buttonPressTimeMap[btn] = curretnTime - pressStartItr->second;
                    }
                }
            }
        }
        return updateFlag != 0;
    }

    bool ButtonCheck::isBtnUpdate(Btn of) const {
        return (updateFlag & of) != 0;
    }

    BtnState ButtonCheck::getBtnState(Btn of) const { 
        const auto itr = buttonStateMap.find(of);
        if (itr == buttonStateMap.end()) {
            return BtnStateRelease; /// not found
        }
        return itr->second;
    }

    uint32_t ButtonCheck::getBtnPressTime(Btn of) const {
        const auto itr = buttonPressTimeMap.find(of);
        if (itr == buttonPressTimeMap.end()) {
            return 0; /// not found
        }
        return itr->second;
    }

    bool ButtonCheck::isButtonStateChanged(Btn of, BtnState ithink, M5Stack& device) {
        BtnState current = getCurrentDeviceBtnState(of, device);
        if (ithink == current) {
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