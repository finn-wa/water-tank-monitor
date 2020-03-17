#include <Arduino.h>
#include <SoftwareSerial.h>

class DepthSensor {
  SoftwareSerial sensorSerial;
  unsigned char data[4] = {};

public:
  /**
   * Creates the DepthSensor object with the supplied RX & TX pins
   */
  DepthSensor(int, int);

  /**
   * Initialises the DepthSensor.
   */
  bool init();

  /**
   * Returns depth sensor reading in millimetres.
   */
  float readDistance();
};