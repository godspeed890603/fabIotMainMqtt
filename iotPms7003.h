#ifndef __IOTPMS7003_H__
#define __IOTPMS7003_H__
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "ReadSetting.h"
#include "iotWebAction.h"
#include "iotwifi.h"
#include "const.h"
#include "./src/mqtt/MQTTClient.h"
//SoftwareSerial SerialPMS5003(D6, D5);
//SoftwareSerial SerialPMS7003(D4, D3);
#define D6 12
#define D5 14

const int MAX_FRAME_LEN = 64;
const bool DEBUG = false;


struct singlePmsRangeData_struct{
    uint16_t range_0_3um=0;//rawGt0_3um-rawGt0_5um
    uint16_t range_0_5um=0;//range_0_5um-rawGt1_0um
    uint16_t range_1_0um=0;//rawGt1_0um-rawGt2_5um
    uint16_t range_2_5um=0;//rawGt2_5um-rawGt5_0um
    uint16_t range_5_0um=0;//range_5_0um-rawGt10_0um
    uint16_t range_10_0um=0;
};


struct PMS7003_framestruct {
    uint8_t  frameHeader[2];
    uint16_t frameLen = MAX_FRAME_LEN;
    uint16_t concPM1_0_CF1;
    uint16_t concPM2_5_CF1;
    uint16_t concPM10_0_CF1;
    uint16_t concPM1_0_amb;
    uint16_t concPM2_5_amb;
    uint16_t concPM10_0_amb;
    uint16_t rawGt0_3um;
    uint16_t rawGt0_5um;
    uint16_t rawGt1_0um;
    uint16_t rawGt2_5um;
    uint16_t rawGt5_0um;
    uint16_t rawGt10_0um;
    uint8_t  version;
    uint8_t  errorCode;
    uint16_t checksum;
};

class iotPms7003 {
    private:
        int incomingByte = 0; // for incoming serial data
        
        char frameBuf[MAX_FRAME_LEN];
        int detectOff = 0;
        int frameLen = MAX_FRAME_LEN;
        bool inFrame = false;
        char printbuf[256];
        uint16_t calcChecksum = 0;
        int pmsLoopchange=0;

        

    public:
        PMS7003_framestruct thisFrame;
        singlePmsRangeData_struct singlePmsRangeData;
        SoftwareSerial* SerialPMS7003;

        uint16_t max_range_0_3um=0;//rawGt0_3um-rawGt0_5um
        uint16_t max_range_0_5um=0;//range_0_5um-rawGt1_0um
        uint16_t max_range_1_0um=0;//rawGt1_0um-rawGt2_5um
        uint16_t max_range_2_5um=0;//rawGt2_5um-rawGt5_0um
        uint16_t max_range_5_0um=0;//range_5_0um-rawGt10_0um
        uint16_t max_range_10_0um=0;
        uint16_t um_total=0;//V1.10


        bool pms_read();
        void initialPms();
        void calculateRangePaticle();
        void setMaxRange();
        void getMaxRange();
        void clearMaxRange();
        int uploadPms(iotWebAction DataAction);
        bool uploadMqttPms(iotWebAction DataAction,MQTTClient* mqttClientHandler);
        //int iotDataAction(int uploadType,iotPms7003 fabPms7003,ReadSetting iotReadSetting,iotWifi fabIotWifi);
        iotWebAction setUploadData(int uploadType,ReadSetting iotReadSetting,iotWifi fabIotWifi);
          
    
};
#endif