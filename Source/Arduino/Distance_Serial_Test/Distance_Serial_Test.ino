#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() 
{
  Serial.begin(115200);

  // Wait until serial port opens
  while (!Serial);

  // Warn if sensor isn't working
  if (!lox.begin())
  {
    Serial.println("Sensor no work");

    while(1);
  }
}



void loop() 
{
  VL53L0X_RangingMeasurementData_t measure;
  
  lox.rangingTest(&measure, false);

  if (measure.RangeStatus !=4)
  {
    // If in range, send measurement
    Serial.println(measure.RangeMilliMeter);
  }
  else
  {
    // If out of range, send 0.0f
    Serial.println(0.0f);
  }

  
}
