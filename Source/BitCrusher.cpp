/*
  ==============================================================================

    BitCrusher.cpp
    Created: 9 Feb 2021 10:20:32am
    Author:  Robert Fullum

  ==============================================================================
*/

#include "BitCrusher.h"

//=============== Public ======================================

BitCrusher::BitCrusher() : sampleRate(44100.0f)
{}

BitCrusher::~BitCrusher() {}

/// Sets up BitCrusher class
void BitCrusher::prepare(float SR)
{
    sampleRate = SR;
    setWavetables();
}

/// Takes AudioBuffer and crush amount (0 to 1). Returns bitcrushed AudioBuffer. onOff is 0 or 1 from ParameterChoice
AudioBuffer<float> BitCrusher::process(AudioBuffer<float>& bufferIn, float crushAmt, float dryWetVal)
{
    sampleBuffer = bufferIn;
    
    float crushMapped = jmap   ( crushAmt, 1.0f, sampleRate );
    float crushFreq   = jmap   ( sampleRate / crushMapped, 1.0f, sampleRate, 20.0f, sampleRate);     // in Hz
    
    squareWT.setIncrement ( crushFreq );
    
    return crush( dryWetVal );
}



//================= Private ===================================

/// Populates Wavetable
void BitCrusher::setWavetables()
{
    squareWT.setSampleRate     ( sampleRate );
    squareWT.populateWavetable ();
}


AudioBuffer<float> BitCrusher::crush(float dryWetAmt)
{
    AudioBuffer<float> bufferOut(sampleBuffer);
    
    for (int channel = 0; channel < sampleBuffer.getNumChannels(); channel++)
    {
        for (int sample = 0; sample < sampleBuffer.getNumSamples(); sample++)
        {
            float outVal;
            float crushVal  = squareWT.process();
            float sampleVal = sampleBuffer.getSample ( channel, sample );
            float holdVal   = 0.0f;
            
            if (crushVal >= 0.0f)
            {
                outVal  = sampleVal;
                holdVal = outVal;
            }
            else
            {
                outVal = holdVal;
            }
            
            float mixedSample = dryWet.dryWetMixEqualPower( sampleVal, outVal, dryWetAmt );
            
            bufferOut.addSample( channel, sample, mixedSample );
        }
    }
    
    return bufferOut;
}



//=========================================================
//=========================================================
//=========================================================

//ADD DRY WET
AudioBuffer<float> HardSquare::process(AudioBuffer<float>& bufferIn, float dryWetVal)
{
    AudioBuffer<float> bufferOut(bufferIn);
    
    for (int channel = 0; channel < bufferIn.getNumChannels(); channel++)
    {
        for (int sample = 0; sample < bufferIn.getNumSamples(); sample++)
        {
            float sampleIn = bufferIn.getSample ( channel, sample );
            float sqSample = ( sampleIn >= 0.0f ) ? 1.0f : -1.0f;
            
            bufferOut.setSample( channel, sample, dryWet.dryWetMixEqualPower(sampleIn, sqSample, dryWetVal) );
        }
    }
    
    return bufferOut;
}
