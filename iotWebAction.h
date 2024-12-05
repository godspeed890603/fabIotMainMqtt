#ifndef IOTWEBACTION_H
#define IOTWEBACTION_H

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

#include "iotDataByz08.h"
#include "iotDataDht.h"
#include "iotDataPms.h"
#include "iotDataSht.h"
#include "iotDataVolt.h"
#include "iotDatawifi.h"
#include "./src/uuid/uuidgenerator.h"
// #include "iotShtxx.h"

#include "ReadSetting.h"

class iotWebAction {
 public:
  iotDataDht DhtData;
  iotDataByz08 BYZ08Data;
  iotDataPms PmsData;
  iotDataWifi WifiData;
  iotDataVolt VoltData;
  iotDataShtXX ShtXXData;
  String SENSOR_ID;
  String machine_ID;

  String mount_Device;
  int uploadType;
  String webserverHtml_Header;
  String getPmsJson(int);  // 2024/10/14 FOR MQTT

  int uploadData(String webHtml);
  iotWebAction();
  iotWebAction(ReadSetting tempSetting);
  String getUploadWebHtml(int uploadType);
  ~iotWebAction();
};

#endif /* IOTWEBACTION_H */
