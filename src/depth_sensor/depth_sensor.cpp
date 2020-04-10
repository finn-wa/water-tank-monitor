#include "depth_sensor/depth_sensor.h"

DepthSensor::DepthSensor(int receivePin, int transmitPin)
    : rx(receivePin), tx(transmitPin), sensorSerial(receivePin, transmitPin) {}

void DepthSensor::init(bool useProcessedReadings) {
  useProcessedReadings ? digitalWrite(rx, HIGH) : digitalWrite(rx, LOW);
  sensorSerial.begin(BAUD_RATE);
  while (!sensorSerial)
    ;
}

int DepthSensor::read() {
  sensorSerial.flush();
  // Wait for data from serial
  while (true) {
    if (sensorSerial.available() >= 4 && sensorSerial.read() == HEADER) {
      data[0] = HEADER;
      for (int i = 1; i < 4; i++) {
        data[i] = sensorSerial.read();
      }
      break;
    }
  }
  // data[3] is the checksum
  if (data[3] == ((data[0] + data[1] + data[2]) & 0x00FF)) {
    depth = (data[1] << 8) + data[2];
    return depth;
  }
  return -1;
}
