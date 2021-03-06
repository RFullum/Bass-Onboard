/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DryWet.h"
#include "WaveShaper.h"
#include "FoldbackDistortion.h"
#include "BitCrusher.h"
#include "FormantFilter.h"

//==============================================================================
/**
*/
class BassOnboardAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    BassOnboardAudioProcessor();
    ~BassOnboardAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    // APVTS Parameters instalnce
    AudioProcessorValueTreeState parameters;

private:
    
    // Member Variables
    
    // APVTS Members
    
    // Gain Params
    std::atomic<float>* inGainDBParam;
    std::atomic<float>* outGainDBParam;
    
    // Noise Gate Params
    std::atomic<float>* ngThreshParam;
    std::atomic<float>* ngRatioParam;
    std::atomic<float>* ngAttackParam;
    std::atomic<float>* ngReleaseParam;
    std::atomic<float>* ngOnOffParam;
    
    // Compressor Params
    std::atomic<float>* compThreshParam;
    std::atomic<float>* compRatioParam;
    std::atomic<float>* compAttackParam;
    std::atomic<float>* compReleaseParam;
    std::atomic<float>* compOnOffParam;
    
    // Distortion Params
    std::atomic<float>* waveShapeAmountParam;
    std::atomic<float>* waveShapeDryWetParam;
    std::atomic<float>* waveShapeOnOffParam;
    
    std::atomic<float>* foldbackAmountParam;
    std::atomic<float>* foldbackDryWetParam;
    std::atomic<float>* foldbackOnOffParam;
    
    std::atomic<float>* bitcrushAmtParam;
    std::atomic<float>* bitcrushDryWetParam;
    std::atomic<float>* bitcrushOnOffParam;
    
    // Spatial Params
    std::atomic<float>* delayFXTimeParam;
    std::atomic<float>* delayFXFeedbackParam;
    std::atomic<float>* delayFXDryWetParam;
    std::atomic<float>* delayFXOnOffParam;
    SmoothedValue<float> delayFXTimeSmooth;
    SmoothedValue<float> delayFXFeedbackSmooth;
    
    std::atomic<float>* haasWidthParam;
    std::atomic<float>* haasOnOffParam;
    SmoothedValue<float> haasSmooth;
    
    // Filter Params
    std::atomic<float>* svFilterCutoffParam;
    std::atomic<float>* svFilterResonanceParam;
    std::atomic<float>* svFilterTypeParam;
    std::atomic<float>* svFilterPolesParam;
    std::atomic<float>* svFilterOnOffParam;
    SmoothedValue<float> svFilterCutoffSmooth;
    SmoothedValue<float> svFilterResonanceSmooth;
    
    std::atomic<float>* formantMorphParam;
    std::atomic<float>* formantDryWetParam;
    std::atomic<float>* formantOnOffParam;
    
    // DSP Widgets & Processors
    dsp::Gain<float> inGain;
    dsp::Gain<float> outGain;
    dsp::NoiseGate<float> noiseGate;
    dsp::Compressor<float> comp;
    dsp::DelayLine<float, dsp::DelayLineInterpolationTypes::Lagrange3rd> delayFX   { 192000 };
    dsp::DelayLine<float, dsp::DelayLineInterpolationTypes::Lagrange3rd> haasDelay { 192000 };
    dsp::StateVariableTPTFilter<float> svFilter1;
    dsp::StateVariableTPTFilter<float> svFilter2;
    
    
    // Non JUCE Processing Classes
    WaveShaper         waveShaper;
    FoldbackDistortion foldback;
    BitCrusher         bitCrusher;
    DryWet             delayFXDryWet;
    FormantFilter      formant;
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BassOnboardAudioProcessor)
};
