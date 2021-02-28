/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SerialConnect.h"

//==============================================================================
/**
*/
class BassOnboardAudioProcessorEditor  : public juce::AudioProcessorEditor, public Timer
{
public:
    BassOnboardAudioProcessorEditor (BassOnboardAudioProcessor&);
    ~BassOnboardAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    SerialConnect serialConnect;
    
    BassOnboardAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BassOnboardAudioProcessorEditor)
};
