/*
  ==============================================================================

    TouchScreen.h
    Created: 28 Feb 2021 5:05:52pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class TouchScreen
{
public:
    TouchScreen();
    ~TouchScreen();
    
    void setTouchScreenCoords(String& stringIn);
    
    float getXCoord();
    float getYCoord();
    float getPressure();
    
private:
    float smoothingFactor;
    float smoothedValX;
    float smoothedValY;
    float smoothedValZ;
};
