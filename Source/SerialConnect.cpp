/*
  ==============================================================================

    SerialConnect.cpp
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

#include <JuceHeader.h>
#include "SerialConnect.h"

//==============================================================================
SerialConnect::SerialConnect() : baud96(9600.0f), baud1152(115200.0f)
{
    // List of serial ports: friendly name & path
    portlist = SerialPort::getSerialPortPaths();
    
    // Open port to Arduino
    macPort = new SerialPort( portlist.getAllValues()[4],
                              SerialPortConfig( baud96, 8, SerialPortConfig::SERIALPORT_PARITY_NONE,
                                                SerialPortConfig::STOPBITS_1, SerialPortConfig::FLOWCONTROL_NONE ) );
    
    if (macPort->exists())
    {
        macOutputStream = new SerialPortOutputStream ( macPort );
        macInputStream  = new SerialPortInputStream  ( macPort );
    }
    
}

SerialConnect::~SerialConnect()
{
    if (macPort->exists())
        delete macPort;
    
    delete macOutputStream;
    delete macInputStream;
}



/**
 Sends bool to Arduino to call for Sensor Value String,
 sends that string to the Sensor Classes for parsing, then
 gets the float values from them.
 Call this in timerCallback(). This is where to call the Sensor Class
 methods that belong in the timerCallback()
 */
void SerialConnect::setValues()
{
    String streamStr;
    
    // If the serial stream exists...
    if (macPort->exists())
    {
        // Tell Arduino to send values
        macOutputStream->writeBool(true);
        
        // Read the stream and write it to streamStr until the stream is exhausted
        while (!macInputStream->isExhausted())
        {
            streamStr = macInputStream->readString();
        }
        
        
        // SENSOR DATA PARSING
        
        // Accelerometer
        accelerometer.setAccelValue ( streamStr );
        
        accelX = accelerometer.getAccelX();
        accelY = accelerometer.getAccelY();
        accelZ = accelerometer.getAccelZ();
        
        // Gyroscope
        gyro.setGyroValue ( streamStr );
        
        gyroX = gyro.getGyroX();
        gyroY = gyro.getGyroY();
        gyroZ = gyro.getGyroZ();
        
        // Distance Meter
        distanceMeter.setDistanceValue( streamStr );
        
        distance = distanceMeter.getDistanceValue();
        
        // TouchScreen
        touchScreen.setTouchScreenCoords( streamStr );
        
        touchX     = touchScreen.getXCoord();
        touchY     = touchScreen.getYCoord();
        touchPress = touchScreen.getPressure();
        
    }
    
    // Tell Arduino not to send values
    macOutputStream->writeBool(false);
}

/// Gets Accelerometer X Axis Value -4.0f to 4.0f
float SerialConnect::getAccelX()
{
    return accelX;
}

/// Gets Accelerometer Y Axis Value -4.0f to 4.0f
float SerialConnect::getAccelY()
{
    return accelY;
}

/// Gets Accelerometer Z Axis Value -4.0f to 4.0f
float SerialConnect::getAccelZ()
{
    return accelZ;
}

/// Gets Distance Meter distance in mm 0.0f to 1500.0f
float SerialConnect::getDistance()
{
    return distance;
}

/// Gets Touchscreen X Coordinate 0.0f to 1024.0f
float SerialConnect::getTouchX()
{
    return touchX;
}

/// Gets Touchscreen Y Coordinate 0.0f to 1024.0f
float SerialConnect::getTouchY()
{
    return touchY;
}

/// Gets Touchscreen Touch Pressure 0.0f to 1024.0f (lower number is greater presure)
float SerialConnect::getTouchPress()
{
    return touchPress;
}
