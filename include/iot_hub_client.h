#include "config.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
#include <AzureIoTUtility.h>
#include <WiFiClientSecure.h>

void sendMessage(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, char *payload);

void createJson(int messageId, int depth, char *payload);