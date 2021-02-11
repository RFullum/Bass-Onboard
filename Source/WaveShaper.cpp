/*
  ==============================================================================

    WaveShaper.cpp
    Created: 8 Feb 2021 3:02:31pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "WaveShaper.h"


WaveShaper::WaveShaper() : isOn(false)
{}

WaveShaper::~WaveShaper() {}

void WaveShaper::setSampleRate(float SR)
{
    wsAmountSmooth.reset          ( SR, 0.01f );
    wsAmountSmooth.setTargetValue ( 0.0f );
    dryWetSmooth.reset            ( SR, 0.01f );
    dryWetSmooth.setTargetValue   ( 0.0f );
}


AudioBuffer<float> WaveShaper::processWaveshape(AudioBuffer<float>& bufferIn, float wsAmount, float dryWetVal, float onOff)
{
    if (onOff == 1.0f)
    {
        int numSamples = bufferIn.getNumSamples();
        
        auto* readL  = bufferIn.getReadPointer  (0);
        auto* readR  = bufferIn.getReadPointer  (1);
        auto* writeL = bufferIn.getWritePointer (0);
        auto* writeR = bufferIn.getWritePointer (1);
        
        wsAmountSmooth.setTargetValue ( wsAmount  );
        dryWetSmooth.setTargetValue   ( dryWetVal );
        
        for (int sample = 0; sample < numSamples; sample++)
        {
            float wsAmtSmoothedVal = wsAmountSmooth.getNextValue();
            
            float wetSampleL = dsp::FastMathApproximations::tanh( readL[sample] * wsAmtSmoothedVal );
            float wetSampleR = dsp::FastMathApproximations::tanh( readR[sample] * wsAmtSmoothedVal );
            
            float dryWetSmoothedVal = dryWetSmooth.getNextValue();
            
            writeL[sample] = dryWet.dryWetMixEqualPower( readL[sample], wetSampleL, dryWetSmoothedVal );
            writeR[sample] = dryWet.dryWetMixEqualPower( readR[sample], wetSampleR, dryWetSmoothedVal );
        }
    }
    

    return bufferIn;
}
