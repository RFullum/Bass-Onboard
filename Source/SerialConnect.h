/*
  ==============================================================================

    SerialConnect.h
    Created: 28 Feb 2021 11:11:32am
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "juce_serialport/juce_serialport.h"
#include "Accelerometer.h"
#include "DistanceMeter.h"

//==============================================================================
/*
*/
class SerialConnect  : public juce::Component
{
public:
    SerialConnect();
    ~SerialConnect() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /// Call from timerCallback() to set the parameter values using individual sensor parsing classes
    void setValues();
    
    float getAccelX();
    float getAccelY();
    float getAccelZ();
    float getDistance();

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
    DistanceMeter distanceMeter;
    
    float accelX;
    float accelY;
    float accelZ;
    float distance;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SerialConnect)
};
