#include "depth_sensor.h"

DepthSensor::DepthSensor(int receivePin, int transmitPin)
    : sensorSerial(receivePin, transmitPin) {}

bool DepthSensor::init() {
  sensorSerial.begin(9600);
  return true;
}

float DepthSensor::readDistance() {
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
      float distance = (data[1] << 8) + data[2];
      if (distance > 30) {
        Serial.println("Distance sensor too close to target.");
      }
      return distance;
    }
  }

  Serial.println("Error reading distance. Retrying in 1 second...");
  delay(1000);
  return readDistance();
}