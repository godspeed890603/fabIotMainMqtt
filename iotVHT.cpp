#include "iotVHT.h"


// void iotVHT::begin(){
//   pinMode(RelyControlPin, OUTPUT); 
//   digitalWrite(RelyControlPin, LOW); // turn the LED on (HIGH is the voltage level) 
//   delay(5500); 
// }


// void iotVHT::initialVoltageDetect(){
//     pinMode(RelyControlPin, OUTPUT); 
//     Serial.println("HIGH"); 
//     digitalWrite(RelyControlPin, HIGH); // turn the LED on (HIGH is the voltage level) 
//     delay(500); 
//     //AO in register
//     Rp=R75K *(R100K+R220K)/(R75K+R100K+R220K);
// }

// void iotVHT::getBaterryVoltage(){

//     float  VAO= 0.0; 
//     float VRt = 0.0;
//     int i=0; 
//     float vinTotal=0.0; 
//     int value = 0; 
    
//     for (i=0;i<sampleCount;i++){ 
//         value = analogRead(voltageSensor); 
//         VAO = ((value * Vw) / 1023.0) ; 
//         //Serial.print("VAO = "); 
//         //Serial.println(VAO); 
        
//         //A0端並聯電阻
//         //Rp=R75K *(R100K + R220K)/(R75K + R100K + R220K);
//         VRt=(VAO *( Rp + R300K ) / Rp) * m + c;
//         //Serial.print("VRt = "); 
//         //Serial.println(VRt); 
//         vinTotal = vinTotal + VRt + Vd; 
//         delay(50);
//     } 
//     Serial.print("Input = "); 
//     //Serial.println(vinTotal/sampleCount);
//     VIN=vinTotal/sampleCount;
//     if (VIN <=0 ){
//          VIN=0;
//     }
        
//     Serial.println(VIN);
// }


iotWebAction iotVHT::setUploadData(int uploadType,ReadSetting iotReadSetting, iotWifi fabIotWifi \
      ,iotVoltSensor fabVoltSensor,iotShtXX fabShtXXSensor){ 

    String sensor;
    iotWebAction DataAction;

    //Volt Data
    DataAction.VoltData.Vin = String(fabVoltSensor.VIN);
    
    //Temp & Humi
    //V1.11
    // DataAction.DhtData.DH = String(fabIotDht.DH1);
    // DataAction.DhtData.DT = String(fabIotDht.DT1);
    DataAction.DhtData.DH = String(fabShtXXSensor.DH1);
    DataAction.DhtData.DT = String(fabShtXXSensor.DT1);

    //Wifi
    DataAction.WifiData.wifiRssi =  String(fabIotWifi.getWifiRssi());
    DataAction.WifiData.ipAdress = fabIotWifi.ipAdress;

    //SENSOR ID 
    DataAction.SENSOR_ID =String(iotReadSetting.stu_sensor_VHT.id);
    DataAction.webserverHtml_Header=iotReadSetting.stu_sensor_VHT.webserverHtml_Header;
    DataAction.uploadType=uploadType;
    DataAction.machine_ID=iotReadSetting.machine_ID;
    DataAction.mount_Device=iotReadSetting.mount_Device;
    return DataAction;
}

int iotVHT::uploadVHT(iotWebAction DataAction){
    int httpCode=-1;
    int httpPostLoop=0;
    String webHtml;

    webHtml=DataAction.getUploadWebHtml(DataAction.uploadType);
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
   // Serial.println("ESP.deepSleep(20e6); ");
   
    return httpCode;

}

