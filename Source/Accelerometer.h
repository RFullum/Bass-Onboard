/*
  ==============================================================================

    Accelerometer.h
    Created: 28 Feb 2021 4:09:45pm
    Author:  Robert Fullum

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

    
    /// Called in timerCalback() to read accelerometer values from Arduino via Serial (USB)
    void setAccelValue(String& stringIn);
    
    /// Returns the X value from the Accelerometer, -4.0f to 4.0f
    float getAccelX();
    
    /// Returns the Y value from the Accelerometer, -4.0f to 4.0f
    float getAccelY();
    
    /// Returns the Z value from the Accelerometer, -4.0f to 4.0f
    float getAccelZ();

private:
    String accelStr;
    
    float smoothingFactor;
    float smoothValX;
    float smoothValY;
    float smoothValZ;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Accelerometer)
};
