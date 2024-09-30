#include "iotbyz08.h"

void iotbyz08::begin(){ 
    Serial.println("-- iotbyz08::begin: ");
    SerialBYZ08 = new SoftwareSerial(D7,D8);//SoftwareSerial(rxPin, txPin, inverse_logic)
    SerialBYZ08->begin(9600);
}

float iotbyz08::getDB(){
    // Serial.println("iotbyz08::getDB ");
    float tmpNoiseDb=0.0;
    getData();
    tmpNoiseDb=(incomingDataByte[3]*256 + incomingDataByte[4])/10;
    if (tmpNoiseDb>max_env_noise)
      max_env_noise=tmpNoiseDb;

    env_noise=tmpNoiseDb;
    return env_noise;
}

void iotbyz08::getData(){
    
    SerialBYZ08->write(byz08ReadCmd,8);
    delay(300);

    int i=0;
    while(SerialBYZ08->available()>0){
      incomingDataByte[i]=SerialBYZ08->read();
      //Serial.println("-- READ: ");
      //Serial.println(incomingDataByte[i], HEX);
      //Serial.println(incomingDataByte[i],DEC);
      i=i+1; 
      if (i>=8)
        break;
    }
  //delay(5000);
}

iotWebAction iotbyz08::setUploadData(int uploadType,ReadSetting iotReadSetting, iotWifi fabIotWifi){ 
    String sensor;
    iotWebAction DataAction;
    // //Noise
    // DataAction.BYZ08Data.env_noise_db=String(fabBYZ08.env_noise,1);
    // //Temp & Humi
    // DataAction.DhtData.DH=fabIotDht.DH1;
    // DataAction.DhtData.DT=fabIotDht.DT1;
    //Particle
    DataAction.BYZ08Data.env_noise_db = String(max_env_noise,1); 

    //Wifi
    DataAction.WifiData.wifiRssi =  String(fabIotWifi.getWifiRssi());
    DataAction.WifiData.ipAdress = fabIotWifi.ipAdress;
    //SENSOR ID 
    DataAction.SENSOR_ID =String(iotReadSetting.stu_sensor_NOISE.id);
    DataAction.webserverHtml_Header=iotReadSetting.stu_sensor_NOISE.webserverHtml_Header;
    DataAction.uploadType=uploadType;
    DataAction.machine_ID=iotReadSetting.machine_ID;
    return DataAction;
}

int iotbyz08::uploadNoise(iotWebAction DataAction){
    int httpCode=-1;
    int httpPostLoop=0;
    String webHtml;

    webHtml=DataAction.getUploadWebHtml(2);
    //if (pmsLoopchange>10) {
        //pmsLoopchange=0;

        //如果wifi有啟動,開始上傳資料
            httpCode=DataAction.uploadData(webHtml);
        //如果wifi有啟動,開始上傳資料
        while(httpCode!=200){
            httpPostLoop++;
            //如果重新送httpRetry次失敗....主機重新開機
            if (httpPostLoop>httpRetry){
                //ESP.restart();
                break;
            }
            delay(1000);
            //重新送資料
            httpCode=DataAction.uploadData(webHtml);
        //if (httpCode!= 200){       
        //  fabIotOledSH1106.DisplayText("Wifi Reconnecting..");
        //  fabIotWifi.WifiReset();
        }
    //}  
    
    
    max_env_noise=0.0;
    return httpCode;

}