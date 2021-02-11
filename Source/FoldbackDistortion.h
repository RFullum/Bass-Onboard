/*
  ==============================================================================

    FoldbackDistortion.h
    Created: 8 Feb 2021 3:50:17pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DryWet.h"

class FoldbackDistortion
{
public:
    FoldbackDistortion();
    ~FoldbackDistortion();
    
    void setSampleRate(float SR);
    
    /// Returns an audio buffer of the dry/wet mixed Foldback signal
    AudioBuffer<float> processFoldback(AudioBuffer<float>& bufferIn, float foldbackAmount, float dryWetVal, float onOff);
    
private:
    // DryWet class instance
    DryWet dryWet;
    
    // Member Variables
    SmoothedValue<float> foldbackAmtSmooth;
    SmoothedValue<float> dryWetSmooth;
};
