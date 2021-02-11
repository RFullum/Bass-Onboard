/*
  ==============================================================================

    WaveShaper.cpp
    Created: 8 Feb 2021 3:02:31pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "WaveShaper.h"


AudioBuffer<float> WaveShaper::processWaveshape(AudioBuffer<float>& bufferIn, float wsAmount, float dryWetVal)
{
    auto* readL = bufferIn.getReadPointer(0);
    auto* readR = bufferIn.getReadPointer(1);
    auto* writeL = bufferIn.getWritePointer(0);
    auto* writeR = bufferIn.getWritePointer(1);
    
    for (int sample = 0; sample < bufferIn.getNumSamples(); sample++)
    {
        float wetSampleL = dsp::FastMathApproximations::tanh( readL[sample] * wsAmount );
        float wetSampleR = dsp::FastMathApproximations::tanh( readR[sample] * wsAmount );
        
        writeL[sample] = dryWet.dryWetMixEqualPower( readL[sample], wetSampleL, dryWetVal );
        writeR[sample] = dryWet.dryWetMixEqualPower( readR[sample], wetSampleR, dryWetVal );
    }
    
    return bufferIn;
}
