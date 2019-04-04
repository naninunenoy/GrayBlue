#include <M5Stack.h>
#include "imu/IMU.h"
#include "ble/BLE.h"
#include "ble/BLEData.h"
#include "input/ButtonCheck.h"

#define SERIAL_PRINT 0

void printSerial(unsigned long t, const float a[], const float g[], const float m[], const float q[]);
void printLcd(unsigned long t, const float a[], const float g[], const float m[], const float q[]);

imu::IMU _imu;
ble::BLE _ble;
input::ButtonCheck _button;

void setup() {
    M5.begin();
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(GREEN ,BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("awaken...");
    if (Wire.begin()) {
        Wire.setClock(400000UL); // i2c 400kHz
        M5.Lcd.println("i2c OK!");
    } else {
        M5.Lcd.println("i2c NG!!!");
    }
    if (_imu.Setup(50)) { // 50Hz
        M5.Lcd.println("imu OK!");
    } else {
        M5.Lcd.println("imu NG!!!");
    }
    if (_ble.Initialize() && _ble.Start()) { // 50Hz
        M5.Lcd.println("ble OK!");
    } else {
        M5.Lcd.println("ble NG!!!");
    }
#if SERIAL_PRINT
    //Serial.begin(115200);
    Serial.println("serial OK!");
    M5.Lcd.println("serial OK!");
#endif
    M5.Lcd.fillScreen(BLACK);
}

void loop() {
    // Button condition
    if (_button.containsUpdate(M5)) {
        for (int i = 0; i < INPUT_BTN_NUM; i++) {
            input::Btn btn = input::AllBtns[i];
            if (_button.isBtnUpdate(btn)) {
                input::BtnState btnState = _button.getBtnState(btn);
                uint8_t btnCode = input::toBtnCode(btn);
                uint8_t btnPress = input::toBtnPress(btnState);
                uint32_t btnPressTime = (btnPress == 0) ? _button.getBtnPressTime(btn) : 0;
#if SERIAL_PRINT
                Serial.print(btnCode); Serial.print(" "); 
                Serial.print(btnPress); Serial.print(" "); 
                Serial.println(btnPressTime);
#endif
                ble::ButtonData data;
                data.btnCode = btnCode;
                data.btnPress = btnPress;
                data.pressTime = (uint16_t)btnPressTime;
                _ble.GetButtonCharacteristic().setValue((uint8_t*)&data, BLE_BUTTON_DATA_LEN);
                _ble.GetButtonCharacteristic().notify();
            }
        }
    }
    // IMU condition
    if (_imu.Update()) {
        ble::IMUData data;
        memcpy(&data.accX, _imu.getAcc(), sizeof(float)*3);
        memcpy(&data.gyroX, _imu.getGyro(), sizeof(float)*3);
        memcpy(&data.magX, _imu.getMag(), sizeof(float)*3);
        memcpy(&data.quatW, _imu.getQuat(), sizeof(float)*4);
        _ble.GetNineAxisCharacteristic().setValue((uint8_t*)&data, BLE_IMU_DATA_LEN);
        _ble.GetNineAxisCharacteristic().notify();
#if SERIAL_PRINT
        printSerial(_imu.getTime(), _imu.getAcc(), _imu.getGyro(), _imu.getMag(), _imu.getQuat());
#endif
        printLcd(_imu.getTime(), _imu.getAcc(), _imu.getGyro(), _imu.getMag(), _imu.getQuat());
    }
     // device update
    M5.update();
}

void printLcd(unsigned long t, const float a[], const float g[], const float m[], const float q[]) {
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("     x       y       z ");
  M5.Lcd.setCursor(0,  24);
  M5.Lcd.printf("% 6d  % 6d  % 6d     mg   \r\n",  (int)(1000*a[0]), (int)(1000*a[1]), (int)(1000*a[2]));
  M5.Lcd.setCursor(0,  44);
  M5.Lcd.printf("% 6d  % 6d  % 6d     o/s  \r\n", (int)(g[0]), (int)(g[1]), (int)(g[2]));
  M5.Lcd.setCursor(0,  64);
  M5.Lcd.printf("% 6d  % 6d  % 6d     mG    \r\n",  (int)(m[0]), (int)(m[1]), (int)(m[2]));

  M5.Lcd.setCursor(0,  100);
  M5.Lcd.print("   qw      qx      qy      qz ");
  M5.Lcd.setCursor(0,  128);
  M5.Lcd.printf(" %2.3f  % 2.3f  %2.3f  %2.3f   \r\n", q[0], q[1], q[2], q[3]);
}

#if SERIAL_PRINT
void printSerial(unsigned long t, const float a[], const float g[], const float m[], const float q[]) {
    return;
    Serial.print(t); Serial.print(",");
    Serial.print(a[0], 3); Serial.print(",");
    Serial.print(a[1], 3); Serial.print(",");
    Serial.print(a[2], 3); Serial.print(",");
    Serial.print(g[0], 3); Serial.print(",");
    Serial.print(g[1], 3); Serial.print(",");
    Serial.print(g[2], 3); Serial.print(",");
    Serial.print(m[0], 3); Serial.print(",");
    Serial.print(m[1], 3); Serial.print(",");
    Serial.print(m[2], 3); Serial.print(",");
    Serial.print(q[0], 3); Serial.print(",");
    Serial.print(q[1], 3); Serial.print(",");
    Serial.print(q[2], 3); Serial.print(",");
    Serial.print(q[3], 3); Serial.println();
}
#endif