/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "Params.h" 
#include "RotaryKnob.h"
#include "LookAndFeel.h"

//==============================================================================
/**
*/
class ReverbAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ReverbAudioProcessorEditor (ReverbAudioProcessor&);
    ~ReverbAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ReverbAudioProcessor& audioProcessor;

    // new ----
    const int WIDTH = 480, HEIGHT = 200;
    const int MID_GAP = 100;
    MainLookAndFeel mainLF; 
    RotaryKnob sizeKnob{ "size", audioProcessor.apvts, ParamID::size, false };
    RotaryKnob dampKnob{ "damp", audioProcessor.apvts, ParamID::damp, false };
    RotaryKnob widthKnob{ "width", audioProcessor.apvts, ParamID::width, false };
    RotaryKnob mixKnob{ "mix", audioProcessor.apvts, ParamID::mix, false };

    juce::Label logo;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbAudioProcessorEditor)
};
