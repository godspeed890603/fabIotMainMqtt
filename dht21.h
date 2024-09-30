#ifndef __DHT21_H__
#define __DHT21_H__

#include <Arduino.h>
#include "DHT.h"
#include "ReadSetting.h"
#include "iotWebAction.h"
#include "iotwifi.h"
#include "const.h"
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
// #define DHTPIN 2     // what pin we're connected to


class iotDHT {       // The class
  public:             // Access specifier
    // DHT dht(DHTPIN1, DHTTYPE1);
    // DHT dht;
    //DHT dht(0, 22);
    String DH1;
    String DT1;
    //DHT* dht;
    float offset_t; //= 1.0; 
    float offset_h; //= 0.0;
    //iotDHT();
    bool readDHT();
    void initialDht(); 
    iotWebAction setUploadData(int uploadType,ReadSetting iotReadSetting, iotWifi fabIotWifi);
    int uploadDht(iotWebAction DataAction);
  private:
    String getDHCalibration(float h);
};

#endif


