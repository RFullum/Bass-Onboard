/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BassOnboardAudioProcessorEditor::BassOnboardAudioProcessorEditor (BassOnboardAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);
    
    Timer::startTimerHz(60);
}

BassOnboardAudioProcessorEditor::~BassOnboardAudioProcessorEditor()
{
    Timer::stopTimer();
}

//==============================================================================
void BassOnboardAudioProcessorEditor::paint (juce::Graphics& g) {}

void BassOnboardAudioProcessorEditor::resized() {}


void BassOnboardAudioProcessorEditor::timerCallback()
{
    serialConnect.setValues();
}
