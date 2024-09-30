#include "ReadSetting.h"

# define INI_ITEM_CNT 15

void ReadSetting::readSetting(){
    // open file for reading
  File f = SPIFFS.open("/f.txt", "r");
  if (!f) {
    Serial.println("file open failed");
    return;
  }  
  //Serial.println("====== Reading from SPIFFS file =======");

  // write 10 strings to file
  for (int i = 1; i <= INI_ITEM_CNT; i++) {
    //Serial.println("====== Reading =======");
    String s = f.readStringUntil('\n');
    //Serial.println(s);
    getData(s);
  }

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ReadSetting::getData(String A){

    String strTest = A;
    Serial.println("Test String: " + strTest);

    StringSplitter *splitter = new StringSplitter(strTest, '=', 2);  // new StringSplitter(string_to_split, delimiter, limit)
    int itemCount = splitter->getItemCount();
    //Serial.println("Item count: " + String(itemCount));


    if (itemCount>0){
        if (splitter->getItemAtIndex(0) == "version"){
            version=splitter->getItemAtIndex(1);
            version.trim();
            //char* ip=machineID1;
            Serial.println( "version" + String(1) + ": " + String(version));
        }
      //machineID1
        if (splitter->getItemAtIndex(0) == "machine_ID"){
            machine_ID=splitter->getItemAtIndex(1);
            machine_ID.trim();
            //char* ip=machineID1;
            Serial.println( "SENSOR_ID" + String(1) + ": " + String(SENSOR_ID));
        }


         if (splitter->getItemAtIndex(0) == "mount_Device"){
            mount_Device=splitter->getItemAtIndex(1);
            mount_Device.trim();
            //char* ip=machineID1;
            Serial.println( "mount_Device" + String(1) + ": " + String(mount_Device));
        } 

        if (splitter->getItemAtIndex(0) == "sensor_DHT"){
            dhtSettingToStruct(String(splitter->getItemAtIndex(1)),&stu_sensor_DHT);   
        }
        if (splitter->getItemAtIndex(0) == "sensor_NOISE"){
            sensor_NOISE=splitter->getItemAtIndex(1);
            sensorSettingToStruct(String(splitter->getItemAtIndex(1)),&stu_sensor_NOISE);
        }
        if (splitter->getItemAtIndex(0) == "sensor_GYRO"){
            sensor_GYRO=splitter->getItemAtIndex(1);
            sensorSettingToStruct(String(splitter->getItemAtIndex(1)),&stu_sensor_GYRO);
        }
        if (splitter->getItemAtIndex(0) == "sensor_VOLT"){
            sensor_VOLT=splitter->getItemAtIndex(1);
            voltSettingToStruct(String(splitter->getItemAtIndex(1)),&stu_sensor_VOLT);
             Serial.println( "stu_sensor_VOLTAGE: " + stu_sensor_VOLT.isEnable);
        }

        if (splitter->getItemAtIndex(0) == "sensor_PMS"){
            sensor_PMS=splitter->getItemAtIndex(1);
            sensorSettingToStruct(String(splitter->getItemAtIndex(1)),&stu_sensor_PMS);
        }

        if (splitter->getItemAtIndex(0) == "sensor_VHT"){
            sensor_VHT=splitter->getItemAtIndex(1);
            sensorSettingToStruct(String(splitter->getItemAtIndex(1)),&stu_sensor_VHT);
        }

         if (splitter->getItemAtIndex(0) == "sensor_SHTXX"){
            sensor_SHT=splitter->getItemAtIndex(1);
            //V1.13
            //sensorSettingToStruct(String(splitter->getItemAtIndex(1)),&stu_sensor_ShtXX);
            ShtSettingToStruct(String(splitter->getItemAtIndex(1)),&stu_sensor_ShtXX);
        }

        if (splitter->getItemAtIndex(0) == "Wifi"){
            sensor_PMS=splitter->getItemAtIndex(1);
            WifiSettingToStruct(String(splitter->getItemAtIndex(1)),&stu_sensor_WIFI);
            Serial.println( "ssid" + String(1) + ": " +stu_sensor_WIFI.ssid);
        }


        if (splitter->getItemAtIndex(0) == "ipaddress"){
            //ROOM_NO1=splitter->getItemAtIndex(1);
            //Serial.println( "ipaddress" + String(1) + ": " + String(splitter->getItemAtIndex(1)));
            ipToIntrray(String(splitter->getItemAtIndex(1)),ip);
            //Serial.println( "getData ipaddress ip[0]: " + String(ip[0]));
        }

        if (splitter->getItemAtIndex(0) == "gateway"){
            //ROOM_NO1=splitter->getItemAtIndex(1);
            //Serial.println( "gateway" + String(1) + ": " + String(splitter->getItemAtIndex(1)));
            ipToIntrray(String(splitter->getItemAtIndex(1)),gateway);
            //Serial.println( "getData gateway ip[0]: " + String(gateway[0]));
        }

        if (splitter->getItemAtIndex(0) == "subnet"){
            //ROOM_NO1=splitter->getItemAtIndex(1);
            //Serial.println( "subnet" + String(1) + ": " + String(splitter->getItemAtIndex(1)));
            ipToIntrray(String(splitter->getItemAtIndex(1)),subnet);
            //Serial.println( "getData subnet ip[0]: " + String(subnet[0]));
        }

        if (splitter->getItemAtIndex(0) == "dns"){
            //ROOM_NO1=splitter->getItemAtIndex(1);
            //Serial.println( "dns" + String(1) + ": " + String(splitter->getItemAtIndex(1)));
            ipToIntrray(String(splitter->getItemAtIndex(1)),dns);
            //Serial.println( "getData dns ip[0]: " + String(dns[0]));
        }
    }
    delete splitter;
}


void ReadSetting::WifiSettingToStruct(String A,iot_Wifi_struct* tmpStu){
    String strTest = A;

    StringSplitter *splitter = new StringSplitter(strTest, ',', 6);  // new StringSplitter(string_to_split, delimiter, limit)
    int itemCount = splitter->getItemCount();
    //Serial.println("sensorSettingToStruct Item count: " + String(itemCount));

    if (itemCount>0){
      tmpStu->ssid=String(splitter->getItemAtIndex(0));
      Serial.println( "tmpStu->ssid: " + tmpStu->ssid);

      if (String(splitter->getItemAtIndex(1)) =="SPACE"){
        tmpStu->pwd="";
        //Serial.println( "tmpStu->pwd: " + tmpStu->pwd);
      }else{
        tmpStu->pwd=String(splitter->getItemAtIndex(1));
        //Serial.println( "tmpStu->pwd: " + tmpStu->pwd);
      }
      Serial.println( "tmpStu->pwd: " + tmpStu->pwd);
      
      if (String(splitter->getItemAtIndex(2)) =="Y" ){
        tmpStu->isEnable=true;
        Serial.println( "tmpStu->isEnable=true " + tmpStu->isEnable);
        //Serial.println( tmpStu->isEnable);
      }else if  (String(splitter->getItemAtIndex(2)) =="N" ){
        tmpStu->isEnable=false;
        Serial.println( "tmpStu->isEnable=false " + tmpStu->isEnable);
        //Serial.println( tmpStu->ReconnectInterval);
      }        
      Serial.println( "tmpStu->isEnable: " + tmpStu->isEnable);

      

      String flgDhcp = String(splitter->getItemAtIndex(3));
      Serial.println( " flgDhcp: " +  flgDhcp);
      if (String(splitter->getItemAtIndex(3)) =="Y" ){
        tmpStu->isDHCP=true;
        Serial.println( "tmpStu->isDHCP=true " + tmpStu->isEnable);
        //Serial.println( tmpStu->isEnable);
      }else if  (String(splitter->getItemAtIndex(3)) =="N" ){
        tmpStu->isDHCP=false;
        Serial.println( "tmpStu->isDHCP=false " + tmpStu->isDHCP);
        //Serial.println( tmpStu->ReconnectInterval);
      }        
      Serial.println( "tmpStu->isDHCP: " + tmpStu->isDHCP);

      tmpStu->ReconnectInterval=String(splitter->getItemAtIndex(4)).toInt();

      // // String flgDhcp = String(splitter->getItemAtIndex(4));
      // // Serial.println( " flgDhcp: " +  flgDhcp);
      // if (String(splitter->getItemAtIndex(4))  == "Y"){
      // //if (flgDhcp == "Y"){
      //   tmpStu->isDHCP=true;
      //   Serial.println( "tmpStu->isDHCP=true " + tmpStu->isDHCP);
      // }else if (String(splitter->getItemAtIndex(4)) == "N"){
      //   tmpStu->isDHCP=false;
      //   Serial.println( "tmpStu->isDHCP=fasle " + tmpStu->isDHCP);
      // }

      // Serial.println( " tmpStu->is: " +  String(splitter->getItemAtIndex(4)));

    }
    delete splitter;
}


void ReadSetting::ipToIntrray(String A,int* tmpArray){
    String ipStr;
    int ip;

    //Serial.println(F("ipToByteArray"));

    //String strTest = "123,456,789,abc";#
    String strTest = A;
    //Serial.println("ipToByteArray Test String: " + strTest);

    StringSplitter *splitter = new StringSplitter(strTest, '.', 4);  // new StringSplitter(string_to_split, delimiter, limit)
    int itemCount = splitter->getItemCount();
    Serial.println("ipToByteArray Item count: " + String(itemCount));


    if (itemCount>0){
      //machineID1
        // if (splitter->getItemAtIndex(0) == "machineID"){
        //ip 1st        
        ipStr=String(splitter->getItemAtIndex(0));
        ip=ipStr.toInt();
        //Serial.print("ipToByteArray String(splitter->getItemAtIndex(0)).toInt -------------->");
        //Serial.println(ip);
        tmpArray[0]=ip;
        Serial.print("ipToByteArray byteIpArray[0] -------------->");
        Serial.println( tmpArray[0]);
        //ip 2nd 
        ipStr=String(splitter->getItemAtIndex(1));
        ip=ipStr.toInt();
        //Serial.print("ipToByteArray String(splitter->getItemAtIndex(0)).toInt -------------->");
        //Serial.println(ip);
        tmpArray[1]=ip;
        Serial.print("ipToByteArray byteIpArray[0] -------------->");
        Serial.println( tmpArray[1]);
        
        //ip 3rd
        ipStr=String(splitter->getItemAtIndex(2));
        ip=ipStr.toInt();
        //Serial.print("ipToByteArray String(splitter->getItemAtIndex(0)).toInt -------------->");
        //Serial.println(ip);
        tmpArray[2]=ip;
        Serial.print("ipToByteArray byteIpArray[0] -------------->");
        Serial.println( tmpArray[2]);
        
        //ip 4th
        ipStr=String(splitter->getItemAtIndex(3));
        ip=ipStr.toInt();
        //Serial.print("ipToByteArray String(splitter->getItemAtIndex(0)).toInt -------------->");
        //Serial.println(ip);
        tmpArray[3]=ip;
        Serial.print("ipToByteArray byteIpArray[0] -------------->");
        Serial.println( tmpArray[3]);
        
    }
    delete splitter;
}


void ReadSetting::sensorSettingToStruct(String A,iot_Sensor_struct* tmpStu){
    String strTest = A;
   
    StringSplitter *splitter = new StringSplitter(strTest, ',', 7);  // new StringSplitter(string_to_split, delimiter, limit)
    int itemCount = splitter->getItemCount();
    //Serial.println("sensorSettingToStruct Item count: " + String(itemCount)); 
    //Serial.println("sensorSettingToStruct Item String: " + String(strTest)); 

    if (itemCount>0){
      tmpStu->id=String(splitter->getItemAtIndex(0));
      tmpStu->DataType=String(splitter->getItemAtIndex(1)).toInt();
      if (String(splitter->getItemAtIndex(2)) =="Y" ){
        tmpStu->isEnable=true;
        //Serial.println( tmpStu->isEnable);
      }else if  (String(splitter->getItemAtIndex(2)) =="N" ){
        tmpStu->isEnable=false;
        //Serial.println( tmpStu->isEnable);
      }        
      tmpStu->actioInterval=String(splitter->getItemAtIndex(3)).toInt();
      tmpStu->uploadLoop=String(splitter->getItemAtIndex(4)).toInt();
      
      tmpStu->webServerIP=String(splitter->getItemAtIndex(5));
      tmpStu->webServerIP.trim();
     // Serial.println(" tmpStu->webServerIP: " + String(splitter->getItemAtIndex(5)));
      tmpStu->webApString=String(splitter->getItemAtIndex(6));
      tmpStu->webApString.trim();
      //Serial.println("tmpStu->webApString: " + String(tmpStu->webApString));
      tmpStu->webserverHtml_Header="http://" + tmpStu->webServerIP + "/" + tmpStu->webApString +"?";
      tmpStu->webserverHtml_Header.trim();
     // Serial.println("tmpStu->webserverHtml_Header: " + String(tmpStu->webserverHtml_Header));
    }
    delete splitter;
}

void ReadSetting::voltSettingToStruct(String A,iot_Volt_Sensor_struct* tmpStu){
    String strTest = A;
   
    StringSplitter *splitter = new StringSplitter(strTest, ',', 9);  // new StringSplitter(string_to_split, delimiter, limit)
    int itemCount = splitter->getItemCount();
    //Serial.println("sensorSettingToStruct Item count: " + String(itemCount)); 
    //Serial.println("sensorSettingToStruct Item String: " + String(strTest)); 

    if (itemCount>0){
      tmpStu->id=String(splitter->getItemAtIndex(0));
      tmpStu->DataType=String(splitter->getItemAtIndex(1)).toInt();
      if (String(splitter->getItemAtIndex(2)) =="Y" ){
        tmpStu->isEnable=true;
        //Serial.println( "stu_sensor_VOLTAGE: " + tmpStu->isEnable);
        //Serial.println( tmpStu->isEnable);
      }else if  (String(splitter->getItemAtIndex(2)) =="N" ){
        tmpStu->isEnable=false;
        //Serial.println( "stu_sensor_VOLTAGE: " + tmpStu->isEnable);
        //Serial.println( tmpStu->isEnable);
      }        
      tmpStu->actioInterval=String(splitter->getItemAtIndex(3)).toInt();
      tmpStu->uploadLoop=String(splitter->getItemAtIndex(4)).toInt();
      
      tmpStu->webServerIP=String(splitter->getItemAtIndex(5));
      tmpStu->webServerIP.trim();
      //Serial.println(" tmpStu->webServerIP: " + String(splitter->getItemAtIndex(5)));
      tmpStu->webApString=String(splitter->getItemAtIndex(6));
      tmpStu->webApString.trim();
      //Serial.println("tmpStu->webApString: " + String(tmpStu->webApString));
      tmpStu->webserverHtml_Header="http://" + tmpStu->webServerIP + "/" + tmpStu->webApString +"?";
      tmpStu->webserverHtml_Header.trim();
      //Serial.println("tmpStu->webserverHtml_Header: " + String(tmpStu->webserverHtml_Header));

      tmpStu->m=String(splitter->getItemAtIndex(7)).toFloat();
      tmpStu->c=String(splitter->getItemAtIndex(8)).toFloat();
      Serial.println("tmpStu->c: " + String(tmpStu->c));
    }
    delete splitter;
}

void ReadSetting::dhtSettingToStruct(String A,iot_Dht_Sensor_struct* tmpStu){
    String strTest = A;
  
    StringSplitter *splitter = new StringSplitter(strTest, ',', 9);  // new StringSplitter(string_to_split, delimiter, limit)
    int itemCount = splitter->getItemCount();
    //Serial.println("sensorSettingToStruct Item count: " + String(itemCount)); 
    //Serial.println("sensorSettingToStruct Item String: " + String(strTest)); 

    if (itemCount>0){
      tmpStu->id=String(splitter->getItemAtIndex(0));
      tmpStu->DataType=String(splitter->getItemAtIndex(1)).toInt();
      if (String(splitter->getItemAtIndex(2)) =="Y" ){
        tmpStu->isEnable=true;
        //Serial.println( tmpStu->isEnable);
      }else if  (String(splitter->getItemAtIndex(2)) =="N" ){
        tmpStu->isEnable=false;
        //Serial.println( tmpStu->isEnable);
      }        
      tmpStu->actioInterval=String(splitter->getItemAtIndex(3)).toInt();
      tmpStu->uploadLoop=String(splitter->getItemAtIndex(4)).toInt();
      
      tmpStu->webServerIP=String(splitter->getItemAtIndex(5));
      tmpStu->webServerIP.trim();
      //Serial.println(" tmpStu->webServerIP: " + String(splitter->getItemAtIndex(5)));
      tmpStu->webApString=String(splitter->getItemAtIndex(6));
      tmpStu->webApString.trim();
      //Serial.println("tmpStu->webApString: " + String(tmpStu->webApString));
      tmpStu->webserverHtml_Header="http://" + tmpStu->webServerIP + "/" + tmpStu->webApString +"?";
      tmpStu->webserverHtml_Header.trim();
      //Serial.println("tmpStu->webserverHtml_Header: " + String(tmpStu->webserverHtml_Header));
      tmpStu->dht_offset_t=String(splitter->getItemAtIndex(7)).toFloat();
      tmpStu->dht_offset_h=String(splitter->getItemAtIndex(8)).toFloat();
      //Serial.println("tmpStu->dht_offset_t: " + String(tmpStu->dht_offset_t));
    }
    delete splitter;
}

//V1.13
void ReadSetting::ShtSettingToStruct(String A,iot_Sht_Sensor_struct* tmpStu){
    String strTest = A;
   

    StringSplitter *splitter = new StringSplitter(strTest, ',', 9);  // new StringSplitter(string_to_split, delimiter, limit)
    int itemCount = splitter->getItemCount();
    //Serial.println("sensorSettingToStruct Item count: " + String(itemCount)); 
    //Serial.println("sensorSettingToStruct Item String: " + String(strTest)); 

    if (itemCount>0){
      tmpStu->id=String(splitter->getItemAtIndex(0));
      tmpStu->DataType=String(splitter->getItemAtIndex(1)).toInt();
      if (String(splitter->getItemAtIndex(2)) =="Y" ){
        tmpStu->isEnable=true;
        //Serial.println( tmpStu->isEnable);
      }else if  (String(splitter->getItemAtIndex(2)) =="N" ){
        tmpStu->isEnable=false;
        //Serial.println( tmpStu->isEnable);
      }        
      tmpStu->actioInterval=String(splitter->getItemAtIndex(3)).toInt();
      tmpStu->uploadLoop=String(splitter->getItemAtIndex(4)).toInt();
      
      tmpStu->webServerIP=String(splitter->getItemAtIndex(5));
      tmpStu->webServerIP.trim();
      //Serial.println(" tmpStu->webServerIP: " + String(splitter->getItemAtIndex(5)));
      tmpStu->webApString=String(splitter->getItemAtIndex(6));
      tmpStu->webApString.trim();
      //Serial.println("tmpStu->webApString: " + String(tmpStu->webApString));
      tmpStu->webserverHtml_Header="http://" + tmpStu->webServerIP + "/" + tmpStu->webApString +"?";
      tmpStu->webserverHtml_Header.trim();
      //Serial.println("tmpStu->webserverHtml_Header: " + String(tmpStu->webserverHtml_Header));
      tmpStu->offset_t=String(splitter->getItemAtIndex(7)).toFloat();
      Serial.println(" tmpStu->offset_h: " + String(tmpStu->offset_t));
      tmpStu->offset_h=String(splitter->getItemAtIndex(8)).toFloat();
      Serial.println(" tmpStu->offset_h: " + String(tmpStu->offset_h));
    }
    delete splitter;
}
