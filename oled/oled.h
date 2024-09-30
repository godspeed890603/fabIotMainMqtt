/* Oled ss1306 control
oled.h
 */

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 0  // GPIO0

static Adafruit_SSD1306 OLED(OLED_RESET);

class iotOled{
    public:
        void initialOLED();
        void DisplayText(String displayText);
        //Adafruit_SSD1306* OLED1;
        void DisplayOLEDIP(String mobileIpAddress);
        void DisplayDHT(String mobileIpAddress,String DH,String DT,int httpcode,int* loopchange);
};