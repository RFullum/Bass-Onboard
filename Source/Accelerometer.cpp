/*
  ==============================================================================

    Accelerometer.cpp
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

#include <JuceHeader.h>
#include "Accelerometer.h"

//==============================================================================
Accelerometer::Accelerometer() : smoothingFactor(0.4f), smoothValX(0.0f), smoothValY(0.0f), smoothValZ(0.0f)
{}

Accelerometer::~Accelerometer() {}


/**
Takes a String in the form of "[TAG][VALUE]\n". Uses the TAG to route the value to the appropriate variable and converts to float
Call in timerCallback()
*/
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


/**
Takes a String in the form of "[TAG][VALUE]\n". Uses the TAG to route the value to the appropriate variable and converts to float
Call in timerCallback()
*/
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

/// Returns Gyroscope's X value -2000.0f to 2000.0f
float Gyroscope::getGyroX()
{
    return smoothGyroX;
}

/// Returns Gyroscope's Y value -2000.0f to 2000.0f
float Gyroscope::getGyroY()
{
    return smoothGyroY;
}

/// Returns Gyroscope's Z value -2000.0f to 2000.0f
float Gyroscope::getGyroZ()
{
    return smoothGyroZ;
}
