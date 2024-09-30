#ifndef __IOTDATAWIFI_H__
#define __IOTDATAWIFI_H__
#include <Arduino.h>

class iotDataWifi {
 public:
  String wifiRssi;
  String ipAdress;
  String macAddress;
  // float* env_noise_db ;
  iotDataWifi();
};
#endif