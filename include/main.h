#include <Arduino.h>
#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
#include <AzureIoTUtility.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>

#include "config.h"
#include "credentials.h"
#include "depth_sensor.h"
#include "iot_hub_client.h"
#include "message.h"
#include "serial_reader.h"

extern bool messagePending;
extern bool messageSending;