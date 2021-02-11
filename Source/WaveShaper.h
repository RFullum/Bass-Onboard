/*
  ==============================================================================

    WaveShaper.h
    Created: 8 Feb 2021 3:02:31pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DryWet.h"

/// Waveshape Distortion Class
class WaveShaper
{
public:
    WaveShaper();
    ~WaveShaper();
    
    void setSampleRate(float SR);

    /// Returns an audio buffer of the dry/wet mixed Waveshaped signal
    AudioBuffer<float> processWaveshape(AudioBuffer<float>& bufferIn, float wsAmount, float dryWetVal, float onOff);
private:
    // Dry Wet Class Instance
    DryWet dryWet;
    
    // Member Variables
    SmoothedValue<float> wsAmountSmooth;
    SmoothedValue<float> dryWetSmooth;
    
    bool isOn;
    
};
