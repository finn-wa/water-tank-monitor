#include "depth_sensor.h"

DepthSensor::DepthSensor(int receivePin, int transmitPin)
    : rx(receivePin), tx(transmitPin), sensorSerial(receivePin, transmitPin) {}

void DepthSensor::init() {
  digitalWrite(rx, HIGH); // Use processed readings
  sensorSerial.begin(9600);
}

float DepthSensor::readDepth() {
  // Load data from serial
  do {
    for (int i = 0; i < 4; i++) {
      data[i] = sensorSerial.read();
    }
  } while (sensorSerial.available() < 4 && sensorSerial.read() == HEADER);
  sensorSerial.flush();

  if (data[0] == HEADER) {
    int sum;
    sum = (data[0] + data[1] + data[2]) & 0x00FF;
    if (sum == data[3]) { // data[3] is the checksum
      depth = (data[1] << 8) + data[2];
      return depth;
    } else
      return -1;
  }
}
