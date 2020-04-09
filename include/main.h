#include <Arduino.h>
#include <SoftwareSerial.h>

#include "config.h"
#include "depth_sensor.h"
#include "serial_reader.h"

#if UPLOAD
#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
#include <AzureIoTUtility.h>
#include <ESP8266WiFi.h>

#include "credentials.h"
#include "iot_hub_client.h"
#endif