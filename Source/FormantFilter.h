/*
  ==============================================================================

    FormantFilter.h
    Created: 17 Feb 2021 3:32:50pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DryWet.h"

class FormantFilter
{
public:
    FormantFilter();
    ~FormantFilter();
    
    /// Pass in a ProcessSpec to prepare the filters
    void prepare(dsp::ProcessSpec& PS);
    
    /**
     Takes the AudioBuffer, formant morph value (0.0f to 9.0f), and dry/wet (0.0 to 1.0f)
     and returns the formant filtered AudioBuffer
     */
    AudioBuffer<float> process(AudioBuffer<float>& buf, float morph, float dW);
    
    
private:
    /// Morphs each formant frequency and Q to the next formant in the series.
    void freqMorph(float morph);
    
    /// Morphs each formant frequency and Q to the next formant in the series.
    void freqMapping(float MV, int inc);
    
    /// Sets the Q vals based on the filter frequencies
    void setQVals();
    
    /// Applies filters to audio, sums filters, and blends with dryWet
    AudioBuffer<float> filterAudio(AudioBuffer<float>& bufIn, float dryWet_);
    
    
    // Filter Instances
    dsp::StateVariableTPTFilter<float> filt1;
    dsp::StateVariableTPTFilter<float> filt2;
    dsp::StateVariableTPTFilter<float> filt3;
    
    DryWet dryWet;
    
    // Member Variables
    SmoothedValue<float> morphSmooth1;
    SmoothedValue<float> morphSmooth2;
    SmoothedValue<float> morphSmooth3;
    SmoothedValue<float> qSmooth1;
    SmoothedValue<float> qSmooth2;
    SmoothedValue<float> qSmooth3;
    SmoothedValue<float> dryWetSmooth;
      
    // Formant Frequencies
    float ow[3] = {570.0f, 840.0f,  2410.0f};
    float oo[3] = {300.0f, 870.0f,  2240.0f};
    float uu[3] = {440.0f, 1020.0f, 2240.0f};
    float ah[3] = {730.0f, 1090.0f, 2440.0f};
    float uh[3] = {520.0f, 1190.0f, 2390.0f};
    float er[3] = {490.0f, 1350.0f, 1690.0f};
    float ae[3] = {660.0f, 1720.0f, 2410.0f};
    float eh[3] = {530.0f, 1840.0f, 2480.0f};
    float ih[3] = {390.0f, 1990.0f, 2550.0f};
    float iy[3] = {270.0f, 2290.0f, 3010.0f};
    
    // Q values
    float owQ[3];
    float ooQ[3];
    float uuQ[3];
    float ahQ[3];
    float uhQ[3];
    float erQ[3];
    float aeQ[3];
    float ehQ[3];
    float ihQ[3];
    float iyQ[3];
    
    // Final Values for Filters
    float outFreqs[3] = { 0.0f };
    float outQVals[3] = { 0.0f };
};
