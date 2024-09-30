#ifndef IOTWEBACTION_H
#define IOTWEBACTION_H

#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include "iotDataDht.h"
#include "iotDataByz08.h"
#include "iotDataPms.h"
#include "iotDatawifi.h"
#include "iotDataVolt.h"
#include "iotDataSht.h"
//#include "iotShtxx.h"


#include "ReadSetting.h"


class iotWebAction{
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

        int uploadData(String webHtml);
        iotWebAction();
        iotWebAction(ReadSetting tempSetting);
        String getUploadWebHtml(int uploadType);
        ~iotWebAction();
};

#endif /* IOTWEBACTION_H */
