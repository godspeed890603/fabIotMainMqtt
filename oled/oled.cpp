/* Oled ss1306 control
oled.cpp
 */
#include "oled.h"

/*Oled initial */
void iotOled::initialOLED(){
  //OLED1=new Adafruit_SSD1306(OLED_RESET);
  Serial.println("initial OLED!");
  OLED.begin();
  OLED.clearDisplay();
  OLED.display();
}

/*oled display ip */
void iotOled::DisplayOLEDIP(String mobileIpAddress){
  OLED.begin();
  OLED.clearDisplay();
  OLED.display();
  //Add stuff into the 'display buffer'
  OLED.setTextWrap(false);
  OLED.setTextSize(1);
  OLED.setTextColor(WHITE);
 
  OLED.setCursor(0,0);
  OLED.println("Wifi: " + mobileIpAddress);
  OLED.display(); //output 'display buffer' to screen  
  //OLED.startscrollleft(0x00, 0x0F); //make display scroll 
  //delay(1000);
  // OLED.clearDisplay();
   //delay(5000);
}

/*oled display text */
void iotOled::DisplayText(String displayText){
  OLED.begin();
  OLED.clearDisplay();
  OLED.display();
  //Add stuff into the 'display buffer'
  OLED.setTextWrap(false);
  OLED.setTextSize(1);
  OLED.setTextColor(WHITE);
 
  OLED.setCursor(0,0);
  OLED.println(displayText);
  OLED.display(); //output 'display buffer' to screen  
  //OLED.startscrollleft(0x00, 0x0F); //make display scroll 
  //delay(1000);
  // OLED.clearDisplay();
   //delay(5000);
}

/*oled dispaly Dht information */
void iotOled::DisplayDHT(String mobileIpAddress,String DH,String DT,int httpCode,int* loopchange){
  *loopchange=*loopchange+1;
  //Serial.println(*loopchange);
  if (*loopchange>9)
      *loopchange=0;
  
  OLED.begin();
  OLED.clearDisplay();
  OLED.display();

  //Add stuff into the 'display buffer'
  OLED.setTextWrap(false);
  OLED.setTextSize(1);
  OLED.setTextColor(WHITE);
 
  OLED.setCursor(0,0);
  OLED.println("Wifi: " + mobileIpAddress);
  OLED.setCursor(0,8);
  OLED.println("Humidity: " + DH + " %");
  OLED.setCursor(0,17);
  OLED.println("Temperature: " + DT + " *C");
  OLED.display(); //output 'display buffer' to screen  

  OLED.setCursor(0,25);
  OLED.println("httpCode: " + String(httpCode) + " " + String(*loopchange));
  OLED.display(); //output 'display buffer' to screen
}
