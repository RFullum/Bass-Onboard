/*
  ==============================================================================

    TouchScreen.cpp
    Created: 28 Feb 2021 5:05:52pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "TouchScreen.h"


TouchScreen::TouchScreen() : smoothingFactor(0.4f), smoothedValX(0.0f), smoothedValY(0.0f), smoothedValZ(0.0f)
{}

TouchScreen::~TouchScreen() {}


void TouchScreen::setTouchScreenCoords(String &stringIn)
{
    float xCoord = 0.0f;
    float yCoord = 0.0f;
    float zCoord = 0.0f;
    
    String touchXStr;
    String touchYStr;
    String touchZStr;
    
    touchXStr = stringIn.fromFirstOccurrenceOf("tsx", false, true).upToFirstOccurrenceOf("\n", false, true);
    touchYStr = stringIn.fromFirstOccurrenceOf("tsy", false, true).upToFirstOccurrenceOf("\n", false, true);
    touchZStr = stringIn.fromFirstOccurrenceOf("tsz", false, true).upToFirstOccurrenceOf("\n", false, true);
    
    xCoord = touchXStr.getDoubleValue();
    yCoord = touchYStr.getDoubleValue();
    zCoord = touchZStr.getDoubleValue();
    
    smoothedValX += ( xCoord - smoothedValX ) * smoothingFactor;
    smoothedValY += ( yCoord - smoothedValY ) * smoothingFactor;
    smoothedValZ += ( zCoord - smoothedValZ ) * smoothingFactor;
}


float TouchScreen::getXCoord()
{
    return smoothedValX;
}

float TouchScreen::getYCoord()
{
    return smoothedValY;
}

float TouchScreen::getPressure()
{
    return smoothedValZ;
}
