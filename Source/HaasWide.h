/*
  ==============================================================================

    HaasWide.h
    Created: 9 Feb 2021 4:45:23pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
//#include "DelayLine.h"
#include "StereoDelayLine.h"
#include "DryWet.h"

class HaasWide
{
public:
    HaasWide();

    ~HaasWide();
    
    
    AudioBuffer<float> process(AudioBuffer<float>& bufferIn, float width);
    
    void setSampleRate(float SR);
    
private:
    void setDelaySize();
    
    // Member Variables
    float sampleRate;
    float delaySizeSamples;
    
    // Instances
    //DelayLine delayL;
    //DelayLine delayR;
    StereoDelayLine delayLine;
    
    DryWet dryWet;
};
