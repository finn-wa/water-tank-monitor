#include <Arduino.h>
#include <SoftwareSerial.h>

/**
 * @brief Class for interacting with the depth sensor. Designed for use with a
 * DFRobot A02YYUW (see documentation:
 * https://wiki.dfrobot.com/A02YYUW%20Waterproof%20Ultrasonic%20Sensor%20SKU:%20SEN0311)
 *
 */
class DepthSensor {
  // Constants
  const int HEADER = 0xff;
  const int BAUD_RATE = 9600;
  // Serial
  int rx;
  int tx;
  SoftwareSerial sensorSerial;
  // Data
  float depth;
  unsigned char data[4] = {};

public:
  /**
   * @brief Construct a new Depth Sensor object
   *
   * @param receivePin RX pin for the SoftwareSerial
   * @param transmitPin TX pin for the SoftwareSerial
   */
  DepthSensor(int receivePin, int transmitPin);

  /**
   * @brief Initialises the DepthSensor.
   *
   * @param useProcessedReadings When set to true, readings take 100-300ms and
   * processes each value properly. When set to false, sensor consistently
   * outputs readings every 100ms they may be less reliable.
   */
  void init(bool useProcessedReadings);

  /**
   * @brief Reads from the depth sensor. Returns the distance to the closest
   * object.
   *
   * @return int The depth sensor reading in millimetres.
   */
  int read();

  /**
   * @brief Reads from the depth sensor as many times as specified. Returns the
   * median reading.
   * @param numReadings The number of times to read from the sensor. If set to
   * an even number, it will be incremented so it is odd.
   * @return int The median depth sensor reading in millimetres.
   */
  int readMedian(size_t numReadings);
};