/*
  ==============================================================================

    FileReader.cpp
    Created: 14 Feb 2021 2:02:42pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "FileReader.h"


FileReader::FileReader() : sensorData("/Users/Prophetnoise/JUCE/Projects/Bass Onboard/Source/DataFile/sensorData.txt")
{}

FileReader::~FileReader() {}

StringArray FileReader::getDataLines()
{
    StringArray dataLines;
    
    sensorData.readLines(dataLines);
    
    return dataLines;
}
