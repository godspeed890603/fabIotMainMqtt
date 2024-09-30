#ifndef _IOTVHT_H_
#define _IOTVHT_H_

//https://github.com/esp8266/Arduino/blob/master/cores/esp8266/IPAddress.cpp

#include <Arduino.h>
#include "ReadSetting.h"
#include "iotWebAction.h"
#include "iotwifi.h"
#include "iotVoltSensor.h"
#include "dht21.h"
#include "iotShtxx.h"
#include "const.h"
  


class iotVHT {       // The class
  public:             // Access specifier
    // float VIN = 0.0;
    // void getBaterryVoltage();
    // void initialVoltageDetect();
    // void begin();
    int uploadVHT(iotWebAction DataAction);
    iotWebAction setUploadData(int uploadType,ReadSetting iotReadSetting, iotWifi fabIotWifi \
      ,iotVoltSensor fabVoltSensor,iotShtXX fabShtXXSensor);

  private:
      // float Rp=0.0;
      // const int sampleCount =100; 
      // const float m=0.9947;
      // //const float c=-0.373;  
      // float c=-0.1; 
      // const int voltageSensor = A0; 
      // const int RelyControlPin = D4; 
      // const float Vd = 0.373; 
      // const float Vw = 3.2; 
      // const float R1K=1000.0;
      // const float R220K = 220 * R1K;
      // const float R100K = 100 * R1K;
      // const float R300K = 300 * R1K; 
      // const float R75K = 75 * R1K; 
};


#endif /* IOTVHT_H */
//#endif
