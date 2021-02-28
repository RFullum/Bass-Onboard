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




//==============================================================================
//==============================================================================
//==============================================================================



Gyroscope::Gyroscope() : smoothingFactor(0.4f), smoothGyroX(0.0f), smoothGyroY(0.0f), smoothGyroZ(0.0f)
{}

Gyroscope::~Gyroscope() {}


void Gyroscope::setGyroValue(String &stringIn)
{
    float gyroX = 0.0f;
    float gyroY = 0.0f;
    float gyroZ = 0.0f;
    
    String gyroXStr;
    String gyroYStr;
    String gyroZStr;
    
    gyroXStr     = stringIn.fromFirstOccurrenceOf ( "gx", false, true ).upToFirstOccurrenceOf( "\n", false, true );
    gyroX        = gyroXStr.getDoubleValue();
    smoothGyroX += ( gyroX - smoothGyroX ) * smoothingFactor;
    
    gyroYStr     = stringIn.fromFirstOccurrenceOf( "gy", true, false ).upToFirstOccurrenceOf( "\n", false, true );
    gyroY        = gyroYStr.getDoubleValue();
    smoothGyroY += ( gyroY - smoothGyroY ) * smoothingFactor;
    
    gyroZStr     = stringIn.fromFirstOccurrenceOf( "gz", false, true ).upToFirstOccurrenceOf( "\n", false, true );
    gyroZ        = gyroZStr.getDoubleValue();
    smoothGyroZ += ( gyroZ - smoothGyroZ ) * smoothingFactor;
    
}

float Gyroscope::getGyroX()
{
    return smoothGyroX;
}

float Gyroscope::getGyroY()
{
    return smoothGyroY;
}

float Gyroscope::getGyroZ()
{
    return smoothGyroZ;
}
