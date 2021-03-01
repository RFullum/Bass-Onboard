#include <Arduino_LSM6DS3.h>

void setup() 
{
  // Start Serial
  Serial.begin(9600);
  
  // Wait until Serial starts
  while (!Serial);
  
  // Warn if IMU isn't working and wait.
  if (!IMU.begin())
  {
    Serial.println("IMU no work");

    while(1);
  }
}


void loop() 
{
  float accelX, accelY, accelZ;
  float gyroX,  gyroY,  gyroZ;

  // If there is incoming data available...
  if (Serial.available() > 0)
  {
    // If that incoming data is boolean true
    if (Serial.read() == true)
    {
      // Read Accelerometer Values and send over Serial with value tags
      if (IMU.accelerationAvailable())
      {
        IMU.readAcceleration(accelX, accelY, accelZ);
        
        Serial.print("ax");
        Serial.println(accelX);
    
        Serial.print("ay");
        Serial.println(accelY);
    
        Serial.print("az");
        Serial.println(accelZ);
      }

      // Read Gyroscope Values and send over Serial with value tags
      if (IMU.gyroscopeAvailable())
      {
        IMU.readGyroscope(gyroX, gyroY, gyroZ);
  
        Serial.print("gx");
        Serial.println(gyroX);
  
        Serial.print("gy");
        Serial.println(gyroY);
  
        Serial.print("gz");
        Serial.println(gyroZ);
      }
      
    }
    
  }
  
}
