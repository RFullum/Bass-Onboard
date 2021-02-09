/*
  ==============================================================================

    HaasWide.cpp
    Created: 9 Feb 2021 4:45:23pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "HaasWide.h"


HaasWide::HaasWide() : sampleRate(44100.0f), delaySizeSamples(0.0f)
{
    setDelaySize();
}

HaasWide::~HaasWide() {}

void HaasWide::setSampleRate(float SR)
{
    sampleRate = SR;
    setDelaySize();
}

/// Takes in AudioBuffer, haas width (-1 to 1 :: Left Delay to Right Delay). Returns widened AudioBuffer
AudioBuffer<float> HaasWide::process(AudioBuffer<float>& bufferIn, float width)
{
    AudioBuffer<float> bufferOut( bufferIn );
    
    // Map width to Delay Amount in samples
    float delayAmt = jmap( std::fabsf( width ), 0.0f, delaySizeSamples );
    
    // Apply delayAmt to L or R delay depending on width direction
    if (width >= 0.0f)
    {
        delayL.setDelayTime ( 0.0f );
        delayR.setDelayTime ( delayAmt );
    }
    else
    {
        delayL.setDelayTime( delayAmt );
        delayR.setDelayTime( 0.0f );
    }
    
    for (int channel = 0; channel < bufferIn.getNumChannels(); channel++)
    {
        for (int sample = 0; sample < bufferIn.getNumSamples(); sample++)
        {
            
            
            if (channel == 0)
            {
                float sampleL = delayL.processDelay( bufferIn.getSample( 0, sample ) );
                
                bufferOut.setSample( channel, sample, sampleL );
            }
            
            if (channel == 1)
            {
                float sampleR = delayR.processDelay( bufferIn.getSample( 1, sample ) );
                
                bufferOut.setSample( channel, sample, sampleR );
            }
        }
    }
    
    
    return bufferOut;
}



void HaasWide::setDelaySize()
{
    // Size in samples = 30ms * samplerate
    delaySizeSamples = 0.03f * sampleRate;
    
    delayL.setBufferSize( delaySizeSamples );
    delayR.setBufferSize( delaySizeSamples );
}
