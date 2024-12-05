#include "MQTTClient.h"

// 定義 MQTTClient 類別

// 构造函数
MQTTClient::MQTTClient() {
  client = new PubSubClient(espClient);
  log_message("Connected to MQTT broker111");
  client->setBufferSize(1024);
  client->setServer(mqtt_server, mqtt_port);
  // 使用 lambda 表達式來捕捉 this 指針，以便在回調中使用成員函數
  client->setCallback([this](char* topic, byte* payload, unsigned int length) {
    this->callback(topic, payload, length);  // 調用非靜態成員函數
  });
  log_message("Connected to MQTT broker222");
}

void MQTTClient::setServiceName(String serviceString) {
  serviceName = "/" + serviceString;
}

void MQTTClient::CreatePubSubTopic() {
  mqtt_subscribe_topic = mqtt_subscribe_topic_prefix + WiFi.macAddress() + serviceName;
  Serial.println("mqtt_subscribe_topic: " + mqtt_subscribe_topic);
  mqtt_request_topic = mqtt_request_topic_prefix + WiFi.macAddress() + serviceName;
  Serial.println("mqtt_request_topic :" + mqtt_request_topic);
}

// 處理接收到的MQTT消息
void MQTTClient::callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Message arrive......................");
}

// 連接到 MQTT 伺服器
void MQTTClient::connect() {
  while (!client->connected()) {
    log_message("Connecting to MQTT broker...");
    if (client->connect(WiFi.macAddress().c_str(), mqtt_user, mqtt_pass)) {
      log_message("Connected to MQTT broker");
      client->subscribe(mqtt_subscribe_topic.c_str(), qos_subscribe);
    } else {
      log_message("Failed to connect to MQTT broker, retrying...");
      delay(5000);
    }
  }
}

// 處理收到的訊息
void MQTTClient::onMessage(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  log_message("Received message: " + message);
  processMessage(String(topic), message);
}

// 循環處理
void MQTTClient::loop() {
  if (!client->connected()) {
    log_message("mqtt reconnect......");
    connect();
  }
  log_message("mqtt loop......");
  client->loop();
}

// 發佈資料到指定的 MQTT topic
bool MQTTClient::publishData(String data) {
  if (!client->connected()){
     log_message("publish data,but mqtt disconnect!!....");
     connect();
  }
  if (client->publish(mqtt_request_topic.c_str(), data.c_str(), qos_publish)) {
    log_message("Data published successfully: " + data);
    return true;
  } else {
    log_message("Failed to publish data to " + mqtt_request_topic);
    return false;
  }
}

// 處理接收到的訊息
void MQTTClient::processMessage(const String& topic, const String& message) {
  log_message("Processing message for topic: " + topic);

  // 模擬分割與處理 IoT 訊息
  if (topic.startsWith("iot/")) {
    String macAddress = topic.substring(4, topic.indexOf('/', 4));
    String serviceName = topic.substring(topic.lastIndexOf('/') + 1);

    log_message("Processing IoT data for MAC: " + macAddress +
                ", Service: " + serviceName);
    iotProcess(message, macAddress, serviceName);
  }
}

// IoT 資料處理
void MQTTClient::iotProcess(const String& payload, const String& macAddress,
                            const String& serviceName) {
  log_message("IoT process - Payload: " + payload +
              ", Service: " + serviceName);
  callService("service1.py", macAddress);
}

// 呼叫外部服務
void MQTTClient::callService(const String& executable, const String& macAddress) {
  log_message("Calling service: " + executable + " for MAC: " + macAddress);
}

// 日誌功能模擬
void MQTTClient::log_message(const String& msg) { Serial.println(msg); }
