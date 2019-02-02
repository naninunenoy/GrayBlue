#include "ButtonCheck.h"

namespace input {
    ButtonCheck::ButtonCheck() {
        updateFlag = 0;
        for(int i = 0; i < INPUT_BTN_NUM; i++) {
            buttonStateMap.insert(std::make_pair(AllBtns[i], BtnStateRelease));
        }
    }

    ButtonCheck::~ButtonCheck() { }

    bool ButtonCheck::containsUpdate(M5Stack& runningDevice) {
        updateFlag = 0;
        for(int i = 0; i < INPUT_BTN_NUM; i++) {
            Btn btn = AllBtns[i];
            if (checkButton(btn, runningDevice)) {
                updateFlag |= btn;
            }
        }
        return updateFlag != 0;
    }

    bool ButtonCheck::isBtnUpdate(Btn of) const {
        return (updateFlag & of) != 0;
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