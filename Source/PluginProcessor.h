/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

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
    
    // Compressor Params
    std::atomic<float>* compThreshParam;
    std::atomic<float>* compRatioParam;
    std::atomic<float>* compAttackParam;
    std::atomic<float>* compReleaseParam;
    
    
    // DSP Processors
    
    
    // DSP Widgets
    dsp::Gain<float> inGain;
    dsp::NoiseGate<float> noiseGate;
    dsp::Compressor<float> comp;
    dsp::WaveShaper<float> waveShaper;
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BassOnboardAudioProcessor)
};
