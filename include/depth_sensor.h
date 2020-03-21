#include <Arduino.h>
#include <SoftwareSerial.h>

// DFRobot A02YYUW
// https://wiki.dfrobot.com/A02YYUW%20Waterproof%20Ultrasonic%20Sensor%20SKU:%20SEN0311

class DepthSensor {
  int rx;
  int tx;
  SoftwareSerial sensorSerial;
  const int HEADER = 0xff;
  float depth;
  unsigned char data[4] = {};

public:
  /**
   * Creates the DepthSensor object with the supplied RX & TX pins
   */
  DepthSensor(int, int);

  /**
   * Initialises the DepthSensor.
   */
  void init();

  /**
   * Returns depth sensor reading in millimetres.
   */
  float readDepth();
};