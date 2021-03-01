/*
  ==============================================================================

    Accelerometer.h
    Created: 28 Feb 2021 4:09:45pm
    Author:  Robert Fullum
    
    
    Written for Arduino Nano 33 IoT internal IMU Accelerometer and Gyroscope ->
    Serial Connection via USB Port
 
    Used in conjunction with SerialConnect class, it takes the data from the
    Serial stream, extracts the sub-Strings tagged for Accelerometer (ax, ay, ax),
    or Gyroscope (gx, gy, gz), and returns the distance as a float in millimeters.
    The Accelerometer values are from -4.0f to 4.0f, with gravity being 1.0f. Values
    between -1.0f and 1.0f are the orientation. Greater than 1.0f or less than -1.0f
    are movements that more Gs than gravity, for instance, stopping suddenly from speed.
    The Gyroscope measures directions of movement, range -2000.0f to 2000.0f.
 
 
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Accelerometer
{
public:
    Accelerometer();
    ~Accelerometer();

    
    /**
    Takes a String in the form of "[TAG][VALUE]\n". Uses the TAG to route the value to the appropriate variable and converts to float
    Call in timerCallback()
    */
    void setAccelValue(String& stringIn);
    
    /// Returns the X value from the Accelerometer, -4.0f to 4.0f
    float getAccelX();
    
    /// Returns the Y value from the Accelerometer, -4.0f to 4.0f
    float getAccelY();
    
    /// Returns the Z value from the Accelerometer, -4.0f to 4.0f
    float getAccelZ();

private:
    float smoothingFactor;
    float smoothValX;
    float smoothValY;
    float smoothValZ;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Accelerometer)
};



//==============================================================================
//==============================================================================
//==============================================================================

class Gyroscope
{
public:
    Gyroscope();
    ~Gyroscope();
    
    /**
    Takes a String in the form of "[TAG][VALUE]\n". Uses the TAG to route the value to the appropriate variable and converts to float
    Call in timerCallback()
    */
    void setGyroValue(String& stringIn);
    
    /// Returns Gyroscope's X value -2000.0f to 2000.0f
    float getGyroX();
    
    /// Returns Gyroscope's Y value -2000.0f to 2000.0f
    float getGyroY();
    
    /// Returns Gyroscope's Z value -2000.0f to 2000.0f
    float getGyroZ();
    
private:
    float smoothingFactor;
    float smoothGyroX;
    float smoothGyroY;
    float smoothGyroZ;
};
