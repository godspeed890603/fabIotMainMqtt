#include "iotWebAction.h"

#include "const.h"

iotWebAction::iotWebAction(){
  //BYZ08Data= new iotDataByz08();
}

iotWebAction::iotWebAction(ReadSetting tmpSetting){
  //BYZ08Data= new iotDataByz08();
}

iotWebAction::~iotWebAction(){
  //delete BYZ08Data;
}

String iotWebAction::getUploadWebHtml(int uploadType){
  String webHtml;

  switch (uploadType) { 
    case 5: 
      //webHtml="http://172.27.10.92/IOT_MON/IOT_SAVE.PHP?SENSOR_ID=" + String(SENSOR_ID) 
      //"ip+typeid","macid","ip","rssi","max_range_0_3um","max_range_0_5um","max_range_1_0um"
      //,"max_range_2_5um","max_range_5_um","max_range_10_0um"
      webHtml= webserverHtml_Header \
      + "SENSOR_ID=" + SENSOR_ID \
      + "&TYPE=" + String(uploadType) \
      + "&DATA_CNT=10" \
      +"&DATA_001=" + machine_ID \
      +"&DATA_002=" + WifiData.ipAdress \
      +"&DATA_003=" + WifiData.wifiRssi \
      +"&DATA_004=" + PmsData.max_range_0_3um \
      +"&DATA_005=" + PmsData.max_range_0_5um \
      +"&DATA_006=" + PmsData.max_range_1_0um \
      +"&DATA_007=" + PmsData.max_range_2_5um \
      +"&DATA_008=" + PmsData.max_range_5_0um\
      +"&DATA_009=" + PmsData.max_range_10_0um \
      +"&DATA_010=" + PmsData.um_total ;//V1.10

      Serial.println("------Pms Read start------ "  + PmsData.max_range_10_0um);
      //return "http://172.27.10.92/IOT_MON/IOT_SAVE.PHP?SENSOR_ID=CIMPARTICLE&DATA_CNT=6&DATA_001=163&DATA_002=52&DATA_003=1&DATA_004=0&DATA_005=0&DATA_006=0";


      return webHtml;
      break; 
    case 2: 
      //webHtml="http://172.27.10.92/IOT_MON/IOT_SAVE.PHP?SENSOR_ID=" + String(SENSOR_ID) 
        //"ip+typeid","macid","ip","rssi","max_range_0_3um","max_range_0_5um","max_range_1_0um"
        //,"max_range_2_5um","max_range_5_um","max_range_10_0um"
        webHtml= webserverHtml_Header \
        + "SENSOR_ID=" + WifiData.ipAdress +SENSOR_ID \
        + "&TYPE=" + String(uploadType) \
        + "&DATA_CNT=4" \
        +"&DATA_001=" + machine_ID \
        +"&DATA_002=" + WifiData.ipAdress \
        +"&DATA_003=" + WifiData.wifiRssi \
        +"&DATA_004=" + BYZ08Data.env_noise_db;
        return webHtml;
        break; 
     case 1: 
      //webHtml="http://172.27.10.92/IOT_MON/IOT_SAVE.PHP?SENSOR_ID=" + String(SENSOR_ID) 
        //"ip+typeid","macid","ip","rssi","max_range_0_3um","max_range_0_5um","max_range_1_0um"
        //,"max_range_2_5um","max_range_5_um","max_range_10_0um"
        webHtml= webserverHtml_Header \
        + "SENSOR_ID=" + WifiData.ipAdress +SENSOR_ID \
        + "&TYPE=" + String(uploadType) \
        + "&DATA_CNT=5" \
        +"&DATA_001=" + machine_ID \
        +"&DATA_002=" + WifiData.ipAdress \
        +"&DATA_003=" + WifiData.wifiRssi \
        +"&DATA_004=" + DhtData.DH \
        +"&DATA_005=" + DhtData.DT;
        return webHtml;
        break;   

      case 4: 
   //webHtml="http://172.27.10.92/IOT_MON/IOT_SAVE.PHP?SENSOR_ID=" + String(SENSOR_ID) 
        //"ip+typeid","macid","ip","rssi","max_range_0_3um","max_range_0_5um","max_range_1_0um"
        //,"max_range_2_5um","max_range_5_um","max_range_10_0um"
        webHtml= webserverHtml_Header \
        + "SENSOR_ID=" + WifiData.ipAdress +SENSOR_ID \
        + "&TYPE=" + String(uploadType) \
        + "&DATA_CNT=4" \
        +"&DATA_001=" + machine_ID \
        +"&DATA_002=" + WifiData.ipAdress \
        +"&DATA_003=" + WifiData.wifiRssi \
        +"&DATA_004=" + VoltData.Vin;
        return webHtml;
        break; 

      case 6: 
      //webHtml="http://172.27.10.92/IOT_MON/IOT_SAVE.PHP?SENSOR_ID=" + String(SENSOR_ID) 
        //"ip+typeid","macid","ip","rssi","max_range_0_3um","max_range_0_5um","max_range_1_0um"
        //,"max_range_2_5um","max_range_5_um","max_range_10_0um"
       // webHtml = "http://172.27.10.92/TH_MON/AMHS_ENV_SAVE.PHP?ROOM_NO=FF0561&MAC_ID=" + machine_ID +"&TEMP1=" + DhtData.DT +"&TEMP2=" + DhtData.DT +"&HDY1=" + DhtData.DH  +"&HDY2="+ DhtData.DH  + "&WIFISTH=" + WifiData.wifiRssi  +"&VOLTAGE="+ VoltData.Vin + "&IPADD=" + WifiData.ipAdress;

        webHtml= webserverHtml_Header \
        + "ROOM_NO=" + mount_Device \
        + "&MAC_ID=" + machine_ID \
        + "&TEMP1=" + DhtData.DT \
        + "&TEMP2=" + DhtData.DT \
        + "&HDY1=" + DhtData.DH  \
        + "&HDY2="+ DhtData.DH \
        + "&WIFISTH=" + WifiData.wifiRssi \
        +"&VOLTAGE="+ VoltData.Vin \
        + "&IPADD=" + WifiData.ipAdress;

        return webHtml;
        break;  


        case 7: 
      //webHtml="http://172.27.10.92/IOT_MON/IOT_SAVE.PHP?SENSOR_ID=" + String(SENSOR_ID) 
        //"ip+typeid","macid","ip","rssi","max_range_0_3um","max_range_0_5um","max_range_1_0um"
        //,"max_range_2_5um","max_range_5_um","max_range_10_0um"
        webHtml= webserverHtml_Header \
        + "SENSOR_ID=" + WifiData.ipAdress +SENSOR_ID \
        + "&TYPE=" + String(uploadType) \
        + "&DATA_CNT=5" \
        +"&DATA_001=" + machine_ID \
        +"&DATA_002=" + WifiData.ipAdress \
        +"&DATA_003=" + WifiData.wifiRssi \
        +"&DATA_004=" + ShtXXData.DH \
        +"&DATA_005=" + ShtXXData.DT;
        return webHtml;
        break;    

  }
}

int iotWebAction::uploadData(String webHtml){
  //String webHtml="";
  float VIN=0.0;
  int httpCode;
 
  WiFiClient client;
  HTTPClient http;

  Serial.print("[HTTP] begin...\n"); 

  //webHtml = "http://172.27.10.921/TH_MON/AMHS_ENV_SAVE.PHP?ROOM_NO=" + ROOM_NO +"&MAC_ID=" + machineID +"&TEMP1=" + DhtData.DT +"&TEMP2=" + DhtData.DT +"&HDY1=" + DhtData.DH +"&HDY2="+ DhtData.DH + "&WIFISTH=" + WifiData.wifiRssi +"&VOLTAGE="+ String(VIN,2) + "&IPADD=" + WifiData.ipAdress + "&NOISE=" + BYZ08Data.env_noise_db;
  Serial.println( webHtml); 

  http.setTimeout(httpTimeout);
  if (http.begin(client, webHtml)) {  // HTTP
    Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
    httpCode = http.GET();
      // httpCode will be negative on error
    if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
      http.end();
  } else {
    Serial.printf("[HTTP} Unable to connect\n");
  }
  return httpCode;
}