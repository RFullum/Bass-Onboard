/*
  ==============================================================================

    TouchScreen.h
    Created: 28 Feb 2021 5:05:52pm
    Author:  Robert Fullum
 
    Written for Adafruit 3.2" Resistive Touch Screen (part 333) ->
    Adafruit Dual 1.0mm 4 connector FPC Touchscreen Breakout ->
    Arduino Nano 33 IoT ->
    Serial Connection over USB Port
 
    Used in conjunction with SerialConnect class, it takes the data from the
    Serial stream, extracts the sub-Strings tagged for Touch Screen (tsx, tsy, tsz), and
    returns the Touch Screen's X Coordinate, Y Coordinate, and Touch Pressure Value
    as floats between 0.0f and 1024.0f.
 
    Actual touch response tends to range 200.0f to 800.0f.
    Pressure readings are inverse: Lower is more pressure. Adjust as needed.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class TouchScreen
{
public:
    TouchScreen();
    ~TouchScreen();
    
    /**
    Takes a String in the form of "[TAG][VALUE]\n". Uses the TAG to route the value to the appropriate variable and converts to float
    Call in timerCallback()
    */
    void setTouchScreenCoords(String& stringIn);
    
    /// Returns Touchscreen X Coordinate 0.0f to 1024 (useable surface approx 200.0f to 800.0f
    float getXCoord();
    
    /// Returns Touchscreen Y Coordinate 0.0f to 1024 (useable surface approx 200.0f to 800.0f
    float getYCoord();
    
    /// Returns Touchscreen Touch Pressure from 0.0f to 1024.0f (lower is more pressure)
    float getPressure();
    
private:
    float smoothingFactor;
    float smoothedValX;
    float smoothedValY;
    float smoothedValZ;
};
