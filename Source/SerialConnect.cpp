/*
  ==============================================================================

    SerialConnect.cpp
    Created: 28 Feb 2021 11:11:32am
    Author:  Robert Fullum

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

void SerialConnect::paint (juce::Graphics& g) {}

void SerialConnect::resized() {}

void SerialConnect::setValues()
{
    String streamStr;
    
    // If the serial stream exists...
    if (macPort->exists())
    {
        // Until the stream is exhausted, read the stream and write it to streamStr
        while (!macInputStream->isExhausted())
        {
            streamStr = macInputStream->readString();
        }
        
        //
        // SENSOR DATA PARSING GOES HERE
        //
        
        accelerometer.setAccelValue ( streamStr );
        
        accelX = accelerometer.getAccelX();
        accelY = accelerometer.getAccelY();
        accelZ = accelerometer.getAccelZ();
        
    }
}


float SerialConnect::getAccelX()
{
    return accelX;
}

float SerialConnect::getAccelY()
{
    return accelY;
}

float SerialConnect::getAccelZ()
{
    return accelZ;
}
