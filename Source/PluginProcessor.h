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
class KaiKhorusAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    KaiKhorusAudioProcessor();
    ~KaiKhorusAudioProcessor() override;

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
    
    juce::AudioProcessorValueTreeState treeState;


private:
    
    juce::AudioBuffer<float> delayBuffer;
    void fillDelayBuffer(juce::AudioBuffer<float>& delayBuffer, int channel, float feedbackGain);
    void updateBufferPositions(juce::AudioBuffer<float>&buffer, juce::AudioBuffer<float>&delayBuffer);
    float cubicInterpolation(int channel, float readPosition, int localReadPosition);
    float lfo(float phase);
    float calculateChorusSample(int channel, int sample, float phase, float width, float frequency);
    float incrementPhase(float frequency, float phase);
    
    int delayBufferSize;
    int writePosition {0};
    int readPosition {0};
    float lfoPhase1 {0};
    float lfoPhase2 {0};
    
    float maxBufferDelay {0.500f}; //Allows for maximum 500ms of delay, the longest this chorus needs is 4.11ms needed for button 2
    float mix;
    
    float button1Frequency {0.513f}; //in Hertz
    float button1Width {0.00369f}; //3.69ms of delay
    
    float button2Frequency {1.0f}; //in Hertz
    float button2Width {0.00411f}; //4.11ms of delay
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KaiKhorusAudioProcessor)
};
