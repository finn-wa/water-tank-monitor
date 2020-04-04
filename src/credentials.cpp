#include "credentials.h"

char *connectionString;
char *ssid;
char *pass;

const int8_t EEPROM_END = 0;
const int8_t EEPROM_START = 1;
const int16_t EEPROM_SIZE = 512;
const int8_t SSID_LEN = 32;
const int8_t PASS_LEN = 32;
const int16_t CONNECTION_STRING_LEN = 256;

void EEPROMWrite(int addr, char *data, int size) {
  EEPROM.begin(EEPROM_SIZE);
  // write the start marker
  EEPROM.write(addr, EEPROM_START);
  addr++;
  for (int i = 0; i < size; i++) {
    EEPROM.write(addr, data[i]);
    addr++;
  }
  EEPROM.write(addr, EEPROM_END);
  EEPROM.commit();
  EEPROM.end();
}

// read bytes from addr util '\0'
// return the length of read out.
int EEPROMread(int addr, char *buf) {
  EEPROM.begin(EEPROM_SIZE);
  int count = -1;
  char c = EEPROM.read(addr);
  addr++;
  if (c != EEPROM_START) {
    return 0;
  }
  while (c != EEPROM_END && count < EEPROM_SIZE) {
    c = (char)EEPROM.read(addr);
    count++;
    addr++;
    buf[count] = c;
  }
  EEPROM.end();
  return count;
}

// reset the EEPROM
void clearParam() {
  char data[EEPROM_SIZE];
  memset(data, '\0', EEPROM_SIZE);
  EEPROMWrite(0, data, EEPROM_SIZE);
}

bool needEraseEEPROM() {
  char result = 'n';
  readFromSerial(
      (char *)"Do you need to re-input your credential information? (Auto skip "
              "this after 5 seconds) [Y/n]",
      &result, 1, 5000);
  if (result == 'Y' || result == 'y') {
    clearParam();
    return true;
  }
  return false;
}

// Read parameters from EEPROM or Serial
void readCredentials() {
  int ssidAddr = 0;
  int passAddr = ssidAddr + SSID_LEN;
  int connectionStringAddr = passAddr + SSID_LEN;

  // malloc for parameters
  ssid = (char *)malloc(SSID_LEN);
  pass = (char *)malloc(PASS_LEN);
  connectionString = (char *)malloc(CONNECTION_STRING_LEN);

  // try to read out the credential information, if failed, the length should be
  // 0.
  int ssidLength = EEPROMread(ssidAddr, ssid);
  int passLength = EEPROMread(passAddr, pass);
  int connectionStringLength =
      EEPROMread(connectionStringAddr, connectionString);

  if (ssidLength > 0 && passLength > 0 && connectionStringLength > 0 &&
      !needEraseEEPROM()) {
    return;
  }

  // read from Serial and save to EEPROM
  readFromSerial((char *)"Input your Wi-Fi SSID: ", ssid, SSID_LEN, 0);
  EEPROMWrite(ssidAddr, ssid, strlen(ssid));

  readFromSerial((char *)"Input your Wi-Fi password: ", pass, PASS_LEN, 0);
  EEPROMWrite(passAddr, pass, strlen(pass));

  readFromSerial((char *)"Input your Azure IoT hub device connection string: ",
                 connectionString, CONNECTION_STRING_LEN, 0);
  EEPROMWrite(connectionStringAddr, connectionString, strlen(connectionString));
}