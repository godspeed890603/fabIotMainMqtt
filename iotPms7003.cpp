#include "iotPms7003.h"

void iotPms7003::initialPms() {
  Serial.println("-- iotPms7003::begin: ");
  SerialPMS7003 = new SoftwareSerial(
      D5, D6);  // SoftwareSerial(rxPin, txPin, inverse_logic)
  SerialPMS7003->begin(9600);
}

iotWebAction iotPms7003::setUploadData(int uploadType,
                                       ReadSetting iotReadSetting,
                                       iotWifi fabIotWifi) {
  String sensor;
  iotWebAction DataAction;

  // Particle
  DataAction.PmsData.max_range_0_3um = String(max_range_0_3um);
  DataAction.PmsData.max_range_0_5um = String(max_range_0_5um);
  DataAction.PmsData.max_range_1_0um = String(max_range_1_0um);
  DataAction.PmsData.max_range_2_5um = String(max_range_2_5um);
  DataAction.PmsData.max_range_5_0um = String(max_range_5_0um);
  DataAction.PmsData.max_range_10_0um = String(max_range_10_0um);
  DataAction.PmsData.um_total = String(um_total);  // V1.10
  // Wifi
  DataAction.WifiData.wifiRssi = String(fabIotWifi.getWifiRssi());
  DataAction.WifiData.ipAdress = fabIotWifi.ipAdress;
  // SENSOR ID
  Serial.println("get Pms --> " + String(iotReadSetting.stu_sensor_PMS.id));
  sensor = iotReadSetting.stu_sensor_PMS.id;
  // DataAction.SENSOR_ID
  // =String(iotReadSetting.stu_sensor_PMS.id);//"wifi111111111111";//"123456";//
  DataAction.SENSOR_ID =
      fabIotWifi.macAddress;  //"wifi111111111111";//"123456";//
  // fabIotWifi.macAddress;
  DataAction.webserverHtml_Header =
      iotReadSetting.stu_sensor_PMS.webserverHtml_Header;
  DataAction.uploadType = uploadType;
  DataAction.machine_ID = iotReadSetting.machine_ID;
  return DataAction;
}

bool iotPms7003::uploadMqttPms(iotWebAction DataAction,
                               MQTTClient* mqttClientHandler) {
  String mqttData = DataAction.getPmsJson(DataAction.uploadType);
  Serial.println(mqttData);
  if (mqttClientHandler->publishData(mqttData)) {
    Serial.println("MQTT data sent successfully.");
  } else {
    Serial.println("MQTT data sent failture....");
  }
}


int iotPms7003::uploadPms(iotWebAction DataAction) {
  int httpCode = -1;
  int httpPostLoop = 0;
  String webHtml;
  int webRerty;

  webHtml = DataAction.getUploadWebHtml(DataAction.uploadType);

  // v1.14
  if (DataAction.PmsData.um_total.toInt() == 0) {
    webRerty = 2;
  } else {
    webRerty = httpRetry;
  }

  // if (pmsLoopchange>10) {
  // pmsLoopchange=0;

  // 如果wifi有啟動,開始上傳資料
  httpCode = DataAction.uploadData(webHtml);
  // 如果wifi有啟動,開始上傳資料
  while (httpCode != 200) {
    httpPostLoop++;
    // 如果重新送httpRetry次失敗....主機重新開機
    if (httpPostLoop > webRerty) {
      // ESP.restart();
      break;
    }
    delay(1000);
    // 重新送資料
    httpCode = DataAction.uploadData(webHtml);
  }
  //}
  clearMaxRange();
  return httpCode;
}

int iotDataAction(int uploadType, iotPms7003 fabPms7003,
                  ReadSetting iotReadSetting, iotWifi fabIotWifi) {
  String sensor;
  iotWebAction DataAction;

  // Particle
  DataAction.PmsData.max_range_0_3um = String(fabPms7003.max_range_0_3um);
  DataAction.PmsData.max_range_0_5um = String(fabPms7003.max_range_0_5um);
  DataAction.PmsData.max_range_1_0um = String(fabPms7003.max_range_1_0um);
  DataAction.PmsData.max_range_2_5um = String(fabPms7003.max_range_2_5um);
  DataAction.PmsData.max_range_5_0um = String(fabPms7003.max_range_5_0um);
  DataAction.PmsData.max_range_5_0um = String(fabPms7003.max_range_5_0um);
  // Wifi
  DataAction.WifiData.wifiRssi = String(fabIotWifi.wifiRssi, 1);
  DataAction.WifiData.ipAdress = fabIotWifi.ipAdress;
  DataAction.WifiData.macAddress = fabIotWifi.macAddress;
  // SENSOR ID
  Serial.println("get Pms --> " + String(iotReadSetting.stu_sensor_PMS.id));
  sensor = iotReadSetting.stu_sensor_PMS.id;
  // DataAction.SENSOR_ID =String(iotReadSetting.stu_sensor_PMS.id);
  DataAction.SENSOR_ID = fabIotWifi.macAddress;
  Serial.println("iotReadSetting.webserverHtml_Header--> " +
                 String(iotReadSetting.stu_sensor_PMS.webserverHtml_Header));
  DataAction.webserverHtml_Header =
      iotReadSetting.stu_sensor_PMS.webserverHtml_Header;
  DataAction.uploadType = uploadType;
  String webHtml = DataAction.getUploadWebHtml(uploadType);
  Serial.println("webHtml --> " + webHtml);
  // DataUpload
  return DataAction.uploadData(webHtml);
}

void iotPms7003::getMaxRange() {
  Serial.println("-- Current_range_0_3um -->" +
                 String(singlePmsRangeData.range_0_3um));
  // Serial.println("-- max_range_0_3um -->" + String(max_range_0_3um));
  // Serial.println("-- max_range_0_5um -->" + String(max_range_0_5um));
  // Serial.println("-- max_range_1_0um -->" + String(max_range_1_0um));
  // Serial.println("-- max_range_2_5um -->" + String(max_range_2_5um));
  // Serial.println("-- max_range_5_0um -->" + String(max_range_5_0um));
  // Serial.println("-- max_range_10_0um -->" + String(max_range_10_0um));

  // 紀錄作多的那一次....
  // 出現最大顆的那一次
  // 只要有找大最大顆的!!
  // 那一次就是要上傳的資料
  if (singlePmsRangeData.range_10_0um > max_range_10_0um) {
    Serial.println("-- getMaxRange max_range_10_0um -->" +
                   String(max_range_10_0um));
    setMaxRange();
    return;
  } else if (max_range_10_0um != 0) {
    return;
  }

  // 會到這一行!!表示max_range_10_0um=0
  if (singlePmsRangeData.range_5_0um > max_range_5_0um) {
    Serial.println("-- getMaxRange max_range_5_0um -->" +
                   String(max_range_5_0um));
    setMaxRange();
    return;
  } else if (max_range_5_0um != 0) {
    return;
  }

  // 會到這一行!!max_range_5_0um=0
  if (singlePmsRangeData.range_2_5um > max_range_2_5um) {
    Serial.println("-- getMaxRange max_range_2_5um -->" +
                   String(max_range_2_5um));
    setMaxRange();
    return;
  } else if (max_range_2_5um != 0) {
    return;
  }

  // 會到這一行!!max_range_2_5um=0
  if (singlePmsRangeData.range_1_0um > max_range_1_0um) {
    Serial.println("-- getMaxRange max_range_1_0um -->" +
                   String(max_range_1_0um));
    setMaxRange();
    return;
  } else if (max_range_1_0um != 0) {
    return;
  }

  // 會到這一行!!max_range_1_0um=0
  if (singlePmsRangeData.range_0_5um > max_range_0_5um) {
    Serial.println("-- getMaxRange max_range_0_5um -->" +
                   String(max_range_0_5um));
    setMaxRange();
    return;
  } else if (max_range_0_5um != 0) {
    return;
  }

  // 會到這一行!!max_range_0_5um=0
  if (singlePmsRangeData.range_0_3um > max_range_0_3um) {
    Serial.println("-- getMaxRange max_range_0_3um -->" +
                   String(max_range_0_3um));
    setMaxRange();
    return;
  }
}

void iotPms7003::setMaxRange() {
  um_total = thisFrame.rawGt0_3um;

  max_range_0_3um = singlePmsRangeData.range_0_3um;
  Serial.println("-- max_range_0_3um -->" + String(max_range_0_3um));

  max_range_0_5um = singlePmsRangeData.range_0_5um;
  Serial.println("-- max_range_0_5um -->" + String(max_range_0_5um));

  max_range_1_0um = singlePmsRangeData.range_1_0um;
  Serial.println("-- max_range_1_0um -->" + String(max_range_1_0um));

  max_range_2_5um = singlePmsRangeData.range_2_5um;
  Serial.println("-- max_range_2_5um -->" + String(max_range_2_5um));

  max_range_5_0um = singlePmsRangeData.range_5_0um;
  Serial.println("--  max_range_5_0um -->" + String(max_range_5_0um));

  max_range_10_0um = singlePmsRangeData.range_10_0um;
  Serial.println("-- max_range_10_0um -->" + String(max_range_10_0um));
}

void iotPms7003::calculateRangePaticle() {
  //
  if (thisFrame.rawGt0_3um == 0) return;  // V1.14
  // >0.3 <0.5
  singlePmsRangeData.range_0_3um = thisFrame.rawGt0_3um - thisFrame.rawGt0_5um;
  Serial.println("-- calculateRangePaticle range_0_3um " +
                 String(singlePmsRangeData.range_0_3um));

  singlePmsRangeData.range_0_5um = thisFrame.rawGt0_5um - thisFrame.rawGt1_0um;
  Serial.println("-- calculateRangePaticle range_0_5um " +
                 String(singlePmsRangeData.range_0_5um));

  singlePmsRangeData.range_1_0um = thisFrame.rawGt1_0um - thisFrame.rawGt2_5um;
  Serial.println("-- calculateRangePaticle range_1_0um " +
                 String(singlePmsRangeData.range_1_0um));

  singlePmsRangeData.range_2_5um = thisFrame.rawGt2_5um - thisFrame.rawGt5_0um;
  Serial.println("-- calculateRangePaticle range_2_5um " +
                 String(singlePmsRangeData.range_2_5um));

  singlePmsRangeData.range_5_0um = thisFrame.rawGt5_0um - thisFrame.rawGt10_0um;
  Serial.println("-- calculateRangePaticle range_5_0um " +
                 String(singlePmsRangeData.range_5_0um));

  singlePmsRangeData.range_10_0um = thisFrame.rawGt10_0um;
  Serial.println("-- calculateRangePaticle range_10_0um " +
                 String(singlePmsRangeData.range_10_0um));

  getMaxRange();
}

void iotPms7003::clearMaxRange() {
  max_range_0_3um = 0;  // rawGt0_3um-rawGt0_5um
  max_range_0_5um = 0;  // range_0_5um-rawGt1_0um
  max_range_1_0um = 0;  // rawGt1_0um-rawGt2_5um
  max_range_2_5um = 0;  // rawGt2_5um-rawGt5_0um
  max_range_5_0um = 0;  // range_5_0um-rawGt10_0um
  max_range_10_0um = 0;
  um_total = 0;
}

// bool iotPms7003::pms_read(SoftwareSerial &pms,String PmsName) {
bool iotPms7003::pms_read() {
  //  Particle.publish("PMS5003", printbuf, 60, PRIVATE);
  // send data only when you receive data:
  Serial.println("-- Reading ");
  SerialPMS7003->begin(9600);
  bool packetReceived = false;
  while (!packetReceived) {
    if (SerialPMS7003->available() > 32) {
      int drain = SerialPMS7003->available();
      if (DEBUG) {
        Serial.print("-- Draining buffer: ");
        SerialPMS7003->println(SerialPMS7003->available(), DEC);
      }
      for (int i = drain; i > 0; i--) {
        SerialPMS7003->read();
      }
    }
    if (SerialPMS7003->available() > 0) {
      if (DEBUG) {
        Serial.print("-- Available: ");
        Serial.println(SerialPMS7003->available(), DEC);
      }
      incomingByte = SerialPMS7003->read();
      if (DEBUG) {
        Serial.print("-- READ: ");
        Serial.println(incomingByte, HEX);
      }
      if (!inFrame) {
        if (incomingByte == 0x42 && detectOff == 0) {
          frameBuf[detectOff] = incomingByte;
          thisFrame.frameHeader[0] = incomingByte;
          calcChecksum = incomingByte;  // Checksum init!
          detectOff++;
        } else if (incomingByte == 0x4D && detectOff == 1) {
          frameBuf[detectOff] = incomingByte;
          thisFrame.frameHeader[1] = incomingByte;
          calcChecksum += incomingByte;
          inFrame = true;
          detectOff++;
        } else {
          // Serial.print("-- Frame syncing... ");
          // Serial.print(incomingByte, HEX);
          if (DEBUG) {
          }
          // Serial.println();
        }
      } else {
        frameBuf[detectOff] = incomingByte;
        calcChecksum += incomingByte;
        detectOff++;
        uint16_t val = frameBuf[detectOff - 1] + (frameBuf[detectOff - 2] << 8);
        switch (detectOff) {
          case 4:
            thisFrame.frameLen = val;
            frameLen = val + detectOff;
            break;
          case 6:
            thisFrame.concPM1_0_CF1 = val;
            break;
          case 8:
            thisFrame.concPM2_5_CF1 = val;
            break;
          case 10:
            thisFrame.concPM10_0_CF1 = val;
            break;
          case 12:
            thisFrame.concPM1_0_amb = val;
            break;
          case 14:
            thisFrame.concPM2_5_amb = val;
            break;
          case 16:
            thisFrame.concPM10_0_amb = val;
            break;
          case 18:
            thisFrame.rawGt0_3um = val;
            break;
          case 20:
            thisFrame.rawGt0_5um = val;
            break;
          case 22:
            thisFrame.rawGt1_0um = val;
            break;
          case 24:
            thisFrame.rawGt2_5um = val;
            break;
          case 26:
            thisFrame.rawGt5_0um = val;
            break;
          case 28:
            thisFrame.rawGt10_0um = val;
            break;
          case 29:
            val = frameBuf[detectOff - 1];
            thisFrame.version = val;
            break;
          case 30:
            val = frameBuf[detectOff - 1];
            thisFrame.errorCode = val;
            break;
          case 32:
            thisFrame.checksum = val;
            calcChecksum -= ((val >> 8) + (val & 0xFF));
            break;
          default:
            break;
        }

        if (detectOff >= frameLen) {
          sprintf(printbuf, "PMS5003 ");
          sprintf(printbuf, "%s[%02x %02x] (%04x) ", printbuf,
                  thisFrame.frameHeader[0], thisFrame.frameHeader[1],
                  thisFrame.frameLen);
          sprintf(printbuf, "%sCF1=[%04x %04x %04x] ", printbuf,
                  thisFrame.concPM1_0_CF1, thisFrame.concPM2_5_CF1,
                  thisFrame.concPM10_0_CF1);
          sprintf(printbuf, "%samb=[%04x %04x %04x] ", printbuf,
                  thisFrame.concPM1_0_amb, thisFrame.concPM2_5_amb,
                  thisFrame.concPM10_0_amb);

          //                    sprintf(printbuf, "%sraw=[%04x %04x %04x %04x
          //                    %04x %04x] ", printbuf,
          //                        thisFrame.rawGt0_3um, thisFrame.rawGt0_5um,
          //                        thisFrame.rawGt1_0um, thisFrame.rawGt2_5um,
          //                        thisFrame.rawGt5_0um,
          //                        thisFrame.rawGt10_0um);

          // sprintf(printbuf, "%sraw=[%04d %04d %04d %04d %04d %04d] ",
          // printbuf,
          //     thisFrame.rawGt0_3um, thisFrame.rawGt0_5um,
          //     thisFrame.rawGt1_0um, thisFrame.rawGt2_5um,
          //     thisFrame.rawGt5_0um, thisFrame.rawGt10_0um);

          // Serial.print("--rawGt0_3um ");
          // Serial.println(thisFrame.rawGt0_3um);

          // Serial.print("--rawGt0_5um ");
          // Serial.println(thisFrame.rawGt0_5um);

          // Serial.print("--rawGt1_0um ");
          // Serial.println(thisFrame.rawGt1_0um);

          // Serial.print("--rawGt2_5um ");
          // Serial.println(thisFrame.rawGt2_5um);

          // Serial.print("--rawGt5_0um ");
          // Serial.println(thisFrame.rawGt5_0um);

          // Serial.print("--rawGt10_0um ");
          // Serial.println(thisFrame.rawGt10_0um);

          //
          //                    sprintf(printbuf, "%sver=%02x err=%02x ",
          //                    printbuf,
          //                        thisFrame.version, thisFrame.errorCode);
          //                    sprintf(printbuf, "%scsum=%04x %s xsum=%04x",
          //                    printbuf,
          //                        thisFrame.checksum, (calcChecksum ==
          //                        thisFrame.checksum ? "==" : "!="),
          //                        calcChecksum);
          //                    Serial.println(printbuf);

          packetReceived = true;
          detectOff = 0;
          calcChecksum = 0;
          inFrame = false;
        }
      }
    }
  }
  SerialPMS7003->flush();
  SerialPMS7003->end();
  calculateRangePaticle();

  Serial.println("-- max_range_0_3um -->" + String(max_range_0_3um));
  Serial.println("-- max_range_0_5um -->" + String(max_range_0_5um));
  Serial.println("-- max_range_1_0um -->" + String(max_range_1_0um));
  Serial.println("-- max_range_2_5um -->" + String(max_range_2_5um));
  Serial.println("-- max_range_5_0um -->" + String(max_range_5_0um));
  Serial.println("-- max_range_10_0um -->" + String(max_range_10_0um));
  return (calcChecksum == thisFrame.checksum);
}
