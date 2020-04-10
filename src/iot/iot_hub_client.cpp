#include "iot/iot_hub_client.h"

const int16_t MESSAGE_MAX_LEN = 256;
bool messagePending = false;
WiFiClientSecure sslClient; // for ESP8266

void sendCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result,
                  void *userContextCallback) {
  if (IOTHUB_CLIENT_CONFIRMATION_OK == result) {
    Serial.println("Message sent to Azure IoT Hub");
  } else {
    Serial.println("Failed to send message to Azure IoT Hub");
  }
  messagePending = false;
}

void sendMessage(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, char *payload) {
  IOTHUB_MESSAGE_HANDLE messageHandle = IoTHubMessage_CreateFromByteArray(
      (const unsigned char *)payload, strlen(payload));
  if (messageHandle == NULL) {
    Serial.println("Unable to create a new IoTHubMessage.");
  } else {
    Serial.printf("Sending message: %s.\r\n", payload);
    if (IoTHubClient_LL_SendEventAsync(iotHubClientHandle, messageHandle,
                                       sendCallback,
                                       NULL) != IOTHUB_CLIENT_OK) {
      Serial.println("Failed to hand over the message to IoTHubClient.");
    } else {
      messagePending = true;
      Serial.println("IoTHubClient accepted the message for delivery.");
    }
    IoTHubMessage_Destroy(messageHandle);
  }
}

void createJson(int depth, int messageId, const char *deviceId, char *payload) {
  StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
  JsonObject &json = jsonBuffer.createObject();
  json["deviceId"] = deviceId;
  json["messageCount"] = messageId;
  if (std::isnan(depth)) {
    json["depth"] = NULL;
  } else {
    json["depth"] = depth;
  }
  json.printTo(payload, MESSAGE_MAX_LEN);
}