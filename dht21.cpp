#include "dht21.h"
#define DHTTYPE1 DHT22   // DHT 22  (AM2302)
#define D3 0    // what pin we're connected to
#define DHTPIN1 D3    // what pin we're connected to
DHT dht(DHTPIN1, DHTTYPE1);

/*DHT Initial */
void iotDHT::initialDht(){
   Serial.println("initial DHT!");
   dht.begin();
}

/* read  Humidity & Temperature*/
bool iotDHT::readDHT(){
    int readDHTLoop = 0;
    int maxReadDhtLoop = 30;
    int retDhtResult = 0;
    while(1){
        float h = dht.readHumidity();
        // Read temperature as Celsius (the default)
        float t = dht.readTemperature();
        //Serial.print("readDHTLoop: ");
        //Serial.println(readDHTLoop);
        // Check if any reads failed and exit early (to try again).
        if (isnan(h) || isnan(t)) {
            Serial.println("Impossible de lire la sonde DHT!");
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
            //h = h + offset_h;
            //this->DH1=String(h, 1);
            this->DH1=String(h);//getDHCalibration(h);
            this->DH1=getDHCalibration(h);
            Serial.println("calibration  Humidity: " + this->DH1 + "%");


            Serial.println("orignal Temperature: " + String(t));
            t = t + offset_t;
            this->DT1=String(t, 1);
            Serial.println("calibration  Temperature: " + this->DT1 + "*C");
            
            // Serial.print("t = t + offset_t: ");
            // Serial.print(offset_t);
            // Serial.println(" xx ");

            // Serial.print("Temperature1: ");
            // Serial.print(this->DT1);
            // Serial.println(" *C ");
            retDhtResult=true;
            break;
        }
    }
    return retDhtResult;    
}


String iotDHT::getDHCalibration(float h){
    float a =0.000091367;
    float b = -0.01452993;
    float c = 1.77623089;
    float d = -14.17403758;
    float y;

    y = a*(h*h*h) + b*(h*h) + c*h + d;
    return String(y,1);
}




iotWebAction iotDHT::setUploadData(int uploadType,ReadSetting iotReadSetting, iotWifi fabIotWifi){ 
    String sensor;
    iotWebAction DataAction;
    // //Noise
    // DataAction.BYZ08Data.env_noise_db=String(fabBYZ08.env_noise,1);
    // //Temp & Humi
    // DataAction.DhtData.DH=fabIotDht.DH1;
    // DataAction.DhtData.DT=fabIotDht.DT1;
    //Particle
    DataAction.DhtData.DH = String(DH1); 
    DataAction.DhtData.DT = String(DT1); 

    //Wifi
    DataAction.WifiData.wifiRssi =  String(fabIotWifi.getWifiRssi());
    DataAction.WifiData.ipAdress = fabIotWifi.ipAdress;
    //SENSOR ID 
    DataAction.SENSOR_ID =String(iotReadSetting.stu_sensor_DHT.id);
    DataAction.webserverHtml_Header=iotReadSetting.stu_sensor_DHT.webserverHtml_Header;
    DataAction.uploadType=uploadType;
    DataAction.machine_ID=iotReadSetting.machine_ID;
    return DataAction;
}

int iotDHT::uploadDht(iotWebAction DataAction){
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
    
    return httpCode;

}
