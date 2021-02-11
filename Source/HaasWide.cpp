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
    // Set width mapped to size in samples
    delayLine.setDelayTime( jmap( width, 0.0f, delaySizeSamples ), 0.0f );
    
    auto* readL  = bufferIn.getReadPointer  (0);
    auto* readR  = bufferIn.getReadPointer  (1);
    auto* writeL = bufferIn.getWritePointer (0);
    auto* writeR = bufferIn.getWritePointer (1);
    
    for (int sample = 0; sample < bufferIn.getNumSamples(); sample++)
    {
        delayLine.processDelay( readL[sample], readR[sample] );
        
        writeL[sample] = delayLine.getDelayOutputLeft  ();
        writeR[sample] = delayLine.getDelayOutputRight ();
    }
    
    return bufferIn;
}



void HaasWide::setDelaySize()
{
    // Size in samples = 30ms * samplerate
    delaySizeSamples = 0.5f * sampleRate;
    
    delayLine.setBufferSize( delaySizeSamples );
}
