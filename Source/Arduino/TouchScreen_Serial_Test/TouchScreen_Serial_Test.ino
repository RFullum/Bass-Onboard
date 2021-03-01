// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'

#include <stdint.h>
#include "TouchScreen.h"

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// Adafruit's spec on this screen says 600 ohms X, 300 ohms Y
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 600);

void setup(void) 
{
  Serial.begin(9600);

  // Wait until serial port opens
  while (!Serial);
}

void loop(void) 
{
  // a point object holds x y and z coordinates
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  // Pressur is inversed (lower number is greater pressure)
  if (p.z > ts.pressureThreshhold) 
  {
     Serial.print("tsx"); Serial.println(p.x);
     Serial.print("tsy"); Serial.println(p.y);
     Serial.print("tsz"); Serial.println(p.z);
  }

}
