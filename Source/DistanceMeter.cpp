/*
  ==============================================================================

    DistanceMeter.cpp
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

#include "DistanceMeter.h"

DistanceMeter::DistanceMeter() : smoothingFactor(0.4f), smoothedDistVal(0.0f)
{}

DistanceMeter::~DistanceMeter() {}

/**
Takes a String in the form of "[TAG][VALUE]\n". Uses the TAG to route the value to the appropriate variable and converts to float
Call in timerCallback()
*/
void DistanceMeter::setDistanceValue(String& stringIn)
{
    float dist = 0.0f;
    
    String subString = stringIn.fromFirstOccurrenceOf( "dist", false, true ).upToFirstOccurrenceOf( "\n", false, true );
    dist             = subString.getDoubleValue();
    smoothedDistVal += (dist - smoothedDistVal) * smoothingFactor;
}

/// Returns float of distance in millimeters
float DistanceMeter::getDistanceValue()
{
    return smoothedDistVal;
}
