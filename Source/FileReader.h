/*
  ==============================================================================

    FileReader.h
    Created: 14 Feb 2021 2:02:42pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class FileReader
{
public:
    FileReader();
    ~FileReader();
    
    StringArray getDataLines();
    
private:
    File sensorData;
};
