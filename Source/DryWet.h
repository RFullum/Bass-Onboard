/*
  ==============================================================================

    DryWet.h
    Created: 29 Apr 2020 10:13:04pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/// Dry/Wet Control
class DryWet
{
public:
    DryWet();
    
    /**
     Takes the dry sample value, wet sample value, and mix value. Returns their mix sample value
     */
    float dryWetMixLinear(float dryIn, float wetIn, float mixVal);
    
    /**
    Takes the dry sample value, wet sample value, and mix value. Returns their mix sample value
    */
    float dryWetMixEqualPower(float dryIn, float wetIn, float mixVal);
    
private:
    /// Calculates gain of dry and wet samples. Returns mix sample (Linear by sample)
    float dryWetCalculationLinear();
    
    /// Calculates gain of dry and wet samples. Returns mix sample (Equal Power by sample)
    float dryWetCalculationEqualPower();
    

    // member variables
    float drySample;
    float wetSample;
    float mixFactor;
    
};
