#include <Arduino.h>
#include <ArduinoJson.h>

#include "config.h"
// #include "main.h"

extern int interval;

void initSensor();
bool readMessage(int messageId, char *payload);
void parseTwinMessage(char *message);