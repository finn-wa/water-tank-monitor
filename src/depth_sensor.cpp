#include "depth_sensor.h"

SoftwareSerial sensorSerial(13, 15); // RX, TX
unsigned char data[4] = {};
float distance;

void initDepthSerial() {
  Serial.begin(9600);
  sensorSerial.begin(9600);
  Serial.setDebugOutput(true);
  Serial.println("Serial successfully inited.");
}

void readFromSerial() {
  do {
    for (int i = 0; i < 4; i++) {
      data[i] = sensorSerial.read();
    }
  } while (sensorSerial.read() == 0xff);

  sensorSerial.flush();

  if (data[0] == 0xff) {
    int sum;
    sum = (data[0] + data[1] + data[2]) & 0x00FF;
    if (sum == data[3]) {
      distance = (data[1] << 8) + data[2];
      if (distance > 30) {
        Serial.print("distance=");
        Serial.print(distance / 10);
        Serial.println("cm");
      } else

      {
        Serial.println("Below the lower limit");
      }
    } else
      Serial.println("ERROR");
  }
  delay(100);
}
