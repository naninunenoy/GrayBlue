#ifndef __INPUT_BUTTON_CHECK_H
#define __INPUT_BUTTON_CHECK_H 

#include <M5Stack.h>
#include <map>

namespace input {
enum Btn { BtnA = 0x01, BtnB = 0x02, BtnC = 0x04 };
enum BtnState { BtnStateRelease = 0, BtnStatePress = 1,  };
class ButtonCheck {
public:
    explicit ButtonCheck();
    ~ButtonCheck();
    bool update(M5Stack& runningDevice, uint8_t& updated);
    BtnState getBtnState(Btn of) const;
private:
    bool checkButton(Btn of, M5Stack& device);
    BtnState getCurrentDeviceBtnState(Btn of, M5Stack& device) const;
    std::map<Btn, BtnState> buttonStateMap;
}; // Button

} // input

#endif // __INPUT_BUTTON_CHECK_H
