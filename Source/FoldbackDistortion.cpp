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
    int numChan = bufferIn.getNumChannels();
    int numSamp = bufferIn.getNumSamples();
    
    AudioBuffer<float> bufferOut( numChan, numSamp );
    
    for (int chan = 0; chan < numChan; ++chan )
    {
        for (int sample = 0; sample < numSamp; ++sample )
        {
            float drySamp = bufferIn.getSample         ( chan, sample );
            float wetSamp = std::sin                   ( drySamp * foldbackAmount );
            float outSamp = dryWet.dryWetMixEqualPower ( drySamp, wetSamp, dryWetVal );
            
            bufferOut.setSample( chan, sample, outSamp );
        }
    }
    
    return  bufferOut;
    
}
