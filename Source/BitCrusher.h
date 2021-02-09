/*
  ==============================================================================

    BitCrusher.h
    Created: 9 Feb 2021 10:20:32am
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DryWet.h"
#include "Wavetable.h"

class BitCrusher
{
public:
    BitCrusher();
    ~BitCrusher();
    
    /// Sets up BitCrusher class
    void prepare(float SR);
    
    /// Takes AudioBuffer and crush amount (0 to 1). Returns bitcrushed AudioBuffer. onOff is 0 or 1 from ParameterChoice
    AudioBuffer<float> process(AudioBuffer<float>& bufferIn, float crushAmt, float dryWetVal);
    
private:
    /// Populates Wavetable
    void setWavetables();
    
    AudioBuffer<float> crush(float dryWet);
    
    
    // Instances
    DryWet dryWet;
    SquareWavetable squareWT;
    
    // Member Variables
    float sampleRate;
    
    AudioBuffer<float> sampleBuffer;
};


//=========================================================
//=========================================================
//=========================================================

class HardSquare
{
public:
    AudioBuffer<float> process(AudioBuffer<float>& bufferIn, float dryWetVal);
    
private:
    DryWet dryWet;
};
