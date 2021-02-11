/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BassOnboardAudioProcessor::BassOnboardAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif

//
// ParameterFloats:
// id, description, min, max, default
// ~OR~
// id, description, normalisableRange(min, max, increment, skew, symmetric),
//                 default, param label, param category, string from value, string to value
//
// ParameterChoices:
// id, descript, choices (StringArray), default index of StringArray
//
parameters(*this, nullptr, "ParameterTree", {
    // Gain params
    std::make_unique<AudioParameterFloat>("inGain", "Input Gain",
                                          NormalisableRange<float>(-100.0f, 12.0f, 0.01f, 2.0f, true), 0.0f, "dB" ),
    std::make_unique<AudioParameterFloat>("outGain", "Output Gain",
                                          NormalisableRange<float>(-100.0f, 12.0f, 0.01f, 2.0f, true), 0.0f, "dB" ),
    // Noise Gate Params
    std::make_unique<AudioParameterFloat>("ngThresh", "Noise Gate Threshold",
                                          NormalisableRange<float>(-100.0f, 12.0f, 0.01f, 2.0f, false), -96.0f, "dB" ),
    std::make_unique<AudioParameterFloat>("ngRatio", "Noise Gate Ratio",
                                          NormalisableRange<float>(1.0f, 25.0f, 0.1f, 0.25f, false), 25.0f, "1:x" ),
    std::make_unique<AudioParameterFloat>("ngAttack", "Noise Gate Attack",
                                          NormalisableRange<float>(0.1f, 10.0f, 0.1f, 1.0f, false), 0.5f, "ms" ),
    std::make_unique<AudioParameterFloat>("ngRelease", "Noise Gate Release",
                                          NormalisableRange<float>(0.1f, 10.0f, 0.1f, 1.0f, false), 2.0f, "ms" ),
    std::make_unique<AudioParameterChoice>("ngOnOff", "Noise Gate On/Off", StringArray( {"Off", "On"} ), 0 ),
    
    // Compressor Params
    std::make_unique<AudioParameterFloat>("compThresh", "Compressor Threshold",
                                          NormalisableRange<float>(-100.0f, 12.0f, 0.01f, 2.0f, false), 0.0f, "dB" ),
    std::make_unique<AudioParameterFloat>("compRatio", "Compressor Ratio",
                                          NormalisableRange<float>(1.0f, 25.0f, 0.1f, 0.25f, false), 1.0f, "x:1" ),
    std::make_unique<AudioParameterFloat>("compAttack", "Compressor Attack",
                                          NormalisableRange<float>(0.1f, 10.0f, 0.1f, 1.0f, false), 0.5f, "ms" ),
    std::make_unique<AudioParameterFloat>("compRelease", "Compressor Release",
                                          NormalisableRange<float>(0.1f, 10.0f, 0.1f, 1.0f, false), 2.0f, "ms" ),
    std::make_unique<AudioParameterChoice>("compOnOff", "Compressor On/Off", StringArray( {"Off", "On"} ), 0 ),
    
    // Distortion Params
    std::make_unique<AudioParameterFloat>("wsAmt", "Waveshape Amount",
                                          NormalisableRange<float>(1.0f, 200.0f, 0.01f, 1.0f, false), 1.0f, "" ),
    std::make_unique<AudioParameterFloat>("wsDryWet", "Waveshape Dry/Wet",
                                          NormalisableRange<float>(0.0f, 1.0f, 0.01f, 1.0f, false), 0.0f, "" ),
    std::make_unique<AudioParameterChoice>("wsOnOff", "Waveshape On/Off", StringArray( {"Off", "On"} ), 0 ),
    
    std::make_unique<AudioParameterFloat>("foldbackAmt", "Foldback Amount",
                                          NormalisableRange<float>(1.0f, 200.0f, 0.01f, 0.325f, false), 1.0f, "" ),
    std::make_unique<AudioParameterFloat>("foldbackDryWet", "Foldback Dry/Wet",
                                          NormalisableRange<float>(0.0f, 1.0f, 0.01f, 1.0f, false), 0.0f, "" ),
    std::make_unique<AudioParameterChoice>("foldbackOnOff", "Foldback On/Off", StringArray( {"Off", "On"} ), 0 ),
    
    std::make_unique<AudioParameterFloat>("bitcrushAmt", "Bitcrush Amount",
                                          NormalisableRange<float>(0.0f, 1.0f, 0.01f, 0.325f, false), 1.0f, "" ),
    std::make_unique<AudioParameterFloat>("bitcrushDryWet", "Bitcrush Dry/Wet",
                                          NormalisableRange<float>(0.0f, 1.0f, 0.01f, 1.0f, false), 0.0f, "" ),
    std::make_unique<AudioParameterChoice>("bitcrushOnOf", "Bitcrush On/Off", StringArray( {"Off", "On"} ), 0 ),
    
    // Spatial Params
    std::make_unique<AudioParameterFloat>("haasWidth", "Width Amount",
                                          NormalisableRange<float>(0.0f, 1.0f, 0.01f, 1.0f, false), 0.0f, "" ),
    std::make_unique<AudioParameterChoice>("haasOnOff", "Width On/Off", StringArray( {"Off", "On"} ), 0 )
    
}),

waveshapeOn(false)

// Constructor
{
    // Gain Params
    inGainDBParam  = parameters.getRawParameterValue ( "inGain"  );
    outGainDBParam = parameters.getRawParameterValue ( "outGain" );
    
    // Noise Gate Params
    ngThreshParam  = parameters.getRawParameterValue ( "ngThresh"  );
    ngRatioParam   = parameters.getRawParameterValue ( "ngRatio"   );
    ngAttackParam  = parameters.getRawParameterValue ( "ngAttack"  );
    ngReleaseParam = parameters.getRawParameterValue ( "ngRelease" );
    ngOnOffParam   = parameters.getRawParameterValue ( "ngOnOff"   );
    
    // Compressor Params
    compThreshParam  = parameters.getRawParameterValue ( "compThresh"  );
    compRatioParam   = parameters.getRawParameterValue ( "compRatio"   );
    compAttackParam  = parameters.getRawParameterValue ( "compAttack"  );
    compReleaseParam = parameters.getRawParameterValue ( "compRelease" );
    compOnOffParam   = parameters.getRawParameterValue ( "compOnOff"   );
    
    // Distortion Params
    waveShapeAmountParam = parameters.getRawParameterValue ( "wsAmt"    );
    waveShapeDryWetParam = parameters.getRawParameterValue ( "wsDryWet" );
    waveShapeOnOffParam  = parameters.getRawParameterValue ( "wsOnOff"  );
    
    foldbackAmountParam = parameters.getRawParameterValue ( "foldbackAmt"    );
    foldbackDryWetParam = parameters.getRawParameterValue ( "foldbackDryWet" );
    foldbackOnOffParam  = parameters.getRawParameterValue ( "foldbackOnOff"  );
    
    bitcrushAmtParam    = parameters.getRawParameterValue ( "bitcrushAmt"    );
    bitcrushDryWetParam = parameters.getRawParameterValue ( "bitcrushDryWet" );
    bitcrushOnOffParam  = parameters.getRawParameterValue ( "bitcrushOnOf"   );
    
    // Spatial Params
    haasWidthParam = parameters.getRawParameterValue ( "haasWidth" );
    haasOnOffParam = parameters.getRawParameterValue ( "haasOnOff" );
}

BassOnboardAudioProcessor::~BassOnboardAudioProcessor()
{
}

//==============================================================================
const juce::String BassOnboardAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BassOnboardAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BassOnboardAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BassOnboardAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BassOnboardAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BassOnboardAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BassOnboardAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BassOnboardAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BassOnboardAudioProcessor::getProgramName (int index)
{
    return {};
}

void BassOnboardAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BassOnboardAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Process Spec
    dsp::ProcessSpec spec;
    
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate       = sampleRate;
    
    
    // DSP Widgets
    // Gains
    inGain.prepare                ( spec   );
    inGain.reset                  (        );
    inGain.setRampDurationSeconds ( 0.01f );
    
    outGain.prepare                ( spec   );
    outGain.reset                  (        );
    outGain.setRampDurationSeconds ( 0.01f );
    
    // Dynamics
    noiseGate.prepare ( spec );
    noiseGate.reset   ();
    
    comp.prepare ( spec );
    comp.reset   ();
    
    // Spatial
    haasDelay.prepare ( spec );
    haasDelay.reset   ();
    
    std::fill(lastDelayOutput.begin(), lastDelayOutput.end(), 0.0f);
    
    // Non Juce Processing
    waveShaper.setSampleRate ( sampleRate );
    foldback.setSampleRate   ( sampleRate );
    bitCrusher.prepare       ( sampleRate );
    
    
    // Value smoothing
    haasSmooth.reset          ( sampleRate, 0.01f );
    haasSmooth.setTargetValue ( 0.0f );
    
}

void BassOnboardAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BassOnboardAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BassOnboardAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // Audio input to buffer
    int numSamples     = buffer.getNumSamples();
    auto* leftChannel  = buffer.getWritePointer(0);
    auto* rightChannel = buffer.getWritePointer(1);
    
    //
    //*** TEMP MONO FOR TESTING *** Mirror right channel bass input on left channel as well ********************************
    //
    for (int i = 0; i < numSamples; i++)
        leftChannel[i] = rightChannel[i];
    
    // Create the AudioBlock for DSP widgets
    dsp::AudioBlock<float> sampleBlock ( buffer );
    
    // Apply Input Gain
    inGain.setGainDecibels ( *inGainDBParam );
    inGain.process         ( dsp::ProcessContextReplacing<float>(sampleBlock) );
    
    // Apply Noise Gate
    if (*ngOnOffParam)
    {
        noiseGate.setThreshold ( *ngThreshParam  );
        noiseGate.setRatio     ( *ngRatioParam   );
        noiseGate.setAttack    ( *ngAttackParam  );
        noiseGate.setRelease   ( *ngReleaseParam );
        noiseGate.process      ( dsp::ProcessContextReplacing<float>(sampleBlock) );
    }
    
    
    
    // Apply Compressor
    if (*compOnOffParam)
    {
        comp.setThreshold ( *compThreshParam );
        comp.setRatio     ( *compRatioParam  );
        comp.setAttack    ( *compAttackParam );
        comp.setRatio     ( *compRatioParam  );
        comp.process      ( dsp::ProcessContextReplacing<float>(sampleBlock) );
    }
    else
    
    int bufferChannels = buffer.getNumChannels();
    int bufferSamples  = buffer.getNumSamples();
    
    
    // Apply Effects
    
    // Create Effects buffer
    AudioBuffer<float> effectsBuffer;
    effectsBuffer.clear();
    effectsBuffer.makeCopyOf( buffer );
    
    
    // Distortions
    effectsBuffer = waveShaper.processWaveshape ( effectsBuffer, *waveShapeAmountParam, *waveShapeDryWetParam, *waveShapeOnOffParam );
    effectsBuffer = foldback.processFoldback    ( effectsBuffer, *foldbackAmountParam,  *foldbackDryWetParam,  *foldbackOnOffParam  );
    effectsBuffer = bitCrusher.process          ( effectsBuffer, *bitcrushAmtParam,     *bitcrushDryWetParam,  *bitcrushOnOffParam  );
      
    int effectsSize = effectsBuffer.getNumSamples ();
    float mag       = effectsBuffer.getMagnitude  ( 0, effectsSize );
    
    // Normalize effectsBuffer values
    if (mag > 1.0f)
    {
        auto* writeL = effectsBuffer.getWritePointer ( 0 );
        auto* writeR = effectsBuffer.getWritePointer ( 1 );
        
        for (int i = 0; i < effectsSize; i++)
        {
            writeL[i] = writeL[i] / mag;
            writeR[i] = writeR[i] / mag;
        }
    }
    
    // DSP!
    for (int i=0; i<numSamples; i++)
    {
        // Apply distortion
        for (int channel = 0; channel < effectsBuffer.getNumChannels(); channel++)
        {
            if (channel == 0)
                leftChannel[i]  = effectsBuffer.getSample ( channel, i );
            if (channel == 1)
                rightChannel[i] = effectsBuffer.getSample ( channel, i );
        }
    }
    
    // Haas Widener
    if (*haasOnOffParam == 1.0f)
    {
        for (int i = 0; i < numSamples; i++)
        {
            haasSmooth.setTargetValue( *haasWidthParam );
            
            float delayInSamples = haasSmooth.getNextValue() * ( 0.03f * getSampleRate() );
            
            haasDelay.pushSample(0, leftChannel[i]);
            
            leftChannel[i] = haasDelay.popSample( 0, delayInSamples, true );
        }
    }
    
    
    
    outGain.setGainDecibels ( *outGainDBParam );
    outGain.process         ( dsp::ProcessContextReplacing<float>(sampleBlock) );
}

//==============================================================================
bool BassOnboardAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BassOnboardAudioProcessor::createEditor()
{
    //return new BassOnboardAudioProcessorEditor (*this);
    return new GenericAudioProcessorEditor (*this);
}

//==============================================================================
void BassOnboardAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // getStateInformation
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void BassOnboardAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // setStateInformation
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName (parameters.state.getType()))
        {
            parameters.replaceState (ValueTree::fromXml (*xmlState));
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BassOnboardAudioProcessor();
}
