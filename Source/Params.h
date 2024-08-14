#pragma once

#include <JuceHeader.h>

namespace ParamID
{
    const juce::ParameterID size{ "size", 1 };
    const juce::ParameterID damp{ "damp ", 1 };
    const juce::ParameterID width{ "width ", 1 };
    const juce::ParameterID mix{ "mix", 1 };
    const juce::ParameterID freeze{ "freeze", 1 };
}

class Params
{
public:
    Params(juce::AudioProcessorValueTreeState& apvts);

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    void prepare(juce::dsp::ProcessSpec spec) noexcept;
    void update() noexcept;
    void process(juce::AudioBuffer<float>& buffer) noexcept;

private:
    juce::AudioParameterFloat* sizeParam;
    juce::AudioParameterFloat* dampParam;
    juce::AudioParameterFloat* widthParam;
    juce::AudioParameterFloat* mixParam;
    juce::AudioParameterBool* freezeParam;

    juce::dsp::Reverb::Parameters params;
    juce::dsp::Reverb reverb;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Params)
};
