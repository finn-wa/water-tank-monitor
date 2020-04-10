#include <EEPROM.h>
#include <stdlib.h>

#include "serial_reader/serial_reader.h"

extern char *connectionString;
extern char *ssid;
extern char *pass;

void readCredentials();
