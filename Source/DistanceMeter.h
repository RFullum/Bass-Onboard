/*
  ==============================================================================

    DistanceMeter.h
    Created: 28 Feb 2021 4:33:09pm
    Author:  Robert Fullum

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
    
    /// Called in timerCallback() to read Distance Sensor values
    void setDistanceValue(String& stringIn);
    
    float getDistanceValue();
    
    
private:
    // Member Variables
    float smoothingFactor;
    float smoothedDistVal;
};
