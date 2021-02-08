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
    /// Returns an audio buffer of the dry/wet mixed Foldback signal
    AudioBuffer<float> processFoldback(AudioBuffer<float>& bufferIn, float foldbackAmount, float dryWetVal);
    
private:
    // DryWet class instance
    DryWet dryWet;
};
