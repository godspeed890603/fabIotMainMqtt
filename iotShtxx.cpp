#include "iotShtxx.h"


//DFRobot_SHT20    sht20;
Adafruit_SHT31 sht31 = Adafruit_SHT31();
/*DHT Initial */
void iotShtXX::initialShtXX(){
    Serial.println("initial Shtxx!");
    //sht20.initSHT20();                                  // Init SHT20 Sensor
    delay(100);
    //sht20.checkSHT20();                                 // Check SHT20 Sensor
    
    Serial.println("SHT31 test");
    if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
        Serial.println("Couldn't find SHT31");
        //while (1) delay(1);
    }
}

/* read  Humidity & Temperature*/
bool iotShtXX::readShtXX(){
    int readDHTLoop = 0;
    int maxReadDhtLoop = 30;
    int retDhtResult = 0;
    while(1){
        float h =  sht31.readHumidity();;
        // Read temperature as Celsius (the default)
        float t = sht31.readTemperature(); 
        //Serial.print("readDHTLoop: ");
        //Serial.println(readDHTLoop);
        // Check if any reads failed and exit early (to try again).
        if (isnan(h) || isnan(t)) {
            Serial.println("Shtxx Read error!");
            if (readDHTLoop > maxReadDhtLoop){
                this->DH1 = "NG";
                this->DT1 = "NG";
                retDhtResult = false;
                break;
            }
            readDHTLoop++;
            delay(2000);
        }else{
            Serial.println("orignal Humidity: " + String(h));
            this->DH1=getHCalibration(h);
            Serial.println("calibration  Humidity: " + this->DH1 + "%");


            Serial.println("orignal Temperature: " + String(t));
            t = t ;
            // this->DT1=String(t, 1);
            this->DT1=getTCalibration(t);
            Serial.println("calibration  Temperature: " + this->DT1 + "*C");
            retDhtResult=true;
            break;
        }
    }
    return retDhtResult;    
}


String iotShtXX::getHCalibration(float h){
    //h = h*1.5652-41.217;
    //h = h*1.04135-8.6;//kermit
    //h = h*1.00;
    return String(h-5.8,1);
}

String iotShtXX::getTCalibration(float t){
    //t=1.0317*t-0.5252;
    t = t*1.00;//+0.9;
    //t = t*1.00;
    return String(t,1);
}




iotWebAction iotShtXX::setUploadData(int uploadType,ReadSetting iotReadSetting, iotWifi fabIotWifi){ 
    String sensor;
    iotWebAction DataAction;

    DataAction.ShtXXData.DH = String(DH1); 
    DataAction.ShtXXData.DT = String(DT1); 

    //Wifi
    DataAction.WifiData.wifiRssi =  String(fabIotWifi.getWifiRssi());
    DataAction.WifiData.ipAdress = fabIotWifi.ipAdress;
    //SENSOR ID 
    DataAction.SENSOR_ID =String(iotReadSetting.stu_sensor_ShtXX.id);
    DataAction.webserverHtml_Header=iotReadSetting.stu_sensor_ShtXX.webserverHtml_Header;
    DataAction.uploadType=uploadType;
    DataAction.machine_ID=iotReadSetting.machine_ID;
    return DataAction;
}

int iotShtXX::uploadShtXX(iotWebAction DataAction){
    int httpCode=-1;
    int httpPostLoop=0;
    String webHtml;

    webHtml=DataAction.getUploadWebHtml(DataAction.uploadType);

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
    
    return httpCode;

}
