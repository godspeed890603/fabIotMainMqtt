#ifndef __SHTXX_H__
#define __SHTXX_H__

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"
// #include "DFRobot_SHT20.h"
#include "ReadSetting.h"
#include "iotWebAction.h"
#include "iotwifi.h"
#include "const.h"



class iotShtXX {       // The class
  public:             // Access specifier
   
    String DH1;
    String DT1;

    float offset_t; //= 1.0; 
    float offset_h; //= 0.0;
    bool readShtXX();
    void initialShtXX(); 
    iotWebAction setUploadData(int uploadType,ReadSetting iotReadSetting, iotWifi fabIotWifi);
    int uploadShtXX(iotWebAction DataAction);
  private:
    String getHCalibration(float h);
    String getTCalibration(float t);
};

#endif


