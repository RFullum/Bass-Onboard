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
    /// Sets up Slider object instances in constructor. sliderInstance is the slider to set up, suffix is textValueSuffix, sliderFillColor is the slider color below the thumb
    void sliderSetup(Slider& sliderInstance, Slider::SliderStyle style, bool showTextBox);
    
    /// Sets up Label for the Slider instances. Takes the labelInstance and the text for setText
    void sliderLabelSetup(Label& labelInstance, String labelText);
    
    /// Sets up an On/Off combo box
    void onOffBoxSetup(ComboBox& boxInstance);
    
    // Sliders
    Slider inGainSlider;
    
    Slider ngThreshSlider;
    Slider ngRatioSlider;
    Slider ngAttackSlider;
    Slider ngReleaseSlider;
    
    Slider compThreshSlider;
    Slider compRatioSlider;
    Slider compAttackSlider;
    Slider compReleaseSlider;
    
    Slider wsAmtSlider;
    Slider wsDryWetSlider;
    
    Slider fbAmtSlider;
    Slider fbDryWetSlider;
    
    Slider bcAmtSlider;
    Slider bcDryWetSlider;
    
    Slider formMorphSlider;
    Slider formDryWetSlider;
    
    Slider delayTimeSlider;
    Slider delayFeedbackSlider;
    Slider delayDryWetSlider;
    
    Slider filtCutoffSlider;
    Slider filtResSlider;
    
    Slider haasWidthSlider;
    
    Slider outGainSlider;
    
    // ComboBox
    ComboBox ngOnOffBox;
    ComboBox compOnOffBox;
    ComboBox wsOnOffBox;
    ComboBox fbOnOffBox;
    ComboBox bcOnOffBox;
    ComboBox formOnOffBox;
    ComboBox delayOnOffBox;
    ComboBox filtTypeBox;
    ComboBox filtPolesBox;
    ComboBox filtOnOffBox;
    ComboBox haasOnOffBox;
    
    // Labels
    Label inLabel;
    Label inGainLabel;
    
    Label ngLabel;
    Label ngThreshLabel;
    Label ngRatioLabel;
    Label ngAttackLabel;
    Label ngReleaseLabel;
    
    Label compLabel;
    Label compThreshLabel;
    Label compRatioLabel;
    Label compAttackLabel;
    Label compReleaseLabel;
    
    Label wsLabel;
    Label wsAmtLabel;
    Label wsDryWetLabel;
    
    Label fbLabel;
    Label fbAmtLabel;
    Label fbDryWetLabel;
    
    Label bcLabel;
    Label bcAmtLabel;
    Label bcDryWetLabel;
    
    Label formLabel;
    Label formMorphLabel;
    Label formDryWetLabel;
    
    Label delayLabel;
    Label delayTimeLabel;
    Label delayFeedbackLabel;
    Label delayDryWetLabel;
    
    Label filtLabel;
    Label filtCutoffLabel;
    Label filtResLabel;
    
    Label haasLabel;
    Label haasWidthLabel;
    
    Label outLabel;
    Label outGainLabel;
    
    // Attachments
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> inGainAttachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> ngThreshAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> ngRatioAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> ngAttackAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> ngReleaseAttachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> compThreshAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> compRatioAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> compAttackAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> compReleaseAttachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> wsAmtAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> wsDryWetAttachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> fbAmtAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> fbDryWetAttachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> bcAmtAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> bcDryWetAttachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> formMorphAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> formDryWetAttachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delayTimeAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delayFeedbackAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delayDryWetAttachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtCutoffAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtResAttachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> haasWidthAttachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> outGainAttachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> ngOnOffAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> compOnOffAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> wsOnOffAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> fbOnOffAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> bcOnOffAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> formOnOffAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> delayOnOffAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filtTypeAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filtPolesAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filtOnOffAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> haasOnOffAttachment;
    
    
    // Serial Connections
    SerialConnect serialConnect;
    
    
    
    BassOnboardAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BassOnboardAudioProcessorEditor)
};
