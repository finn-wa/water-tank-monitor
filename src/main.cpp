#include "main.h"

char *connectionString;
char *ssid;
char *pass;
IOTHUB_CLIENT_LL_HANDLE handle;

int messageCount = 1;
extern bool messagePending;
extern bool messageSending;
unsigned long interval = INTERVAL;

DepthSensor depthSensor(13, 15);
int depth;

void initWifi() {
  Serial.printf("Attempting to connect to WiFi network %s...\n", ssid);
  // Connect to WPA/WPA2 network
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    uint8_t mac[6];
    WiFi.macAddress(mac);
    Serial.printf("Device with MAC address %02x:%02x:%02x:%02x:%02x:%02x "
                  "failed to connect to %s! Waiting 10 seconds to retry...\n",
                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], ssid);
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

void setup() {
  initSerial();
  depthSensor.init(USE_PROCESSED_READINGS);

  pinMode(LED_PIN, OUTPUT);
  delay(2000);

  readCredentials();
  initWifi();
  initTime();

  Serial.println("Setting up Azure...");
  handle = IoTHubClient_LL_CreateFromConnectionString(connectionString,
                                                      MQTT_Protocol);
  if (handle == NULL) {
    Serial.println("Failed on IoTHubClient_CreateFromConnectionString.");
    while (1)
      ;
  }
  Serial.println("Finished setup.");
}

void loop() {
  depth = depthSensor.read();
  if (depth == -1) {
    Serial.println("Error reading from depth sensor.");
  } else if (depth > 30) {
    Serial.printf("Distance: %dmm\n", depth);
  } else {
    Serial.println("Object too close to depth sensor.");
  }
  if (!messagePending && messageSending) {
    char messagePayload[MESSAGE_MAX_LEN];
    createJson(messageCount, depth, messagePayload);
    sendMessage(handle, messagePayload);
    messageCount++;
  }
  IoTHubClient_LL_DoWork(handle);
  delay(interval);
}