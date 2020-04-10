#include <Arduino.h>

void initSerial();
bool readFromSerial(char *prompt, char *buf, int maxLen, int timeout);