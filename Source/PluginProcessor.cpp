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
                                          NormalisableRange<float>(0.0f, 2.0f, 0.01f, 2.0f, true), 1.0f, "Input Gain" ),
    std::make_unique<AudioParameterFloat>("outGain", "Output Gain",
                                          NormalisableRange<float>(0.0f, 2.0f, 0.01f, 2.0f, true), 1.0f, "Output Gain" ),
    // Noise Gate Params
    std::make_unique<AudioParameterFloat>("ngThresh", "Noise Gate Threshold",
                                          NormalisableRange<float>(-100.0f, 12.0f, 0.01f, 2.0f, false), -96.0f, "Noise Gate Threshold" ),
    std::make_unique<AudioParameterFloat>("ngRatio", "Noise Gate Ratio",
                                          NormalisableRange<float>(1.0f, 25.0f, 0.1f, 0.25f, false), 25.0f, "Noise Gate Ratio" ),
    std::make_unique<AudioParameterFloat>("ngAttack", "Noise Gate Attack",
                                          NormalisableRange<float>(0.1f, 10.0f, 0.1f, 1.0f, false), 0.5f, "Noise Gate Attack" ),
    std::make_unique<AudioParameterFloat>("ngRelease", "Noise Gate Release",
                                          NormalisableRange<float>(0.1f, 10.0f, 0.1f, 1.0f, false), 2.0f, "Noise Gate Release" ),
    
    // Compressor Params
    std::make_unique<AudioParameterFloat>("compThresh", "Compressor Threshold",
                                          NormalisableRange<float>(-100.0f, 12.0f, 0.01f, 2.0f, false), 0.0f, "Compressor Threshold" ),
    std::make_unique<AudioParameterFloat>("compRatio", "Compressor Ratio",
                                          NormalisableRange<float>(1.0f, 25.0f, 0.1f, 0.25f, false), 1.0f, "Compressor Ratio" ),
    std::make_unique<AudioParameterFloat>("compAttack", "Compressor Attack",
                                          NormalisableRange<float>(0.1f, 10.0f, 0.1f, 1.0f, false), 0.5f, "Compressor Attack" ),
    std::make_unique<AudioParameterFloat>("compRelease", "Compressor Release",
                                          NormalisableRange<float>(0.1f, 10.0f, 0.1f, 1.0f, false), 2.0f, "Compressor Release" )
    
})

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
    
    // Compressor Params
    compThreshParam  = parameters.getRawParameterValue ( "compThresh"  );
    compRatioParam   = parameters.getRawParameterValue ( "compRatio"   );
    compAttackParam  = parameters.getRawParameterValue ( "compAttack"  );
    compReleaseParam = parameters.getRawParameterValue ( "compRelease" );
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
    dsp::ProcessSpec spec;
    
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate       = sampleRate;
    
    inGain.prepare                ( spec );
    inGain.reset                  ();
    inGain.setRampDurationSeconds ( 0.001f );
    
    noiseGate.prepare ( spec );
    noiseGate.reset   ();
    
    comp.prepare ( spec );
    comp.reset   ();
    
    waveShaper.prepare ( spec );
    waveShaper.reset   ();
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
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // Create the AudioBlock for DSP widgets
    dsp::AudioBlock<float> sampleBlock ( buffer );
    
    // Apply Input Gain
    inGain.setGainDecibels ( *inGainDBParam );
    inGain.process         ( dsp::ProcessContextReplacing<float>(sampleBlock) );
    
    // Apply Noise Gate
    noiseGate.setThreshold ( *ngThreshParam  );
    noiseGate.setRatio     ( *ngRatioParam   );
    noiseGate.setAttack    ( *ngAttackParam  );
    noiseGate.setRelease   ( *ngReleaseParam );
    noiseGate.process      ( dsp::ProcessContextReplacing<float>(sampleBlock) );
    
    // Apply Compressor
    comp.setThreshold ( *compThreshParam );
    comp.setRatio     ( *compRatioParam  );
    comp.setAttack    ( *compAttackParam );
    comp.setRatio     ( *compRatioParam  );
    comp.process      ( dsp::ProcessContextReplacing<float>(sampleBlock) );

    // Audio input to buffer
    int numSamples     = buffer.getNumSamples();
    auto* leftChannel  = buffer.getWritePointer(0);
    auto* rightChannel = buffer.getWritePointer(1);
    
    
    for (int i=0; i<numSamples; i++)
    {
        // Apply input gain
        //float inLeftSample  = leftChannel[i]  * *inGainDBParam;
        //float inRightSample = rightChannel[i] * *inGainDBParam;
        
        // Ouput Gain
        //leftChannel[i]  = inLeftSample  * *outGainDBParam;
        //rightChannel[i] = inRightSample * *outGainDBParam;
    }
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