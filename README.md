GrayBlue 
====

<img src="https://github.com/naninunenoy/GrayBlue/blob/doc/doc/icon.png" width="200" />

This is M5Stack **Gray** firmware to notify 9DOF motion sensor(MPU-9250) data by **Blue**tooth Low Enagy.

Therefore <img src="https://img.shields.io/badge/Gray-Blue-blue.svg?labelColor=lightGray" />.

## Description

### IMU
MPU-9250 provide these data.
 * acceleration (xyz) [mg]
 * gyro (xyz) [deg/s]
 * magnetic force (xyz) [mG]
 * quaternion (wxyz) []

Quaternion is calculated from acc and gyro by DMP of MPU-9250.
These 13(3+3+3+4) data are notified by BLE.

### Front 3 buttons
Press or release 3 buttons on front is also notified by BLE.

### BLE
Above data are notified by BLE Gatt.

#### 9-DOF data profile
 * Service UUID: `c87ace96-3523-11e9-b210-d663bd873d93`
 * Characteristics 
    - UUID: `c87ad148-3523-11e9-b210-d663bd873d93`
    - type: 52 byte binary array. (13 `float` value)
    - format: 
       - accX [0:3]
       - accY [4:7]
       - accZ [8:11]
       - gyroX [12:15]
       - gyroY [16:19]
       - gyroZ [20:23]
       - magX [24:27]
       - magY [28:31]
       - magZ [32:35]
       - quatW [36:39]
       - quatX [40:43]
       - quatY [44:47]
       - quatZ [48:51]

#### Button event profile
 * Service UUID: `de4c3b20-26ea-11e9-ab14-d663bd873d93`
 * Characteristics 
    - UUID: `de4c4016-26ea-11e9-ab14-d663bd873d93`
    - type: 4 byte value
    - format:
       - isPressed [0] (pressed=`1`/release=`0`)
       - buttonType [1] (left=`'A'`/center=`'B'`/right=`'C'`)
       - pressTime [2:3] (milliSeconds. On button press, value=`0`.)

## Demo
Applied the notified quaternion to the virtual object with Unity.

<img src="https://github.com/naninunenoy/GrayBlue/blob/doc/doc/demo.gif" width="200" />

## Install
This project use [PlatformIO](https://platformio.org/).

If you try to build and write to your M5Stack Gray, you need to install PlatformIO environment on your PC.

## Library
 * M5Stack
    - https://github.com/m5stack/M5Stack
    - [LICENSE](https://github.com/m5stack/M5Stack/blob/master/LICENSE)
 * SparkFun_MPU-9250-DMP_Arduino_Library
    - https://github.com/sparkfun/SparkFun_MPU-9250-DMP_Arduino_Library
    - [LICENSE](https://github.com/sparkfun/SparkFun_MPU-9250-DMP_Arduino_Library/blob/master/LICENSE.md)

## Licence
[MIT](https://github.com/naninunenoy/GrayBlue/blob/master/LICENSE)

## Author
[@naninunenoy](https://github.com/naninunenoy)
