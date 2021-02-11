/*
  ==============================================================================

    FoldbackDistortion.cpp
    Created: 8 Feb 2021 3:50:17pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "FoldbackDistortion.h"

AudioBuffer<float> FoldbackDistortion::processFoldback(AudioBuffer<float>& bufferIn, float foldbackAmount, float dryWetVal)
{
    auto* readL = bufferIn.getReadPointer(0);
    auto* readR = bufferIn.getReadPointer(1);
    auto* writeL = bufferIn.getWritePointer(0);
    auto* writeR = bufferIn.getWritePointer(1);
    
    for (int sample = 0; sample < bufferIn.getNumSamples(); sample++)
    {
        float wetSampleL = dsp::FastMathApproximations::sin( readL[sample] * foldbackAmount );
        float wetSampleR = dsp::FastMathApproximations::sin( readR[sample] * foldbackAmount );
        
        writeL[sample] = dryWet.dryWetMixEqualPower( readL[sample], wetSampleL, dryWetVal );
        writeR[sample] = dryWet.dryWetMixEqualPower( readR[sample], wetSampleR, dryWetVal );
    }
    
    return bufferIn;
}
