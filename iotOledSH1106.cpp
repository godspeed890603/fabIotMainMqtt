/* Oled ss1306 control
oled.cpp
 */
#include "iotOledSH1106.h"

/*Oled initial */
void iotOledSH1106::initialOLEDSH1106() {
  // OLED1=new Adafruit_SSD1306(OLED_RESET);
  Serial.println("initial OLED!");
  // OLED1 =SH1106(i2cAddress, D2, D1);
  OLED1.init();
  OLED1.flipScreenVertically();
  OLED1.setFont(ArialMT_Plain_16);
  // Serial.println("initial OLED2!");
  // Serial.println("initial OLED3!");
  // OLED.begin();
  OLED1.clear();
  // Serial.println("initial OLED4!");
  OLED1.display();
  // Serial.println("initial OLED5!");
}

void iotOledSH1106::DisplaySystemStartText(int poX, int poY,
                                           String displayText) {
  OLED1.setFont(ArialMT_Plain_10);
  OLED1.drawString(poX, poY, displayText);
  OLED1.display();  // output 'display buffer' to screen
}

/*oled display ip */
void iotOledSH1106::DisplayIP(String mobileIpAddress) {
  // OLED.begin();
  OLED1.clear();
  OLED1.display();
  // Add stuff into the 'display buffer'
  OLED1.setFont(ArialMT_Plain_10);
  OLED1.drawString(0, 0, "Wifi: " + mobileIpAddress);
  OLED1.display();  // output 'display buffer' to screen
  // OLED.startscrollleft(0x00, 0x0F); //make display scroll
  // delay(1000);
  //  OLED.clearDisplay();
  // delay(5000);
}

/*oled display text */
void iotOledSH1106::DisplayText(String displayText) {
  // OLED.begin();
  OLED1.clear();
  OLED1.display();
  // Add stuff into the 'display buffer'
  OLED1.drawString(0, 0, displayText);
  OLED1.println(displayText);
  OLED1.display();  // output 'display buffer' to screen
  // OLED.startscrollleft(0x00, 0x0F); //make display scroll
  // delay(1000);
  //  OLED.clearDisplay();
  // delay(5000);
}

/*oled dispaly Dht information */
// void iotOledSH1106::DisplayDHT(String mobileIpAddress,String DH,String DT,int
// httpCode,int* loopchange){
void iotOledSH1106::DisplayDHT(String mobileIpAddress, iotDHT fabIotDht,
                               int httpcode, int* loopchange) {
  *loopchange = *loopchange + 1;
  // Serial.println(*loopchange);
  if (*loopchange >= 10) *loopchange = 0;

  // OLED.begin();
  OLED1.clear();
  OLED1.display();

  // Add stuff into the 'display buffer'
  OLED1.drawString(0, 0, "Wifi: " + mobileIpAddress);
  OLED1.drawString(0, 15, "Humidity: " + fabIotDht.DH1 + " %");
  OLED1.drawString(0, 30, "Temperature: " + fabIotDht.DT1 + " *C");
  // OLED.display(); //output 'display buffer' to screen

  // OLED.setCursor(0,25);
  OLED1.drawString(0, 45,
                   "httpCode: " + String(httpcode) + " " + String(*loopchange));
  OLED1.display();  // output 'display buffer' to screen
}

/*oled dispaly Dht information */
// void iotOledSH1106::DisplayDHT(String mobileIpAddress,String DH,String DT,int
// httpCode,int* loopchange){
void iotOledSH1106::DisplayShtXX(String mobileIpAddress,
                                 iotShtXX fabShtXXSensor, int httpcode,
                                 int* loopchange) {
  *loopchange = *loopchange + 1;
  // Serial.println(*loopchange);
  if (*loopchange >= 10) *loopchange = 0;

  // OLED.begin();
  OLED1.clear();
  OLED1.display();

  // Add stuff into the 'display buffer'
  OLED1.drawString(0, 0, "Wifi: " + mobileIpAddress);
  OLED1.drawString(0, 15, "Sh Humidity: " + fabShtXXSensor.DH1 + " %");
  OLED1.drawString(0, 30, "Sh Temperature: " + fabShtXXSensor.DT1 + " *C");
  // OLED.display(); //output 'display buffer' to screen

  // OLED.setCursor(0,25);
  OLED1.drawString(0, 45,
                   "httpCode: " + String(httpcode) + " " + String(*loopchange));
  OLED1.display();  // output 'display buffer' to screen
}

/*oled dispaly Pms information */
void iotOledSH1106::DisplayPms(String ipAddress, iotPms7003 pms, int httpCode,
                               int* loopchange) {
  Serial.println("------ipAddress;------ " +ipAddress);
                           
  *loopchange = *loopchange + 1;
  // Serial.println(*loopchange);
  if (*loopchange > 9) *loopchange = 0;

  Serial.println("------DisplayPms;------ ");

  OLED1.clear();
  // draw the current demo method
  // demos[demoMode]();

  OLED1.setTextAlignment(TEXT_ALIGN_RIGHT);
  OLED1.drawString(10, 128, String(millis()));

  OLED1.setTextAlignment(TEXT_ALIGN_LEFT);

  OLED1.setFont(ArialMT_Plain_10);
  OLED1.drawString(0, 0,
                   "Ip:" + ipAddress + " hc:" + String(httpCode) + " " +
                       String(*loopchange));
  OLED1.drawString(0, 15,
                   "10u =" + String(pms.max_range_10_0um) +
                       "  5.0u =" + String(pms.max_range_5_0um));
  OLED1.drawString(0, 30,
                   "3.0u =" + String(pms.max_range_2_5um) +
                       "  1.0u =" + String(pms.max_range_1_0um));
  OLED1.drawString(0, 45,
                   "0.5u =" + String(pms.max_range_0_5um) +
                       "  0.3u =" + String(pms.max_range_0_3um));
  // OLED1.drawString(0, 15, "10u ="+String(pms.max_range_10_0um,5) +"  5.0u ="
  // + String(pms.max_range_5_0um,5)); OLED1.drawString(0, 30, "3.0u
  // ="+String(pms.max_range_2_5um,5) +"  1.0u =" +
  // String(pms.max_range_1_0um,5)); OLED1.drawString(0, 45, "0.5u
  // ="+String(pms.max_range_0_5um,5) +"  0.3u =" +
  // String(pms.max_range_0_3um,5));
  // write the buffer to the display
  OLED1.display();

  delay(10);
  // OLED1.drawString(0, 60,"httpCode: " + String(httpCode) + " " +
  // String(*loopchange));
  OLED1.display();  // output 'display buffer' to screen
}

/*oled dispaly Pms information */
void iotOledSH1106::DisplayNoise(String ipAddress, iotbyz08 noise, int httpCode,
                                 int* loopchange) {
  *loopchange = *loopchange + 1;
  // Serial.println(*loopchange);
  if (*loopchange >= 10) *loopchange = 0;

  OLED1.clear();
  // OLED1.setTextAlignment(TEXT_ALIGN_RIGHT);
  OLED1.setTextAlignment(TEXT_ALIGN_LEFT);
  OLED1.setFont(ArialMT_Plain_10);
  OLED1.drawString(0, 0,
                   "Ip:" + ipAddress + " hc:" + String(httpCode) + " " +
                       String(*loopchange));
  OLED1.drawString(0, 15, "Env Noise = " + String(noise.env_noise) + " db");
  OLED1.display();
  delay(10);
}

/*oled dispaly Pms information */
void iotOledSH1106::DisplayVolt(String ipAddress, iotVoltSensor fabVoltSensor,
                                int httpCode, int* loopchange) {
  *loopchange = *loopchange + 1;
  // Serial.println(*loopchange);
  if (*loopchange >= 10) *loopchange = 0;

  OLED1.clear();
  // OLED1.setTextAlignment(TEXT_ALIGN_RIGHT);
  OLED1.setTextAlignment(TEXT_ALIGN_LEFT);
  OLED1.setFont(ArialMT_Plain_10);
  OLED1.drawString(0, 0,
                   "Ip:" + ipAddress + " hc:" + String(httpCode) + " " +
                       String(*loopchange));
  OLED1.drawString(0, 15, "Input Volt = " + String(fabVoltSensor.VIN) + " V");
  OLED1.display();
  delay(10);
}