#include <Arduino.h>
#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
#include <AzureIoTUtility.h>
#include <WiFiClientSecure.h>

#include "config.h"
#include "message.h"

void sendMessage(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, char *buffer,
                 bool temperatureAlert);

IOTHUBMESSAGE_DISPOSITION_RESULT
receiveMessageCallback(IOTHUB_MESSAGE_HANDLE message,
                       void *userContextCallback);

int deviceMethodCallback(const char *methodName, const unsigned char *payload,
                         size_t size, unsigned char **response,
                         size_t *response_size, void *userContextCallback);

void twinCallback(DEVICE_TWIN_UPDATE_STATE updateState,
                  const unsigned char *payLoad, size_t size,
                  void *userContextCallback);