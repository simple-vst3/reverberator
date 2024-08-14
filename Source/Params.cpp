#include "Params.h"

template<typename T>
static void castParameter(juce::AudioProcessorValueTreeState& apvts,
    const juce::ParameterID& id, T& destination)
{
    destination = dynamic_cast<T>(apvts.getParameter(id.getParamID()));
    jassert(destination);  // parameter does not exist or wrong type
}

Params::Params(juce::AudioProcessorValueTreeState& apvts)
{
    castParameter(apvts, ParamID::size, sizeParam);
    castParameter(apvts, ParamID::damp, dampParam);
    castParameter(apvts, ParamID::width, widthParam);
    castParameter(apvts, ParamID::mix, mixParam);
    castParameter(apvts, ParamID::freeze, freezeParam);
}

juce::AudioProcessorValueTreeState::ParameterLayout Params::createParameterLayout()
{
    using namespace juce;
    AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParamID::size,
        "Size",
        juce::NormalisableRange<float> {0.0f, 100.0f, 0.1f},
        50.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParamID::damp,
        "Damp",
        juce::NormalisableRange<float> {0.0f, 100.0f, 0.1f},
        50.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParamID::width,
        "Width",
        juce::NormalisableRange<float> {0.0f, 100.0f, 0.1f},
        50.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParamID::mix,
        "Mix",
        juce::NormalisableRange<float> {0.0f, 100.0f, 0.1f},
        50.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")));

    layout.add(std::make_unique<juce::AudioParameterBool>(
        ParamID::freeze,
        "Freeze",
        false));

    return layout;
}

void Params::prepare(juce::dsp::ProcessSpec spec) noexcept
{
    reverb.prepare(spec);
}

void Params::update() noexcept
{
    // convert these params from range [0,100] - > [0, 1]
    params.roomSize = sizeParam->get() * 0.01f;
    params.damping = dampParam->get() * 0.01f;
    params.width = widthParam->get() * 0.01f;
    params.wetLevel = mixParam->get() * 0.01f;
    params.dryLevel = 1.0f - mixParam->get() * 0.01f;
    params.freezeMode = freezeParam->get();

    reverb.setParameters(params);
}

void Params::process(juce::AudioBuffer<float>& buffer) noexcept
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing ctx(block);
    reverb.process(ctx);
}