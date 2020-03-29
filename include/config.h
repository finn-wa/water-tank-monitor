// Physical device information for board and sensor
#define DEVICE_ID "FeatherHuzzah1"
#define DHT_TYPE DHT22

// Configuration for depth sensor
#define USE_PROCESSED_READINGS 1

// Pin layout configuration
#define LED_PIN 0
#define DHT_PIN 2

// Interval time(ms) for sending message to IoT Hub
#define INTERVAL 10000

// EEPROM address configuration
#define EEPROM_SIZE 512

// SSID and SSID password's length should < 32 bytes
// http://serverfault.com/a/45509
#define SSID_LEN 32
#define PASS_LEN 32
#define CONNECTION_STRING_LEN 256

#define MESSAGE_MAX_LEN 256
