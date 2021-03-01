/*
  ==============================================================================

    TouchScreen.cpp
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

#include "TouchScreen.h"


TouchScreen::TouchScreen() : smoothingFactor(0.4f), smoothedValX(0.0f), smoothedValY(0.0f), smoothedValZ(0.0f)
{}

TouchScreen::~TouchScreen() {}


/**
 Takes a String in the form of "[TAG][VALUE]\n". Uses the TAG to route the value to the appropriate variable and converts to float
 Call in timerCallback()
 */
void TouchScreen::setTouchScreenCoords(String& stringIn)
{
    float xCoord = 0.0f;
    float yCoord = 0.0f;
    float zCoord = 0.0f;
    
    String touchXStr;
    String touchYStr;
    String touchZStr;
    
    // Route substrings using TAG and linebreak
    touchXStr = stringIn.fromFirstOccurrenceOf("tsx", false, true).upToFirstOccurrenceOf("\n", false, true);
    touchYStr = stringIn.fromFirstOccurrenceOf("tsy", false, true).upToFirstOccurrenceOf("\n", false, true);
    touchZStr = stringIn.fromFirstOccurrenceOf("tsz", false, true).upToFirstOccurrenceOf("\n", false, true);
    
    // Convert substring to float
    xCoord = touchXStr.getDoubleValue();
    yCoord = touchYStr.getDoubleValue();
    zCoord = touchZStr.getDoubleValue();
    
    // Smooth values
    smoothedValX += ( xCoord - smoothedValX ) * smoothingFactor;
    smoothedValY += ( yCoord - smoothedValY ) * smoothingFactor;
    smoothedValZ += ( zCoord - smoothedValZ ) * smoothingFactor;
}


/// Returns Touchscreen X Coordinate 0.0f to 1024 (useable surface approx 200.0f to 800.0f
float TouchScreen::getXCoord()
{
    return smoothedValX;
}

/// Returns Touchscreen Y Coordinate 0.0f to 1024 (useable surface approx 200.0f to 800.0f
float TouchScreen::getYCoord()
{
    return smoothedValY;
}

/// Returns Touchscreen Touch Pressure from 0.0f to 1024.0f (lower is more pressure)
float TouchScreen::getPressure()
{
    return smoothedValZ;
}
