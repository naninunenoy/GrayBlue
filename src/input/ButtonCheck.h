#ifndef __INPUT_BUTTON_CHECK_H
#define __INPUT_BUTTON_CHECK_H 

#include <M5Stack.h>
#include <map>

namespace input {
enum Btn { BtnA = 0x01, BtnB = 0x02, BtnC = 0x04 };
enum BtnState { BtnStateRelease = 0, BtnStatePress = 1,  };

#define INPUT_BTN_NUM 3
static const Btn AllBtns[INPUT_BTN_NUM] = { BtnA, BtnB, BtnC };

class ButtonCheck {
public:
    explicit ButtonCheck();
    ~ButtonCheck();
    bool containsUpdate(M5Stack& runningDevice);
    bool isBtnUpdate(Btn of) const;
    BtnState getBtnState(Btn of) const;
    uint32_t getBtnPressTime(Btn of) const;
private:
    uint8_t updateFlag;
    bool isButtonStateChanged(Btn of, BtnState ithink, M5Stack& device);
    BtnState getCurrentDeviceBtnState(Btn of, M5Stack& device) const;
    std::map<Btn, BtnState> buttonStateMap;
    std::map<Btn, uint32_t> buttonPressStartTimeMap;
    std::map<Btn, uint32_t> buttonPressTimeMap;
}; // Button

inline uint8_t toBtnCode(Btn btn) {
    switch (btn) {
    case BtnA: return 'A';
    case BtnB: return 'B';
    case BtnC: return 'C';
    }
    return '?';
}

inline uint8_t toBtnPress(BtnState btn) {
    if (btn == BtnStatePress) {
        return 1;
    }
    return 0;
}

} // input

#endif // __INPUT_BUTTON_CHECK_H
