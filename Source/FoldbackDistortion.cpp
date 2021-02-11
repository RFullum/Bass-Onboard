/*
  ==============================================================================

    FoldbackDistortion.cpp
    Created: 8 Feb 2021 3:50:17pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "FoldbackDistortion.h"

FoldbackDistortion::FoldbackDistortion()  {}
FoldbackDistortion::~FoldbackDistortion() {}

void FoldbackDistortion::setSampleRate(float SR)
{
    foldbackAmtSmooth.reset          ( SR, 0.01f );
    foldbackAmtSmooth.setTargetValue ( 0.0f );
    dryWetSmooth.reset               ( SR, 0.01f );
    dryWetSmooth.setTargetValue      ( 0.0f );
}

AudioBuffer<float> FoldbackDistortion::processFoldback(AudioBuffer<float>& bufferIn, float foldbackAmount, float dryWetVal, float onOff)
{
    if (onOff == 1.0f)
    {
        auto* readL  = bufferIn.getReadPointer  ( 0 );
        auto* readR  = bufferIn.getReadPointer  ( 1 );
        auto* writeL = bufferIn.getWritePointer ( 0 );
        auto* writeR = bufferIn.getWritePointer ( 1 );
        
        foldbackAmtSmooth.setTargetValue ( foldbackAmount );
        dryWetSmooth.setTargetValue      ( dryWetVal );
        
        for (int sample = 0; sample < bufferIn.getNumSamples(); sample++)
        {
            float foldbackAmtSmoothVal = foldbackAmtSmooth.getNextValue();
            
            float wetSampleL = dsp::FastMathApproximations::sin( readL[sample] * foldbackAmtSmoothVal );
            float wetSampleR = dsp::FastMathApproximations::sin( readR[sample] * foldbackAmtSmoothVal );
            
            float dryWetSmoothVal = dryWetSmooth.getNextValue();
            
            writeL[sample] = dryWet.dryWetMixEqualPower( readL[sample], wetSampleL, dryWetSmoothVal );
            writeR[sample] = dryWet.dryWetMixEqualPower( readR[sample], wetSampleR, dryWetSmoothVal );
        }
    }
    
    
    return bufferIn;
}
