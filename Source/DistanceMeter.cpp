/*
  ==============================================================================

    DistanceMeter.cpp
    Created: 28 Feb 2021 4:33:09pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "DistanceMeter.h"

DistanceMeter::DistanceMeter() : smoothingFactor(0.4f), smoothedDistVal(0.0f)
{}

DistanceMeter::~DistanceMeter() {}


void DistanceMeter::setDistanceValue(String& stringIn)
{
    float dist = 0.0f;
    
    String subString = stringIn.fromFirstOccurrenceOf( "dist", false, true ).upToFirstOccurrenceOf( "\n", false, true );
    
    dist             = subString.getDoubleValue();
    smoothedDistVal += (dist - smoothedDistVal) * smoothingFactor;
}


float DistanceMeter::getDistanceValue()
{
    return smoothedDistVal;
}
