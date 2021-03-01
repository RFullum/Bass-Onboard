/*
  ==============================================================================

    SerialConnect.h
    Created: 28 Feb 2021 11:11:32am
    Author:  Robert Fullum

    Uses juce_serialport library https://github.com/cpr2323/juce_serialport
 
    Creates a Serial Port Connection, and corresponding Input and Output Streams
    It sends the Arduino a True to call the sensor values, gets the sensor values
    as a String from the Input Stream, and sends that string to the Sensor
    Classes (Accelerometer, Distance, TouchScreen, etc.)
    
    It then calls the parsed float values from the Sensor Classes and provides
    them via getter methods.
 
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "juce_serialport/juce_serialport.h"
#include "Accelerometer.h"
#include "DistanceMeter.h"
#include "TouchScreen.h"

//==============================================================================
/*
*/
class SerialConnect
{
public:
    SerialConnect();
    ~SerialConnect();

    /**
    Sends bool to Arduino to call for Sensor Value String,
    sends that string to the Sensor Classes for parsing, then
    gets the float values from them.
    Call this in timerCallback(). This is where to call the Sensor Class
    methods that belong in the timerCallback()
    */
    void setValues();
    
    /// Gets Accelerometer X Axis Value -4.0f to 4.0f
    float getAccelX();
    
    /// Gets Accelerometer Y Axis Value -4.0f to 4.0f
    float getAccelY();
    
    /// Gets Accelerometer Z Axis Value -4.0f to 4.0f
    float getAccelZ();
    
    /// Gets Distance Meter distance in mm 0.0f to 1500.0f
    float getDistance();
    
    /// Gets Touchscreen X Coordinate 0.0f to 1024.0f
    float getTouchX();
    
    /// Gets Touchscreen Y Coordinate 0.0f to 1024.0f
    float getTouchY();
    
    /// Gets Touchscreen Touch Pressure 0.0f to 1024.0f (lower number is greater presure)
    float getTouchPress();

private:
    // Member Variables
    float baud96;
    float baud1152;
    
    // Serial port connections
    StringPairArray portlist;
    
    SerialPort* macPort;
    
    SerialPortOutputStream* macOutputStream;
    SerialPortInputStream*  macInputStream;
    
    // Sensor Instances
    Accelerometer accelerometer;
    Gyroscope     gyro;
    DistanceMeter distanceMeter;
    TouchScreen   touchScreen;
    
    // Private Member Variables
    float accelX;
    float accelY;
    float accelZ;
    float gyroX;
    float gyroY;
    float gyroZ;
    float distance;
    float touchX;
    float touchY;
    float touchPress;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SerialConnect)
};
