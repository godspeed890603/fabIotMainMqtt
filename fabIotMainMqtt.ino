// #include "./wifi1/iotwifi1.h"
// #include <Arduino.h>
// #include "iotwifi.h"
// #include "oled.h"
// //#include "dht22.h"
// #include "dht21.h"
// #include "iotbyz08.h"
// #include "Timer.h"
// #include "iotPms7003.h"
// #include "iotWebAction.h"
// //#include "ReadSetting.h"

// //#include <ESP8266WiFi.h>
// //#include <ESP8266WiFiMulti.h>
// //#include <ESP8266HTTPClient.h>
// //#include <WiFiClient.h>
#include "fabIotMainMqtt.h"

int pms_httpCode = -1;
int noise_httpCode = -1;
int dht_httpCode = -1;
int volt_httpCode = -1;
int vht_httpCode = -1;
int shtxx_httpCode = -1;
int loopchange = 0;

int pmsLoopchange = 0;
int noiseLoopchange = 0;
int dhtLoopchange = 0;
int voltLoopchange = 0;
int vhtLoopchange = 0;
int shtxxLoopchange = 0;

// read initial
ReadSetting iotReadSetting;
// iot device Class
iotDHT fabIotDht;
iotWifi fabIotWifi;
// iotOled* fabIotOled;
iotOledSH1106 fabIotOledSH1106;
iotbyz08 fabBYZ08;
iotPms7003 fabPms7003;
iotVoltSensor fabVoltSensor;
iotVHT fabVHTSensor;
iotShtXX fabShtXXSensor;
//Mqtt 2024/10/14
MQTTClient* mqttClientHandler;
String service = "service_pms";

// iot Data Action
iotWebAction webAction;

Timer tDHT;
Timer tBYZ08;
Timer tPms;
Timer tVoltSensor;
Timer tVHT;
Timer tShtXX;

void setTimer() {
  // Serial.println("get tBYZ08TickEvent  --> tBYZ08TickEvent");
  // Serial.println(iotReadSetting.stu_sensor_NOISE.isEnable);
  if (iotReadSetting.stu_sensor_NOISE.isEnable == true) {
    int tBYZ08TickEvent =
        tBYZ08.every(iotReadSetting.stu_sensor_NOISE.actioInterval, doBYZ08);
    Serial.println("get tBYZ08TickEvent  --> tBYZ08TickEvent");
  }

  if (iotReadSetting.stu_sensor_DHT.isEnable == true) {
    int tDHTTickEvent =
        tDHT.every(iotReadSetting.stu_sensor_DHT.actioInterval, doDHT);
    Serial.println("get tDHTTickEvent  --> tDHTTickEvent");
  }

  if (iotReadSetting.stu_sensor_PMS.isEnable == true) {
    int tPmsTickEvent =
        tPms.every(iotReadSetting.stu_sensor_PMS.actioInterval, doPms);
    Serial.println("get tPmsTickEvent  --> tPmsTickEvent");
  }

  if (iotReadSetting.stu_sensor_VOLT.isEnable == true) {
    int tVoltSensorTickEvent = tVoltSensor.every(
        iotReadSetting.stu_sensor_VOLT.actioInterval, doVoltSensor);
    Serial.println("get tVoltSensorTickEvent  --> tVoltSensorTickEvent");
  }

  if (iotReadSetting.stu_sensor_VHT.isEnable == true) {
    int tVHTTickEvent =
        tVHT.every(iotReadSetting.stu_sensor_VHT.actioInterval, doVHT);
    Serial.println("get tVHTTickEvent  --> tVHTTickEvent");
  }

  if (iotReadSetting.stu_sensor_ShtXX.isEnable == true) {
    int tShtXXTickEvent =
        tShtXX.every(iotReadSetting.stu_sensor_ShtXX.actioInterval, doShtXX);
    Serial.println("get tShtXXTickEvent  --> tShtXXTickEvent");
  }
}

void WifiReConnect() {
  // fabIotOled->DisplayText("Wifi Reconnecting..");
  fabIotOledSH1106.DisplayText("Wifi Reconnecting..");
  fabIotWifi.WifiReset();
}
void checkHttpCodeAction(int reHttpcode) {
  if (reHttpcode != 200) {
    WifiReConnect();
    // like Reboot
    // All sensor loop restart
    //  pms_httpCode=-1;
    //  noise_httpCode=-1;
    //  dht_httpCode=-1;
    //  volt_httpCode=-1;
    //  vht_httpCode=-1;
    //  loopchange=0;

    // pmsLoopchange=0;
    // noiseLoopchange=0;
    // dhtLoopchange=0;
    // voltLoopchange=0;
    // vhtLoopchange=0;
  }
}
void doShtXX() {
  iotWebAction DataAction;
  int httpPostLoop = 0;

  Serial.println("------SHt Read start------ " + String(shtxxLoopchange) +
                 " -- " + String(iotReadSetting.stu_sensor_ShtXX.uploadLoop));

  // delay(5000);
  shtxxLoopchange++;
  if (fabShtXXSensor.readShtXX() != true) {
    Serial.println("------SHTXX Sensor Abnormal------ ");
    shtxx_httpCode = -999;
    // fabIotOledSH1106.DisplayDHT(fabIotWifi.ipAdress,
    // fabIotDht,dht_httpCode,&loopchange);
    ESP.restart();
  }

  fabIotOledSH1106.DisplayShtXX(fabIotWifi.ipAdress, fabShtXXSensor,
                                shtxx_httpCode, &loopchange);
  if (iotReadSetting.stu_sensor_WIFI.isEnable == true) {
    if (shtxxLoopchange > iotReadSetting.stu_sensor_ShtXX.uploadLoop) {
      // tmpType=iotReadSetting.stu_sensor_DHT.DataType;
      // uploadType=tmpType.toInt();

      DataAction = fabShtXXSensor.setUploadData(
          iotReadSetting.stu_sensor_ShtXX.DataType, iotReadSetting, fabIotWifi);
      shtxx_httpCode = fabShtXXSensor.uploadShtXX(DataAction);
      shtxxLoopchange = 0;
      // if httpcoe !=200 wifi reset;
      checkHttpCodeAction(shtxx_httpCode);
      // fabIotOledSH1106.DisplayPms(fabIotWifi.ipAdress,fabPms7003,pms_httpCode,&loopchange);
      fabIotOledSH1106.DisplayShtXX(fabIotWifi.ipAdress, fabShtXXSensor,
                                    shtxx_httpCode, &loopchange);
    }
  }
  Serial.println("------Shtxx Read End------ ");
  Serial.println("\n\n\n");
  // delay(5000);
}

void doVHT() {
  iotWebAction DataAction;
  int httpPostLoop = 0;

  Serial.println("------VHT Read start------ " + String(vhtLoopchange) +
                 " -- " + String(iotReadSetting.stu_sensor_VHT.uploadLoop));

  // fabVoltSensor.getBaterryVoltage();
  vhtLoopchange++;
  // fabIotOledSH1106.DisplayVolt(fabIotWifi.ipAdress,fabVoltSensor,dht_httpCode,&loopchange);
  if (iotReadSetting.stu_sensor_WIFI.isEnable == true) {
    if (vhtLoopchange > iotReadSetting.stu_sensor_VHT.uploadLoop) {
      // V1.11
      //  DataAction =
      //  fabVHTSensor.setUploadData(iotReadSetting.stu_sensor_VHT.DataType,iotReadSetting,fabIotWifi
      //  \
 ,fabVoltSensor,fabIotDht );
      DataAction = fabVHTSensor.setUploadData(
          iotReadSetting.stu_sensor_VHT.DataType, iotReadSetting, fabIotWifi,
          fabVoltSensor, fabShtXXSensor);
      vht_httpCode = fabVHTSensor.uploadVHT(DataAction);
      vhtLoopchange = 0;
      // if httpcoe !=200 wifi reset;
      checkHttpCodeAction(vht_httpCode);
      // fabIotOledSH1106.DisplayVolt(fabIotWifi.ipAdress,
      // fabVoltSensor,vht_httpCode,&loopchange);
    }
    Serial.println("------VHT Read End------ ");
    Serial.println("\n\n\n");
  }
}

void doVoltSensor() {
  iotWebAction DataAction;
  int httpPostLoop = 0;

  Serial.println("------Volt Read start------ " + String(voltLoopchange) +
                 " -- " + String(iotReadSetting.stu_sensor_VOLT.uploadLoop));
  voltLoopchange++;

  fabVoltSensor.getBaterryVoltage();

  fabIotOledSH1106.DisplayVolt(fabIotWifi.ipAdress, fabVoltSensor, dht_httpCode,
                               &loopchange);
  if (iotReadSetting.stu_sensor_WIFI.isEnable == true) {
    if (voltLoopchange > iotReadSetting.stu_sensor_VOLT.uploadLoop) {
      DataAction = fabVoltSensor.setUploadData(
          iotReadSetting.stu_sensor_VOLT.DataType, iotReadSetting, fabIotWifi);
      volt_httpCode = fabVoltSensor.uploadVolt(DataAction);
      voltLoopchange = 0;
      // if httpcoe !=200 wifi reset;
      checkHttpCodeAction(volt_httpCode);
      fabIotOledSH1106.DisplayVolt(fabIotWifi.ipAdress, fabVoltSensor,
                                   volt_httpCode, &loopchange);
    }

    Serial.println("------Volt Read End------ ");
    Serial.println("\n\n\n");
  }
}

void doDHT() {
  iotWebAction DataAction;
  int httpPostLoop = 0;

  Serial.println("------DHT Read start------ " + String(dhtLoopchange) +
                 " -- " + String(iotReadSetting.stu_sensor_DHT.uploadLoop));

  // delay(5000);
  dhtLoopchange++;
  if (fabIotDht.readDHT() != true) {
    Serial.println("------DHT Sensor Abnormal------ ");
    dht_httpCode = -999;
    // fabIotOledSH1106.DisplayDHT(fabIotWifi.ipAdress,
    // fabIotDht,dht_httpCode,&loopchange);
    ESP.restart();
  }

  fabIotOledSH1106.DisplayDHT(fabIotWifi.ipAdress, fabIotDht, dht_httpCode,
                              &loopchange);
  if (iotReadSetting.stu_sensor_WIFI.isEnable == true) {
    if (dhtLoopchange > iotReadSetting.stu_sensor_DHT.uploadLoop) {
      DataAction = fabIotDht.setUploadData(
          iotReadSetting.stu_sensor_DHT.DataType, iotReadSetting, fabIotWifi);
      dht_httpCode = fabIotDht.uploadDht(DataAction);
      dhtLoopchange = 0;
      // if httpcoe !=200 wifi reset;
      checkHttpCodeAction(dht_httpCode);
      // fabIotOledSH1106.DisplayPms(fabIotWifi.ipAdress,fabPms7003,pms_httpCode,&loopchange);
      fabIotOledSH1106.DisplayDHT(fabIotWifi.ipAdress, fabIotDht, dht_httpCode,
                                  &loopchange);
    }
  }

  Serial.println("------DHT Read End------ ");
  Serial.println("\n\n\n");
}

void doBYZ08() {
  iotWebAction DataAction;
  int httpCode;
  int httpPostLoop = 0;

  Serial.println("------Noise Read start------ " + String(noiseLoopchange) +
                 " -- " + String(iotReadSetting.stu_sensor_NOISE.uploadLoop));
  noiseLoopchange++;
  fabBYZ08.getDB();
  fabIotOledSH1106.DisplayNoise(fabIotWifi.ipAdress, fabBYZ08, noise_httpCode,
                                &loopchange);
  if (iotReadSetting.stu_sensor_WIFI.isEnable == true) {
    if (noiseLoopchange > iotReadSetting.stu_sensor_NOISE.uploadLoop) {
      DataAction = fabBYZ08.setUploadData(
          iotReadSetting.stu_sensor_NOISE.DataType, iotReadSetting, fabIotWifi);
      noise_httpCode = fabBYZ08.uploadNoise(DataAction);
      noiseLoopchange = 0;
      // if httpcoe !=200 wifi reset;
      checkHttpCodeAction(noise_httpCode);
      fabIotOledSH1106.DisplayNoise(fabIotWifi.ipAdress, fabBYZ08,
                                    noise_httpCode, &loopchange);
    }
  }

  Serial.println("------Noise Read End------ ");
  Serial.println("\n\n\n");
}

void doPms() {
  iotWebAction DataAction;
  int httpPostLoop = 0;

  Serial.println("------Pms Read start------ " + String(pmsLoopchange) +
                 " -- " + String(iotReadSetting.stu_sensor_PMS.uploadLoop));
  pmsLoopchange++;
  fabPms7003.pms_read();
  fabIotOledSH1106.DisplayPms(fabIotWifi.ipAdress, fabPms7003, pms_httpCode,
                              &loopchange);
  if (iotReadSetting.stu_sensor_WIFI.isEnable == true) {
    if (pmsLoopchange > iotReadSetting.stu_sensor_PMS.uploadLoop) {
      DataAction = fabPms7003.setUploadData(
          iotReadSetting.stu_sensor_PMS.DataType, iotReadSetting, fabIotWifi);
      
      pms_httpCode = fabPms7003.uploadPms(DataAction);

      Serial.println("------uploadMqttPms Read start------ " );
      bool uploadRtn = fabPms7003.uploadMqttPms(DataAction,mqttClientHandler);//2024/10/14 Add Mqtt
      Serial.println("------uploadMqttPms Read end------ " );
      
      // mqttClientHandler
      fabPms7003.clearMaxRange();  // v1.10
      pmsLoopchange = 0;
      // if httpcoe !=200 wifi reset;
      checkHttpCodeAction(pms_httpCode);
      fabIotOledSH1106.DisplayPms(fabIotWifi.ipAdress, fabPms7003, pms_httpCode,
                                  &loopchange);
    }
  }

  //~~~~
  if (iotReadSetting.stu_sensor_WIFI.isEnable != true) {
    if (pmsLoopchange > iotReadSetting.stu_sensor_PMS.uploadLoop) {
      fabPms7003.clearMaxRange();  // v1.10
      pmsLoopchange = 0;
      //  *loopchange = *loopchange + 1;
      // Serial.println(*loopchange);
      // if (loopchange > ) loopchange = 0;
      // if httpcoe !=200 wifi reset;
       fabIotOledSH1106.DisplayPms(fabIotWifi.ipAdress, fabPms7003, pms_httpCode,
                                  &loopchange);
    }
  }

  //~~~~
  Serial.println("------Pms Read End------ ");
  Serial.println("\n\n\n");
}

void setup() {
  // put your setup code here, to run once:
  int yPos = 0;
  Serial.begin(9600);
  SPIFFS.begin();
  // read Setting from SPIFFS
  iotReadSetting.readSetting();
  // //DisplaySensorPowerOn();
  //  //Wifi setting & start
  // if (iotReadSetting.stu_sensor_WIFI.isEnable == true){
  //   //fabIotOledSH1106.DisplaySystemStartText(0,yPos,"Wifi Start..");
  //   yPos=yPos+10;
  //   fabIotWifi.initialSetting(iotReadSetting);
  //   fabIotWifi.WifiReset();
  // }else{
  //   //fabIotOledSH1106.DisplaySystemStartText(0,yPos,"No Wifi..");
  //   yPos=yPos+10;
  // }

  // OLED display
  fabIotOledSH1106.initialOLEDSH1106();
  fabIotOledSH1106.DisplaySystemStartText(
      0, yPos,
      "Ver:" + iotReadSetting.version + " MID:" + iotReadSetting.machine_ID);
  yPos = yPos + 10;

  fabIotOledSH1106.DisplaySystemStartText(0, yPos, "System Start..");
  yPos = yPos + 10;

  // Noise Sensor
  if (iotReadSetting.stu_sensor_NOISE.isEnable == true) {
    fabBYZ08.begin();
    fabIotOledSH1106.DisplaySystemStartText(0, yPos, "Support Noise..");
    yPos = yPos + 10;
  }

  // PMS sensor
  if (iotReadSetting.stu_sensor_PMS.isEnable == true) {
    fabPms7003.initialPms();
    fabIotOledSH1106.DisplaySystemStartText(0, yPos, "Support Pms..");
    yPos = yPos + 10;
  }

  // temp & humi sensor
  if (iotReadSetting.stu_sensor_DHT.isEnable == true) {
    fabIotDht.initialDht();
    // Serial.print("iotReadSetting.stu_sensor_DHT.dht_offset_t: ");
    // Serial.print(iotReadSetting.stu_sensor_DHT.dht_offset_t);
    //   Serial.print("iotReadSetting.stu_sensor_DHT.dht_offset_h: ");
    // Serial.print(iotReadSetting.stu_sensor_DHT.dht_offset_h);
    // Serial.println(" xx ");
    fabIotDht.offset_t = iotReadSetting.stu_sensor_DHT.dht_offset_t;
    fabIotDht.offset_h = iotReadSetting.stu_sensor_DHT.dht_offset_h;
    fabIotOledSH1106.DisplaySystemStartText(0, yPos, "Support DHT..");
    yPos = yPos + 10;
  }

  // fabVoltSensor sensor
  if (iotReadSetting.stu_sensor_VOLT.isEnable == true) {
    fabVoltSensor.begin();
    fabVoltSensor.m = iotReadSetting.stu_sensor_VOLT.m;
    fabVoltSensor.c = iotReadSetting.stu_sensor_VOLT.c;

    fabVoltSensor.initialVoltageDetect();
    fabIotOledSH1106.DisplaySystemStartText(0, yPos, "Support Volt..");
    yPos = yPos + 10;
  }

  // fabVHTSensor sensor
  if (iotReadSetting.stu_sensor_VHT.isEnable == true) {
    fabIotOledSH1106.DisplaySystemStartText(0, yPos, "Support VHT..");
    yPos = yPos + 10;
  }

  // fabShtSensor sensor
  if (iotReadSetting.stu_sensor_ShtXX.isEnable == true) {
    fabShtXXSensor.initialShtXX();
    fabShtXXSensor.offset_t =
        iotReadSetting.stu_sensor_ShtXX.offset_t;  // v1.13
    fabShtXXSensor.offset_h =
        iotReadSetting.stu_sensor_ShtXX.offset_h;  // V1.13
    fabIotOledSH1106.DisplaySystemStartText(0, yPos, "Support Shtxx..");
    yPos = yPos + 10;
  }
  // //DisplaySensorPowerOn();
  // Wifi setting & start
  if (iotReadSetting.stu_sensor_WIFI.isEnable == true) {
    fabIotOledSH1106.DisplaySystemStartText(0, yPos, "Wifi Start..");
    yPos = yPos + 10;
    fabIotWifi.initialSetting(iotReadSetting);
    fabIotWifi.WifiReset();
  } else {
    fabIotOledSH1106.DisplaySystemStartText(0, yPos, "No Wifi..");
    yPos = yPos + 10;
  }

 // Wifi setting & start 2024/10/14
  mqttClientHandler= new MQTTClient(); 
  delay(100);
  mqttClientHandler->setServiceName(service);
  mqttClientHandler->CreatePubSubTopic();
  mqttClientHandler->connect();  // 連接到 MQTT broker
  mqttClientHandler->loop();
  delay(100);

  // Set trigger Timer
  setTimer();
}

void loop() {
  // Mcu Start
  if (iotReadSetting.stu_sensor_WIFI.isEnable == true) {
    if (fabIotWifi.getWifiStatus() != WL_CONNECTED) {
      //  // fabIotOled->DisplayText("Wifi Reconnecting..");
      // fabIotOledSH1106.DisplayText("Wifi Reconnecting..");
      // fabIotWifi.WifiReset();
      WifiReConnect();
    } else {
      // Serial.println("  ArduinoOTA.handle() Start ");
      ArduinoOTA.handle();  // V1.11
      // Serial.println("  ArduinoOTA.handle() End ");
    }
  } else {
    fabIotWifi.ipAdress = "Offline ";
  }

  // Serial.println("------Wifi Rssi------ " +
  // String(fabIotWifi.getWifiRssi()));
  if (iotReadSetting.stu_sensor_NOISE.isEnable == true) {
    tBYZ08.update();
  }

  if (iotReadSetting.stu_sensor_PMS.isEnable == true) {
    tPms.update();
  }

  if (iotReadSetting.stu_sensor_VHT.isEnable == true) {
    tVHT.update();
  }
  if (iotReadSetting.stu_sensor_DHT.isEnable == true) {
    tDHT.update();
  }

  if (iotReadSetting.stu_sensor_VOLT.isEnable == true) {
    tVoltSensor.update();
  }

  if (iotReadSetting.stu_sensor_ShtXX.isEnable == true) {
    tShtXX.update();
  }
  // delay(50);
}
