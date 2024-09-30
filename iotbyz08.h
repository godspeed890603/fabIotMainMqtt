#ifndef __IOTBYZ08_H__
#define __IOTBYZ08_H__
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "iotWebAction.h"
#include "iotwifi.h"
#include "const.h"

const int dataLen=8;
const char  byz08ReadCmd[8] = { 0x01, 0x03, 0x00 ,0x00, 0x00, 0x01,0x84, 0x0A};
#define D7 13
#define D8 15

class iotbyz08 {       // The class
  public:             // Access specifier
    int incomingDataByte[dataLen];
    SoftwareSerial *SerialBYZ08;
    void begin();
    float getDB();
    iotWebAction setUploadData(int uploadType,ReadSetting iotReadSetting, iotWifi fabIotWifi);
    int uploadNoise(iotWebAction DataAction);
    float env_noise;
    float max_env_noise;
    private:
    void getData();  
};
#endif

