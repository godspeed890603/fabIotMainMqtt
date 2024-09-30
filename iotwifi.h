#ifndef IOTWIFI_H
#define IOTWIFI_H

//https://github.com/esp8266/Arduino/blob/master/cores/esp8266/IPAddress.cpp

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "ReadSetting.h"
#include <ESP8266mDNS.h>//V1.11
#include <WiFiUdp.h>//V1.11
#include <ArduinoOTA.h>//V1.11



class iotWifi {       // The class
  public:             // Access specifier
    float wifiRssi = 0.0 ;
    String ipAdress;
    ReadSetting setting;
    String macAddress;
    uint8_t ip_array[4];
    uint8_t gateway_array[4];
    uint8_t subnet_array[4];
    uint8_t dns_array[4];


    String ssid;
    String pwd;
    int reconnectInterval;
    bool isDhcp;

    IPAddress ip;
    IPAddress gateway;
    IPAddress subnet;
    IPAddress dns;

    
    void initialSetting(ReadSetting tmpSetting);
    void WifiReset();
    void initialWifi();
    void WifiOTA();//V1.11
    wl_status_t getWifiStatus();
    float getWifiRssi();
 
    String getIpAddress();
    String getmacAddress();
    iotWifi();

};


#endif /* IOTWIFI_H */
//#endif /* GETTIME_H */
