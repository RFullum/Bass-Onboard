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
    int numChans = bufferIn.getNumChannels();
    int numSamps = bufferIn.getNumSamples();
    
    AudioBuffer<float> bufferOut ( numChans, numSamps );
    
    for (int chan = 0; chan < numChans; ++chan )
    {
        for (int sample = 0; sample < numSamps; ++sample )
        {
            float drySample = bufferIn.getSample                ( chan, sample );
            float wetSample = dsp::FastMathApproximations::tanh ( drySample * wsAmount );
            float outSample = dryWet.dryWetMixEqualPower        ( drySample, wetSample, dryWetVal );
            
            bufferOut.setSample ( chan, sample, outSample );
        }
    }
    
    return bufferOut;
}
