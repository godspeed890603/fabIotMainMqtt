#ifndef READSETTING_H
#define READSETTING_H

#include <Arduino.h>
//#include "const.h"
#include <StringSplitter.h>
#include <FS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

struct iot_Sensor_struct {
    String id;
    int DataType;
    bool isEnable;
    int actioInterval;
    int uploadLoop;
    String webServerIP;
    String webApString;
    String webserverHtml_Header;
};
struct iot_Dht_Sensor_struct {
    String id;
    int DataType;
    bool isEnable;
    int actioInterval;
    int uploadLoop;
    String webServerIP;
    String webApString;
    String webserverHtml_Header;
    float dht_offset_h;
    float dht_offset_t;
};

struct iot_Sht_Sensor_struct {
    String id;
    int DataType;
    bool isEnable;
    int actioInterval;
    int uploadLoop;
    String webServerIP;
    String webApString;
    String webserverHtml_Header;
    float offset_h;
    float offset_t;
};

struct iot_Volt_Sensor_struct {
    String id;
    int DataType;
    bool isEnable;
    int actioInterval;
    int uploadLoop;
    String webServerIP;
    String webApString;
    String webserverHtml_Header;
    float m;//斜率
    float c;//原點
};

struct iot_Wifi_struct {
    String ssid;
    String pwd;
    bool isEnable;
    bool isDHCP;
    int ReconnectInterval;
};

class ReadSetting{
    public:
        void readSetting();
        void getData(String A);
        void ipStringtoArray(String A);
        void ipToIntrray(String A, int* IpArray);
        void sensorSettingToStruct(String A,iot_Sensor_struct* tmpStu);
        void WifiSettingToStruct(String A,iot_Wifi_struct* tmpStu);
        void dhtSettingToStruct(String A,iot_Dht_Sensor_struct* tmpStu);
        void ShtSettingToStruct(String A,iot_Sht_Sensor_struct* tmpStu);//V1.13
        void voltSettingToStruct(String A,iot_Volt_Sensor_struct* tmpStu);


        iot_Dht_Sensor_struct   stu_sensor_DHT;
        iot_Sensor_struct   stu_sensor_NOISE;
        iot_Sensor_struct   stu_sensor_GYRO;
        iot_Volt_Sensor_struct   stu_sensor_VOLT;
        iot_Sensor_struct   stu_sensor_PMS;
        iot_Sensor_struct   stu_sensor_VHT;
        iot_Wifi_struct     stu_sensor_WIFI;
        iot_Sht_Sensor_struct   stu_sensor_ShtXX;
       

        String SENSOR_ID;
        String version;
        String machine_ID;
        String mount_Device;
        String sensor_DHT;
        String sensor_NOISE;
        String sensor_GYRO;
        String sensor_VOLT;
        String sensor_PMS;
        String sensor_VHT;
        String sensor_SHT;

        //String webserverHtml_Header;

        int ip[4];
        int gateway[4];
        int subnet[4];
        int dns[4];

};
#endif /* READSETTING_H */
