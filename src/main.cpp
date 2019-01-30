#include <M5Stack.h>
#include "imu/IMU.h"

#define SERIAL_PRINT 1

void printSerial(unsigned long t, const float a[], const float g[], const float m[], const float q[]);
void printLcd(unsigned long t, const float a[], const float g[], const float m[], const float q[]);

imu::IMU _imu;

void setup() {
    M5.begin();
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(GREEN ,BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("awaken...");
    if (Wire.begin()) {
        M5.Lcd.println("i2c OK!");
    } else {
        M5.Lcd.println("i2c NG!!!");
    }
    if (_imu.Setup(50)) { // 50Hz
        M5.Lcd.println("imu OK!");
    } else {
        M5.Lcd.println("imu NG!!!");
    }
#if SERIAL_PRINT
    Serial.begin(115200);
    Serial.println("serial OK!");
    M5.Lcd.println("serial OK!");
#endif
    M5.Lcd.fillScreen(BLACK);
}

void loop() {
    if (_imu.Update()) {
#if SERIAL_PRINT
        printSerial(_imu.getTime(), _imu.getAcc(), _imu.getGyro(), _imu.getMag(), _imu.getQuat());
#endif
        printLcd(_imu.getTime(), _imu.getAcc(), _imu.getGyro(), _imu.getMag(), _imu.getQuat());
    }
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