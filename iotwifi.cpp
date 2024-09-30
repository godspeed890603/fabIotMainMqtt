#include "iotwifi.h"


iotWifi::iotWifi(){
}

void iotWifi::initialSetting(ReadSetting tmpSetting){

  ip_array[0]=tmpSetting.ip[0];
  ip_array[1]=tmpSetting.ip[1];
  ip_array[2]=tmpSetting.ip[2];
  ip_array[3]=tmpSetting.ip[3];
  ip=IPAddress(ip_array);

  
  gateway_array[0]=tmpSetting.gateway[0];
  gateway_array[1]=tmpSetting.gateway[1];
  gateway_array[2]=tmpSetting.gateway[2];
  gateway_array[3]=tmpSetting.gateway[3];
  gateway=IPAddress(gateway_array);

 
  subnet_array[0]=tmpSetting.subnet[0];
  subnet_array[1]=tmpSetting.subnet[1];
  subnet_array[2]=tmpSetting.subnet[2];
  subnet_array[3]=tmpSetting.subnet[3];
  subnet=IPAddress(subnet_array);
  
  dns_array[0]=tmpSetting.dns[0];
  dns_array[1]=tmpSetting.dns[1];
  dns_array[2]=tmpSetting.dns[2];
  dns_array[3]=tmpSetting.dns[3];
  dns=IPAddress(dns_array);


  ssid=tmpSetting.stu_sensor_WIFI.ssid;
  pwd=tmpSetting.stu_sensor_WIFI.pwd;
  reconnectInterval=tmpSetting.stu_sensor_WIFI.ReconnectInterval;
  isDhcp=tmpSetting.stu_sensor_WIFI.isDHCP;
  Serial.println("[ip.ssid] begin..." + ssid);
  Serial.println("[ip.pwd] begin..." + pwd);


}

/*wifi disconnect & reconnect */
void iotWifi::WifiReset(){
  
  Serial.printf("[Disconnct Wifi...]\n");
  WiFi.disconnect();
  delay(reconnectInterval);
  initialWifi();
}

/*wifi reconnect */
void iotWifi::initialWifi(){

  
  WiFi.mode(WIFI_STA);
  // Static IP Setup Info Here...
  
  if (isDhcp != true){
    Serial.println("[ip.getway] begin..." + ip.toString());
    WiFi.config(ip, gateway, subnet); //If you need Internet Access You should Add DNS also...
  }
    
  Serial.printf("set pwd.....");
  WiFi.begin(ssid, pwd);
 // WiFiMulti.addAP(ssid, pwd);
  //ipDisplay();
  //if ((WiFiMulti.run() == WL_CONNECTED)) {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf("connecting....");
     //ipDisplay();
     //delay(1*Sec1);
     delay(reconnectInterval);
  }

  //Start OTA
  WifiOTA();
 // wifiLose =false;
  Serial.println("[WiFi.getway] begin..." + WiFi.localIP().toString());
  Serial.println("[WiFi.getway] begin..." + WiFi.gatewayIP().toString());
  Serial.println("[WiFi.subnet] begin..." + WiFi.subnetMask().toString());
  wifiRssi=WiFi.RSSI();
  ipAdress=getIpAddress();
  macAddress = getmacAddress();
  Serial.println("[WiFi.macAddress] begin..." +macAddress);
}


String iotWifi::getmacAddress() {
  // char ipAddress1[16];

  // sprintf(ipAddress1, "%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1],
  //         WiFi.localIP()[2], WiFi.localIP()[3]);
  return String(WiFi.macAddress().c_str());
}

String iotWifi::getIpAddress(){
  char ipAddress1[16];

  sprintf(ipAddress1, "%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3] );
  return String(ipAddress1); 

}


// /*get wifi Status */
// bool iotWifi::getWifiStatus(){
 
//   if (WiFi.status() != WL_CONNECTED){
//     Serial.println("[WiFi.status()] begin...WiFi.status() != WL_CONNECTED" + String(WiFi.status()));
//     return false;
//   }

//   if (WiFi.status() == WL_CONNECTED){
//     Serial.println("[WiFi.status()] begin...WiFi.status() == WL_CONNECTED" + String(WiFi.status()));
//     return true;
//   }
// }


/*get wifi Status */
wl_status_t iotWifi::getWifiStatus(){
  return WiFi.status();
 
  // if (WiFi.status() != WL_CONNECTED){
  //   Serial.println("[WiFi.status()] begin...WiFi.status() != WL_CONNECTED" + String(WiFi.status()));
  //   return false;
  // }

  // if (WiFi.status() == WL_CONNECTED){
  //   Serial.println("[WiFi.status()] begin...WiFi.status() == WL_CONNECTED" + String(WiFi.status()));
  //   return true;
  // }
}

/*get wifi Rssi */
float iotWifi::getWifiRssi(){
  return WiFi.RSSI();
}



//V1.11
void iotWifi::WifiOTA(){
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  //ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
}