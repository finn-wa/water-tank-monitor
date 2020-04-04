#include "iot_hub_client.h"

WiFiClientSecure sslClient; // for ESP8266

const char *onSuccess = "\"Successfully invoke device method\"";
const char *notFound = "\"No method found\"";
bool messagePending = false;

void sendCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result,
                  void *userContextCallback) {
  if (IOTHUB_CLIENT_CONFIRMATION_OK == result) {
    Serial.println("Message sent to Azure IoT Hub");
    // Blink LED
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
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

void createJson(int messageId, int depth, char *payload) {
  StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
  JsonObject &json = jsonBuffer.createObject();
  json["deviceId"] = DEVICE_ID;
  json["messageCount"] = messageId;
  if (std::isnan(depth)) {
    json["depth"] = NULL;
  } else {
    json["depth"] = depth;
  }
  json.printTo(payload, MESSAGE_MAX_LEN);
}