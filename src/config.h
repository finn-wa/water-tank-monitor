const unsigned long SECOND = 1000UL;
const unsigned long MINUTE = 60UL * SECOND;
const unsigned long HOUR = 60UL * MINUTE;

// Interval time(ms) for sending message to IoT Hub
const unsigned long INTERVAL = 30UL * SECOND;

// Physical device information for board and sensor
const char *DEVICE_ID = "FeatherHuzzah1";

// Configuration for depth sensor
const bool USE_PROCESSED_READINGS = true;

// Pin layout configuration
const int8_t LED_PIN = 0;
const int8_t RX_PIN = 13;
const int8_t TX_PIN = 15;