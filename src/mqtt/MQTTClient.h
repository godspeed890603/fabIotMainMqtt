#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

// 根據平台選擇使用的 WiFi 庫
#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <PubSubClient.h>

// MQTTClient 類別的宣告
class MQTTClient {
 public:
  // 構造函數
  MQTTClient();

  // 連接到 MQTT 伺服器
  void connect();

  // 處理收到的訊息
  void onMessage(char* topic, byte* payload, unsigned int length);

  // 循環處理
  void loop();

  // 發佈資料到指定的 MQTT topic
  bool publishData(String data);

  void setServiceName(String serviceString);
  void CreatePubSubTopic();

 private:
  // 處理接收到的訊息
  void processMessage(const String& topic, const String& message);

  // IoT 資料處理
  void iotProcess(const String& payload, const String& macAddress,
                  const String& serviceName);

  // 呼叫外部服務
  void callService(const String& executable, const String& macAddress);

  // 日誌功能模擬
  void log_message(const String& msg);

  // 處理接收到的MQTT消息
  void callback(char* topic, byte* payload, unsigned int length);

  const char* mqtt_server = "172.27.17.250";  // 替換為您的 MQTT broker 地址
  const int mqtt_port = 1883;        // 替換為您的 MQTT broker 端口
  const char* mqtt_user = "eason";   // 替換為您的 MQTT 使用者名稱
  const char* mqtt_pass = "qazwsx";  // 替換為您的 MQTT 密碼
  String serviceName;
  const String mqtt_request_topic_prefix = "request/iot/";
  const String mqtt_subscribe_topic_prefix = "response/iot/";

  String mqtt_request_topic;  // 替換為您的 MQTT 主題
  String mqtt_subscribe_topic;

 private:
  WiFiClient espClient;  // 定義 WiFiClient 實例
  PubSubClient* client;  // 定義 PubSubClient 並傳遞 espClien
  int qos_subscribe = 1;
  int qos_publish = 1;
};

#endif  // MQTTCLIENT_H
