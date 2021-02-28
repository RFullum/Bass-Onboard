/*
  ==============================================================================

    Accelerometer.cpp
    Created: 28 Feb 2021 4:09:45pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Accelerometer.h"

//==============================================================================
Accelerometer::Accelerometer() : smoothingFactor(0.4f), smoothValX(0.0f), smoothValY(0.0f), smoothValZ(0.0f)
{}

Accelerometer::~Accelerometer() {}


/// Called in timerCalback() to read accelerometer values from Arduino via Serial (USB)
void Accelerometer::setAccelValue(String& stringIn)
{
    float accelX = 0.0f;
    float accelY = 0.0f;
    float accelZ = 0.0f;
    
    String accelXStr;
    String accelYStr;
    String accelZStr;
    
    accelXStr   = stringIn.fromFirstOccurrenceOf ( "ax", false, true ).upToFirstOccurrenceOf ( "\n", false, true );
    accelX      = accelXStr.getDoubleValue();
    smoothValX += ( accelX - smoothValX ) * smoothingFactor;
    
    accelYStr   = stringIn.fromFirstOccurrenceOf ( "ay", false, true ).upToFirstOccurrenceOf ( "\n", false, true );
    accelY      = accelYStr.getDoubleValue();
    smoothValY += ( accelY - smoothValY ) * smoothingFactor;
    
    accelZStr   = stringIn.fromFirstOccurrenceOf ( "az", false, true ).upToFirstOccurrenceOf ( "\n", false, true );
    accelZ      = accelZStr.getDoubleValue();
    smoothValZ += ( accelZ - smoothValZ ) * smoothingFactor;
}


/// Returns the X value from the Accelerometer, -4.0f to 4.0f
float Accelerometer::getAccelX()
{
    return smoothValX;
}

/// Returns the Y value from the Accelerometer, -4.0f to 4.0f
float Accelerometer::getAccelY()
{
    return smoothValY;
}

/// Returns the Z value from the Accelerometer, -4.0f to 4.0f
float Accelerometer::getAccelZ()
{
    return smoothValZ;
}
