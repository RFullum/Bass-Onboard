/*
  ==============================================================================

    DistanceMeter.h
    Created: 28 Feb 2021 4:33:09pm
    Author:  Robert Fullum
    
    Written for Adafruit Time of Flight Distance Sensor VL53L0X ->
    Arduino Nano 33 IoT ->
    Serial Connection via USB Port
 
    Used in conjunction with SerialConnect class, it takes the data from the
    Serial stream, extracts the sub-Strings tagged for Distance (dist), and
    returns the distance as a float in millimeters. The sensor is rated from
    50mm to 1200mm, but can get shorter or further readings depending on
    ambient light and reflectivity of obect being sensed. Readings out of range
    return 0.0f;
 
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


//==============================================================================
/*
*/

class DistanceMeter
{
public:
    DistanceMeter();
    ~DistanceMeter();
    
    /**
    Takes a String in the form of "[TAG][VALUE]\n". Uses the TAG to route the value to the appropriate variable and converts to float
    Call in timerCallback()
    */
    void setDistanceValue(String& stringIn);
    
    /// Returns float of distance in millimeters
    float getDistanceValue();
    
    
private:
    // Member Variables
    float smoothingFactor;
    float smoothedDistVal;
};
