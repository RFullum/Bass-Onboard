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
    setSize (1000, 600);
    
    Timer::startTimerHz(60);
    
    //
    // Sliders Setup
    //
    Slider::SliderStyle genericSlider = Slider::SliderStyle::LinearVertical;
    
    // In Gain
    sliderSetup ( inGainSlider, genericSlider, true );
    
    // Noise Gate
    sliderSetup ( ngThreshSlider,  genericSlider, true );
    sliderSetup ( ngRatioSlider,   genericSlider, true );
    sliderSetup ( ngAttackSlider,  genericSlider, true );
    sliderSetup ( ngReleaseSlider, genericSlider, true );
    
    // Compressor
    sliderSetup ( compThreshSlider,  genericSlider, true );
    sliderSetup ( compRatioSlider,   genericSlider, true );
    sliderSetup ( compAttackSlider,  genericSlider, true );
    sliderSetup ( compReleaseSlider, genericSlider, true );
    
    // Waveshaper
    sliderSetup ( wsAmtSlider,    genericSlider, true );
    sliderSetup ( wsDryWetSlider, genericSlider, true );
    
    // Foldback
    sliderSetup ( fbAmtSlider,    genericSlider, true );
    sliderSetup ( fbDryWetSlider, genericSlider, true );
    
    // Bitcrusher
    sliderSetup ( bcAmtSlider,    genericSlider, true );
    sliderSetup ( bcDryWetSlider, genericSlider, true );
    
    // Formant
    sliderSetup ( formMorphSlider,  genericSlider, true );
    sliderSetup ( formDryWetSlider, genericSlider, true );
    
    // Delay
    sliderSetup ( delayTimeSlider,     genericSlider, true );
    sliderSetup ( delayFeedbackSlider, genericSlider, true );
    sliderSetup ( delayDryWetSlider,   genericSlider, true );
    
    // Filter
    sliderSetup ( filtCutoffSlider, genericSlider, true );
    sliderSetup ( filtResSlider,    genericSlider, true );
    
    // Haas Width
    sliderSetup ( haasWidthSlider, genericSlider, true );
    
    // Out Gain
    sliderSetup ( outGainSlider, genericSlider, true );
    
    //
    // Combo Box Setup
    //
    
    // On/Off boxes
    onOffBoxSetup ( ngOnOffBox    );
    onOffBoxSetup ( compOnOffBox  );
    onOffBoxSetup ( wsOnOffBox    );
    onOffBoxSetup ( fbOnOffBox    );
    onOffBoxSetup ( bcOnOffBox    );
    onOffBoxSetup ( formOnOffBox  );
    onOffBoxSetup ( delayOnOffBox );
    onOffBoxSetup ( filtOnOffBox  );
    onOffBoxSetup ( haasOnOffBox  );
    
    // Filter Type
    filtTypeBox.addItem              ( "LPF", 1 );
    filtTypeBox.addItem              ( "BPF", 2 );
    filtTypeBox.addItem              ( "HPF", 3 );
    filtTypeBox.setJustificationType ( Justification::centred );
    filtTypeBox.setSelectedItemIndex ( 0 );
    addAndMakeVisible                ( filtTypeBox );
    
    // Filter Poles
    filtPolesBox.addItem              ( "-12dB", 1 );
    filtPolesBox.addItem              ( "-24dB", 2 );
    filtPolesBox.setJustificationType ( Justification::centred );
    filtPolesBox.setSelectedItemIndex ( 0 );
    addAndMakeVisible                 ( filtPolesBox );
    
    //
    // Label Setup
    //
    
    // In Gain
    sliderLabelSetup ( inLabel, "In"       );
    sliderLabelSetup ( inGainLabel, "Gain" );
    
    // Noise Gate
    sliderLabelSetup ( ngLabel, "Noise Gate"     );
    sliderLabelSetup ( ngThreshLabel, "Thresh"   );
    sliderLabelSetup ( ngRatioLabel, "Ratio"     );
    sliderLabelSetup ( ngAttackLabel, "Attack"   );
    sliderLabelSetup ( ngReleaseLabel, "Release" );
    
    // Compressor
    sliderLabelSetup ( compLabel, "Compressor"     );
    sliderLabelSetup ( compThreshLabel, "Thresh"   );
    sliderLabelSetup ( compRatioLabel, "Ratio"     );
    sliderLabelSetup ( compAttackLabel, "Attack"   );
    sliderLabelSetup ( compReleaseLabel, "Release" );
    
    // Waveshaper
    sliderLabelSetup ( wsLabel, "Waveshaper"    );
    sliderLabelSetup ( wsAmtLabel, "Amount"     );
    sliderLabelSetup ( wsDryWetLabel, "Dry/Wet" );
    
    // Foldback
    sliderLabelSetup ( fbLabel, "Foldback"      );
    sliderLabelSetup ( fbAmtLabel, "Amount"     );
    sliderLabelSetup ( fbDryWetLabel, "Dry/Wet" );
    
    // Bitcursher
    sliderLabelSetup ( bcLabel, "Bitcrusher"     );
    sliderLabelSetup ( bcAmtLabel, "Amount"     );
    sliderLabelSetup ( bcDryWetLabel, "Dry/Wet" );
    
    // Formant
    sliderLabelSetup ( formLabel, "Formant"       );
    sliderLabelSetup ( formMorphLabel, "Morph"    );
    sliderLabelSetup ( formDryWetLabel, "Dry/Wet" );
    
    // Delay
    sliderLabelSetup ( delayLabel, "Delay"            );
    sliderLabelSetup ( delayTimeLabel, "Time"         );
    sliderLabelSetup ( delayFeedbackLabel, "Feedback" );
    sliderLabelSetup ( delayDryWetLabel, "Dry/Wet"    );
    
    // Filter
    sliderLabelSetup ( filtLabel, "Filter"       );
    sliderLabelSetup ( filtCutoffLabel, "Cutoff" );
    sliderLabelSetup ( filtResLabel, "Resonance" );
    
    // Haas Width
    sliderLabelSetup ( haasLabel, "Width"       );
    sliderLabelSetup ( haasWidthLabel, "Amount" );
    
    // Out Gain
    sliderLabelSetup ( outLabel, "Out"      );
    sliderLabelSetup ( outGainLabel, "Gain" );
    
    //
    // Slider Attachments
    //
    
    // In Gain
    inGainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> ( audioProcessor.parameters, "inGain", inGainSlider );
    
    // Noise Gate
    ngThreshAttachment  = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "ngThresh",  ngThreshSlider  );
    ngRatioAttachment   = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "ngRatio",   ngRatioSlider   );
    ngAttackAttachment  = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "ngAttack",  ngAttackSlider  );
    ngReleaseAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "ngRelease", ngReleaseSlider );
    
    // Compressor
    compThreshAttachment  = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters,"compThresh",  compThreshSlider  );
    compRatioAttachment   = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters,"compRatio",   compRatioSlider   );
    compAttackAttachment  = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters,"compAttack",  compAttackSlider  );
    compReleaseAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters,"compRelease", compReleaseSlider );
    
    // Waveshaper
    wsAmtAttachment    = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "wsAmt",    wsAmtSlider    );
    wsDryWetAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "wsDryWet", wsDryWetSlider );
    
    // Foldback
    fbAmtAttachment    = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "foldbackAmt",    fbAmtSlider    );
    fbDryWetAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "foldbackDryWet", fbDryWetSlider );
    
    // Bitcrusher
    bcAmtAttachment    = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "bitcrushAmt",    bcAmtSlider    );
    bcDryWetAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "bitcrushDryWet", bcDryWetSlider );
    
    // Formant
    formMorphAttachment  = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "formantMorph",  formMorphSlider  );
    formDryWetAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "formantDryWet", formDryWetSlider );
    
    // Delay
    delayTimeAttachment     = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "delayFXTime",   delayTimeSlider     );
    delayFeedbackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "delayFXFdbck",  delayFeedbackSlider );
    delayDryWetAttachment   = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "delayFXDryWet", delayDryWetSlider   );
    
    // Filter
    filtCutoffAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "svFiltCutoff", filtCutoffSlider );
    filtResAttachment    = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "svFiltRes",    filtResSlider    );
    
    // Haas Width
    haasWidthAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "haasWidth", haasWidthSlider );
    
    // Out Gain
    outGainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "outGain", outGainSlider );
    
    //
    // ComboBox Attachments
    //
    ngOnOffAttachment    = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( audioProcessor.parameters, "ngOnOff",       ngOnOffBox    );
    compOnOffAttachment  = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( audioProcessor.parameters, "compOnOff",     compOnOffBox  );
    wsOnOffAttachment    = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( audioProcessor.parameters, "wsOnOff",       wsOnOffBox    );
    fbOnOffAttachment    = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( audioProcessor.parameters, "foldbackOnOff", fbOnOffBox    );
    bcOnOffAttachment    = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( audioProcessor.parameters, "bitcrushOnOff", bcOnOffBox    );
    formOnOffAttachment  = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( audioProcessor.parameters, "formantOnOff",  formOnOffBox  );
    delayOnOffAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( audioProcessor.parameters, "delayFXOnOff",  delayOnOffBox );
    filtTypeAttachment   = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( audioProcessor.parameters, "svFiltType",    filtTypeBox   );
    filtPolesAttachment  = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( audioProcessor.parameters, "svFiltPoles",   filtPolesBox  );
    filtOnOffAttachment  = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( audioProcessor.parameters, "svFiltOnOff",   filtOnOffBox  );
    haasOnOffAttachment  = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( audioProcessor.parameters, "haasOnOff",     haasOnOffBox  );
}

BassOnboardAudioProcessorEditor::~BassOnboardAudioProcessorEditor()
{
    Timer::stopTimer();
}

//==============================================================================
void BassOnboardAudioProcessorEditor::paint (juce::Graphics& g) {}

void BassOnboardAudioProcessorEditor::resized()
{
    // Padding around each effect section to visually separate
    float areaPadding = 10.0f;
    
    // Total area split to top & bottom halves
    Rectangle<int> totalArea  = getLocalBounds();
    Rectangle<int> topHalf    = totalArea.removeFromTop( totalArea.getHeight() * 0.5f );
    Rectangle<int> bottomHalf = totalArea;
    
    // Top & Bottom Halves split into effect sections, width based on number of sliders
    float topSpacing    = topHalf.getWidth() / 15.0f;
    float bottomSpacing = bottomHalf.getWidth() / 11.0f;
    
    Rectangle<int> inArea   = topHalf.removeFromLeft ( topSpacing ).reduced        ( areaPadding );
    Rectangle<int> ngArea   = topHalf.removeFromLeft ( topSpacing * 4.0f ).reduced ( areaPadding );
    Rectangle<int> compArea = topHalf.removeFromLeft ( topSpacing * 4.0f ).reduced ( areaPadding );
    Rectangle<int> wsArea   = topHalf.removeFromLeft ( topSpacing * 2.0f ).reduced ( areaPadding );
    Rectangle<int> fbArea   = topHalf.removeFromLeft ( topSpacing * 2.0f ).reduced ( areaPadding );
    Rectangle<int> bcArea   = topHalf.reduced                                      ( areaPadding );
    
    Rectangle<int> formArea  = bottomHalf.removeFromLeft ( bottomSpacing * 2.0f ).reduced ( areaPadding );
    Rectangle<int> delayArea = bottomHalf.removeFromLeft ( bottomSpacing * 3.0f ).reduced ( areaPadding );
    Rectangle<int> filtArea  = bottomHalf.removeFromLeft ( bottomSpacing * 4.0f ).reduced ( areaPadding );
    Rectangle<int> haasArea  = bottomHalf.removeFromLeft ( bottomSpacing ).reduced        ( areaPadding );
    Rectangle<int> outArea   = bottomHalf.reduced                                         ( areaPadding );
    
    float labelHeight = 50.0f;
    float boxHeight   = 50.0f;
    float boxReduceX  = 75.0f;  // Only works on wider effects section
    float boxReduceY  = 12.0f;
    
    
    // Top Half Areas
    
    // In Gain
    Rectangle<int> inLabelArea     = inArea.removeFromTop    ( labelHeight );
    Rectangle<int> inGainLabelArea = inArea.removeFromTop    ( labelHeight );
    Rectangle<int> inBoxSpacer     = inArea.removeFromBottom ( boxHeight   );
    
    inLabel.setBounds      ( inLabelArea );
    inGainLabel.setBounds  ( inGainLabelArea );
    inGainSlider.setBounds ( inArea );
    
    
    // Noise Gate
    Rectangle<int> ngLabelArea      = ngArea.removeFromTop    ( labelHeight );
    Rectangle<int> ngParamLabelArea = ngArea.removeFromTop    ( labelHeight );
    Rectangle<int> ngBoxArea        = ngArea.removeFromBottom ( boxHeight   );
    
    ngLabel.setBounds    ( ngLabelArea );
    ngOnOffBox.setBounds ( ngBoxArea.reduced( boxReduceX, boxReduceY) );
    
    float ngWidth = ngArea.getWidth() * 0.25f;
    
    Rectangle<int> ngThreshLabelArea  = ngParamLabelArea.removeFromLeft ( ngWidth );
    Rectangle<int> ngRatioLabelArea   = ngParamLabelArea.removeFromLeft ( ngWidth );
    Rectangle<int> ngAttackLabelArea  = ngParamLabelArea.removeFromLeft ( ngWidth );
    Rectangle<int> ngReleaseLabelArea = ngParamLabelArea;
    
    ngThreshLabel.setBounds  ( ngThreshLabelArea  );
    ngRatioLabel.setBounds   ( ngRatioLabelArea   );
    ngAttackLabel.setBounds  ( ngAttackLabelArea  );
    ngReleaseLabel.setBounds ( ngReleaseLabelArea );
    
    Rectangle<int> ngThreshArea  = ngArea.removeFromLeft ( ngWidth );
    Rectangle<int> ngRatioArea   = ngArea.removeFromLeft ( ngWidth );
    Rectangle<int> ngAttackArea  = ngArea.removeFromLeft ( ngWidth );
    Rectangle<int> ngReleaseArea = ngArea;
    
    ngThreshSlider.setBounds  ( ngThreshArea  );
    ngRatioSlider.setBounds   ( ngRatioArea   );
    ngAttackSlider.setBounds  ( ngAttackArea  );
    ngReleaseSlider.setBounds ( ngReleaseArea );
    
    
    // Compressor
    Rectangle<int> compLabelArea      = compArea.removeFromTop    ( labelHeight );
    Rectangle<int> compParamLabelArea = compArea.removeFromTop    ( labelHeight );
    Rectangle<int> compBoxArea        = compArea.removeFromBottom ( boxHeight   );
    
    compLabel.setBounds    ( compLabelArea );
    compOnOffBox.setBounds ( compBoxArea.reduced(boxReduceX, boxReduceY) );
    
    float compWidth = compArea.getWidth() * 0.25f;
    
    Rectangle<int> compThreshLabelArea  = compParamLabelArea.removeFromLeft ( compWidth );
    Rectangle<int> compRatioLabelArea   = compParamLabelArea.removeFromLeft ( compWidth );
    Rectangle<int> compAttackLabelArea  = compParamLabelArea.removeFromLeft ( compWidth );
    Rectangle<int> compReleaseLabelArea = compParamLabelArea;
    
    compThreshLabel.setBounds  ( compThreshLabelArea  );
    compRatioLabel.setBounds   ( compRatioLabelArea   );
    compAttackLabel.setBounds  ( compAttackLabelArea  );
    compReleaseLabel.setBounds ( compReleaseLabelArea );
    
    Rectangle<int> compThreshArea  = compArea.removeFromLeft ( compWidth );
    Rectangle<int> compRatioArea   = compArea.removeFromLeft ( compWidth );
    Rectangle<int> compAttackArea  = compArea.removeFromLeft ( compWidth );
    Rectangle<int> compReleaseArea = compArea;
    
    compThreshSlider.setBounds  ( compThreshArea  );
    compRatioSlider.setBounds   ( compRatioArea   );
    compAttackSlider.setBounds  ( compAttackArea  );
    compReleaseSlider.setBounds ( compReleaseArea );
    
    
    // Waveshaper
    Rectangle<int> wsLabelArea      = wsArea.removeFromTop    ( labelHeight );
    Rectangle<int> wsParamLabelArea = wsArea.removeFromTop    ( labelHeight );
    Rectangle<int> wsBoxArea        = wsArea.removeFromBottom ( boxHeight   );
    
    wsLabel.setBounds    ( wsLabelArea );
    wsOnOffBox.setBounds ( wsBoxArea.reduced(boxReduceY, boxReduceY) );
    
    float wsWidth = wsArea.getWidth() * 0.5f;
    
    Rectangle<int> wsAmtLabelArea    = wsParamLabelArea.removeFromLeft ( wsWidth );
    Rectangle<int> wsDryWetLabelArea = wsParamLabelArea;
    
    wsAmtLabel.setBounds    ( wsAmtLabelArea    );
    wsDryWetLabel.setBounds ( wsDryWetLabelArea );
    
    Rectangle<int> wsAmtArea    = wsArea.removeFromLeft ( wsWidth );
    Rectangle<int> wsDryWetArea = wsArea;
    
    wsAmtSlider.setBounds    ( wsAmtArea    );
    wsDryWetSlider.setBounds ( wsDryWetArea );
    
    
    // Foldback
    Rectangle<int> fbLabelArea      = fbArea.removeFromTop    ( labelHeight );
    Rectangle<int> fbParamLabelArea = fbArea.removeFromTop    ( labelHeight );
    Rectangle<int> fbBoxArea        = fbArea.removeFromBottom ( boxHeight   );
    
    fbLabel.setBounds    ( fbLabelArea );
    fbOnOffBox.setBounds ( fbBoxArea.reduced(boxReduceY, boxReduceY) );
    
    float fbWidth = fbArea.getWidth() * 0.5f;
    
    Rectangle<int> fbAmtLabelArea    = fbParamLabelArea.removeFromLeft ( fbWidth );
    Rectangle<int> fbDryWetLabelArea = fbParamLabelArea;
    
    fbAmtLabel.setBounds    ( fbAmtLabelArea    );
    fbDryWetLabel.setBounds ( fbDryWetLabelArea );
    
    Rectangle<int> fbAmtArea    = fbArea.removeFromLeft ( fbWidth );
    Rectangle<int> fbDryWetArea = fbArea;
    
    fbAmtSlider.setBounds    ( fbAmtArea    );
    fbDryWetSlider.setBounds ( fbDryWetArea );
    
    
    // Bitcrusher
    Rectangle<int> bcLabelArea      = bcArea.removeFromTop    ( labelHeight );
    Rectangle<int> bcParamLabelArea = bcArea.removeFromTop    ( labelHeight );
    Rectangle<int> bcBoxArea        = bcArea.removeFromBottom ( boxHeight   );
    
    bcLabel.setBounds    ( bcLabelArea );
    bcOnOffBox.setBounds ( bcBoxArea.reduced(boxReduceY, boxReduceY)   );
    
    float bcWidth = bcArea.getWidth() * 0.5f;
    
    Rectangle<int> bcAmtLabelArea    = bcParamLabelArea.removeFromLeft ( bcWidth );
    Rectangle<int> bcDryWetLabelArea = bcParamLabelArea;
    
    bcAmtLabel.setBounds    ( bcAmtLabelArea    );
    bcDryWetLabel.setBounds ( bcDryWetLabelArea );
    
    Rectangle<int> bcAmtArea    = bcArea.removeFromLeft ( bcWidth );
    Rectangle<int> bcDryWetArea = bcArea;
    
    bcAmtSlider.setBounds    ( bcAmtArea    );
    bcDryWetSlider.setBounds ( bcDryWetArea );
    
    
    // Bottom Half Areas
    
    // Formant
    Rectangle<int> formLabelArea      = formArea.removeFromTop    ( labelHeight );
    Rectangle<int> formParamLabelArea = formArea.removeFromTop    ( labelHeight );
    Rectangle<int> formBoxArea        = formArea.removeFromBottom ( boxHeight   );
    
    formLabel.setBounds    ( formLabelArea );
    formOnOffBox.setBounds ( formBoxArea.reduced(boxReduceY, boxReduceY) );
    
    float formWidth = formArea.getWidth() * 0.5f;
    
    Rectangle<int> formMorphLabelArea  = formParamLabelArea.removeFromLeft ( formWidth );
    Rectangle<int> formDryWetLabelArea = formParamLabelArea;
    
    formMorphLabel.setBounds  ( formMorphLabelArea  );
    formDryWetLabel.setBounds ( formDryWetLabelArea );
    
    Rectangle<int> formMorphArea  = formArea.removeFromLeft ( formWidth );
    Rectangle<int> formDryWetArea = formArea;
    
    formMorphSlider.setBounds  ( formMorphArea  );
    formDryWetSlider.setBounds ( formDryWetArea );
    
    
    // Delay
    Rectangle<int> delayLabelArea      = delayArea.removeFromTop    ( labelHeight );
    Rectangle<int> delayParamLabelArea = delayArea.removeFromTop    ( labelHeight );
    Rectangle<int> delayBoxArea        = delayArea.removeFromBottom ( boxHeight   );
    
    delayLabel.setBounds    ( delayLabelArea );
    delayOnOffBox.setBounds ( delayBoxArea.reduced(boxReduceX, boxReduceY) );
    
    float delayWidth = delayArea.getWidth() * 0.33f;
    
    Rectangle<int> delayTimeLabelArea   = delayParamLabelArea.removeFromLeft ( delayWidth );
    Rectangle<int> delayFdbkLabelArea   = delayParamLabelArea.removeFromLeft ( delayWidth );
    Rectangle<int> delayDryWetLabelArea = delayParamLabelArea;
    
    delayTimeLabel.setBounds     ( delayTimeLabelArea  );
    delayFeedbackLabel.setBounds ( delayFdbkLabelArea  );
    delayDryWetLabel.setBounds   (delayDryWetLabelArea );
    
    Rectangle<int> delayTimeArea   = delayArea.removeFromLeft ( delayWidth );
    Rectangle<int> delayFdbkArea   = delayArea.removeFromLeft ( delayWidth );
    Rectangle<int> delayDryWetArea = delayArea;
    
    delayTimeSlider.setBounds     ( delayTimeArea   );
    delayFeedbackSlider.setBounds ( delayFdbkArea   );
    delayDryWetSlider.setBounds   ( delayDryWetArea );
    
    
    // Filter
    Rectangle<int> filtLabelArea      = filtArea.removeFromTop    ( labelHeight );
    Rectangle<int> filtParamLabelArea = filtArea.removeFromTop    ( labelHeight );
    Rectangle<int> filtBoxArea        = filtArea.removeFromBottom ( boxHeight   );
    
    filtLabel.setBounds    ( filtLabelArea );
    filtOnOffBox.setBounds ( filtBoxArea.reduced(boxReduceX, boxReduceY) );
    
    float filtWidth = filtArea.getWidth() * 0.25f;
    
    Rectangle<int> filtCutoffLabelArea = filtParamLabelArea.removeFromLeft  ( filtWidth );
    Rectangle<int> filtParamSpacerArea = filtParamLabelArea.removeFromRight ( filtWidth * 2.0f );
    Rectangle<int> filtResLabelArea    = filtParamLabelArea;
    
    filtCutoffLabel.setBounds ( filtCutoffLabelArea );
    filtResLabel.setBounds    ( filtResLabelArea    );
    
    Rectangle<int> filtCutoffArea = filtArea.removeFromLeft ( filtWidth );
    Rectangle<int> filtResArea    = filtArea.removeFromLeft ( filtWidth );
    Rectangle<int> filtTypeArea   = filtArea.removeFromTop  ( filtArea.getHeight() * 0.5f );
    Rectangle<int> filtPoleArea   = filtArea;
    
    filtCutoffSlider.setBounds ( filtCutoffArea );
    filtResSlider.setBounds    ( filtResArea    );
    filtTypeBox.setBounds      ( filtTypeArea.reduced(boxReduceY, boxReduceY) );
    filtPolesBox.setBounds     ( filtPoleArea.reduced(boxReduceY, boxReduceY) );
    
    
    // Haas Width
    Rectangle<int> haasLabelArea      = haasArea.removeFromTop    ( labelHeight );
    Rectangle<int> haasParamLabelArea = haasArea.removeFromTop    ( labelHeight );
    Rectangle<int> haasBoxArea        = haasArea.removeFromBottom ( boxHeight   );
    
    haasLabel.setBounds       ( haasLabelArea );
    haasWidthLabel.setBounds  ( haasParamLabelArea );
    haasOnOffBox.setBounds    ( haasBoxArea.reduced( 0.0f, boxReduceY) );
    haasWidthSlider.setBounds ( haasArea );
    
    
    // Out Gain
    Rectangle<int> outLabelArea      = outArea.removeFromTop    ( labelHeight );
    Rectangle<int> outParamLabelArea = outArea.removeFromTop    ( labelHeight );
    Rectangle<int> outBoxSpacer      = outArea.removeFromBottom ( boxHeight   );
    
    outLabel.setBounds      ( outLabelArea      );
    outGainLabel.setBounds  ( outParamLabelArea );
    outGainSlider.setBounds ( outArea           );
    
    
    
}



void BassOnboardAudioProcessorEditor::timerCallback()
{
    // Calls Arduinos, gets the input stream, and sets the values in the Sensors' classess
    serialConnect.setValues();
    
    // Gets values from Acceleromter axes and updates the Slider values with them
    delayTimeSlider.setValue     ( serialConnect.getAccelX() );
    delayFeedbackSlider.setValue ( serialConnect.getAccelY() );
    delayDryWetSlider.setValue   ( serialConnect.getAccelZ() );
    
}


/// Sets up Slider object instances in constructor. sliderInstance is the slider to set up, suffix is textValueSuffix, sliderFillColor is the slider color below the thumb
void BassOnboardAudioProcessorEditor::sliderSetup(Slider &sliderInstance, Slider::SliderStyle style, bool showTextBox)
{
    sliderInstance.setSliderStyle(style);
        
    // If slider has a textbox, draw it, otherwise, don't
    if (showTextBox)
    {
        sliderInstance.setTextBoxStyle ( Slider::TextBoxBelow, false, 50, 20 );
        sliderInstance.setColour       ( Slider::textBoxOutlineColourId, Colour( (uint8)0, (uint8)0, (uint8)0, (uint8)0 ) );
        sliderInstance.setColour       ( Slider::textBoxTextColourId, Colours::darkblue );
    }
    else
    {
        sliderInstance.setTextBoxStyle( Slider::NoTextBox, false, 0, 0 );
    }
    
    addAndMakeVisible(sliderInstance);
}


/// Sets up Label for the Slider instances. Takes the labelInstance and the text for setText
void BassOnboardAudioProcessorEditor::sliderLabelSetup(Label &labelInstance, String labelText)
{
    labelInstance.setText              ( labelText, dontSendNotification );
    labelInstance.setJustificationType ( Justification::centred );
    addAndMakeVisible                  ( labelInstance );
}


/// Sets up an On/Off combo box
void BassOnboardAudioProcessorEditor::onOffBoxSetup(ComboBox &boxInstance)
{
    boxInstance.addItem              ( "Off", 1 );
    boxInstance.addItem              ( "On",  2 );
    boxInstance.setJustificationType ( Justification::centred );
    boxInstance.setSelectedItemIndex ( 0 );
    addAndMakeVisible                ( boxInstance );
}
