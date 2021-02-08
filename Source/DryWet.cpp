/*
  ==============================================================================

    DryWet.cpp
    Created: 26 Dec 2020 11:16:26am
    Author:  Robert Fullum

  ==============================================================================
*/

#include "DryWet.h"

DryWet::DryWet() : drySample(0.0f), wetSample(0.0f), mixFactor(0.0f)
{
}

/**
Takes the dry sample value, wet sample value, and mix value. Returns their mix sample value
*/
float DryWet::dryWetMixLinear(float dryIn, float wetIn, float mixVal)
{
    drySample = dryIn;
    wetSample = wetIn;
    mixFactor = mixVal;

    return dryWetCalculationLinear();
}

float DryWet::dryWetMixEqualPower(float dryIn, float wetIn, float mixVal)
{
    drySample = dryIn;
    wetSample = wetIn;
    mixFactor = mixVal;
    
    return  dryWetCalculationEqualPower();
}

/// Calculates gain of dry and wet samples. Returns mix sample (Linear by sample)
float DryWet::dryWetCalculationLinear()
{
    float wetScaled = wetSample * mixFactor;
    float dryScaled = drySample * (1.0f - mixFactor);
    
    return dryScaled + wetScaled;
}

/// Calculates gain of dry and wet samples. Returns mix sample (Equal Power by sample)
float DryWet::dryWetCalculationEqualPower()
{
    float dryMix = std::sin( 0.5f * MathConstants<float>::pi * (1.0f - mixFactor) ) * drySample;
    float wetMix = std::sin( 0.5f * MathConstants<float>::pi * mixFactor ) * wetSample;
    
    return dryMix + wetMix;
}
