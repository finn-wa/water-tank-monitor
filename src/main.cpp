#include "main.h"

char *connectionString;
char *ssid;
char *pass;
IOTHUB_CLIENT_LL_HANDLE handle;
int messageCount = 1;

void initWifi() {
  Serial.printf("Attempting to connect to WiFi network %s...\n", ssid);
  // Connect to WPA/WPA2 network
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    uint8_t mac[6];
    WiFi.macAddress(mac);
    Serial.printf("Device with MAC address %02x:%02x:%02x:%02x:%02x:%02x "
                  "failed to connect to %s! Waiting 10 seconds to
                  retry...\n ", mac[0], mac[1], mac[2], mac[3], mac[4],
                  mac[5],
                  ssid);
    WiFi.begin(ssid, pass);
    delay(10000);
  }
  Serial.printf("Connected to WiFi network %s.\n", ssid);
}

void initTime() {
  configTime(0, 0, "pool.ntp.org", "s1.ntp.net.nz");
  time_t epochTime = 0;
  while (epochTime == 0) {
    epochTime = time(NULL);
    if (epochTime == 0) {
      Serial.println(
          "Failed to fetch NTP epoch time! Waiting 2 seconds to retry...");
      delay(2000);
    }
  }
  Serial.printf("Fetched NTP epoch time: %lu.\n", epochTime);
}

DepthSensor depthSensor(13, 15);

void setup() {
  initSerial();
  depthSensor.init();

  pinMode(LED_PIN, OUTPUT);
  delay(2000);

  readCredentials();
  initWifi();
  initTime();
  initSensor();

  Serial.println("Setting up Azure...");
  handle = IoTHubClient_LL_CreateFromConnectionString(connectionString,
                                                      MQTT_Protocol);
  if (handle == NULL) {
    Serial.println("Failed on IoTHubClient_CreateFromConnectionString.");
    while (1)
      ;
  }
  IoTHubClient_LL_SetMessageCallback(handle, receiveMessageCallback, NULL);
  IoTHubClient_LL_SetDeviceMethodCallback(handle, deviceMethodCallback, NULL);
  IoTHubClient_LL_SetDeviceTwinCallback(handle, twinCallback, NULL);
  Serial.println("Finished setup.");
}

void loop() {
  depthSensor.readDistance();
  Serial.printf("Distance: %fmm\n", distance);
  if (!messagePending && messageSending) {
    char messagePayload[MESSAGE_MAX_LEN];
    bool temperatureAlert = readMessage(messageCount, messagePayload);
    sendMessage(handle, messagePayload, temperatureAlert);
    messageCount++;
    delay(interval);
  }
  IoTHubClient_LL_DoWork(handle);
  delay(10);
}