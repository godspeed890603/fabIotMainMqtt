/* Oled ss1306 control
oled.h
 */
#ifndef __IOTOLEDSH1106_H__
#define __IOTOLEDSH1106_H__

#include <Arduino.h>
#include "iotPms7003.h"
#include "iotbyz08.h"
#include "dht21.h"
#include "iotVoltSensor.h"
#include "iotShtxx.h"
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
#include "SH1106Wire.h"   
#include "SH1106.h"

#define D2 4
#define D1 5
#define i2cAddress 0x3c

static SH1106 OLED1(i2cAddress, D2, D1);     // ADDRESS, SDA, SCL


class iotOledSH1106{
    public:
       
        //SH1106 OLED1();     // ADDRESS, SDA, SCL
        void initialOLEDSH1106();
        void DisplayText(String displayText);
        void DisplaySystemStartText(int poX, int poY,String displayText);
        //Adafruit_SSD1306* OLED1;
        void DisplayIP(String mobileIpAddress);
        //void DisplayDHT(String mobileIpAddress,String DH,String DT,int httpcode,int* loopchange);
        void DisplayDHT(String mobileIpAddress,iotDHT fabIotDht,int httpcode,int* loopchange);
        void DisplayShtXX(String mobileIpAddress,iotShtXX fabShtXXSensor,int httpcode,int* loopchange);
        
        void DisplayPms(String ipAddress,iotPms7003 pms,int httpCode,int* loopchange);
        void DisplayNoise(String ipAddress,iotbyz08 noise,int httpCode,int* loopchange);
        void DisplayVolt(String ipAddress,iotVoltSensor fabVoltSensor,int httpCode,int* loopchange);
};

#endif