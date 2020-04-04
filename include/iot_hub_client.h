#include <ArduinoJson.h>
#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
#include <AzureIoTUtility.h>
#include <WiFiClientSecure.h>

extern const int16_t MESSAGE_MAX_LEN;
extern bool messagePending;

void sendMessage(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, char *payload);

void createJson(int depth, int messageId, const char *deviceId, char *payload);