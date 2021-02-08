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
    /// Returns an audio buffer of the dry/wet mixed Waveshaped signal
    AudioBuffer<float> processWaveshape(AudioBuffer<float>& bufferIn, float wsAmount, float dryWetVal);
private:
    // Dry Wet Class Instance
    DryWet dryWet;
    
};
