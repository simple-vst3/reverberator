#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

class FreezeButton final : public juce::Component
{
public:
    enum ColourIds
    {
        onColourId,
        offColourId,
        focusColourId
    };

    FreezeButton(juce::AudioProcessorValueTreeState& apvts, const juce::String parameterID);

    void paint(juce::Graphics& g) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;

    void focusGained(FocusChangeType cause) override;
    void focusLost(FocusChangeType cause) override;

    bool keyPressed(const juce::KeyPress& key) override;

private:
    void updateState(bool newState);

    bool state{ false };

    juce::Path iconPath;
    juce::Rectangle<float> iconBounds;
    juce::Label label;

    juce::ParameterAttachment attachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FreezeButton)
};