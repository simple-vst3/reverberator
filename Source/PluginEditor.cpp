/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReverbAudioProcessorEditor::ReverbAudioProcessorEditor (ReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    logo.setText(PLUGIN_NAME, juce::dontSendNotification);
    logo.setFont(juce::FontOptions(25.f, juce::Font::bold));
    logo.setColour(juce::Label::textColourId, Colours::textColour);
    logo.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(logo);
    
    addAndMakeVisible(sizeKnob);
    addAndMakeVisible(dampKnob);

    addAndMakeVisible(freezeButton);

    addAndMakeVisible(widthKnob);
    addAndMakeVisible(mixKnob);

    setSize (WIDTH + MID_GAP, HEIGHT);
}

ReverbAudioProcessorEditor::~ReverbAudioProcessorEditor()
{
}

//==============================================================================
void ReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(Colours::boxOutline); // outer rectangle outline
    
    g.setColour(Colours::midOutline); // mid-rectangle outline
    int pad = 3;
    g.fillRect(pad, pad, getWidth() - 2 * pad, getHeight() - 2 * pad);

    g.setColour(Colours::background); // inner rectangle
    pad *= 2;
    g.fillRect(pad, pad, getWidth() - 2 * pad, getHeight() - 2 * pad);
}

void ReverbAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    auto  currWidth = WIDTH;
    const int TOP_HEIGHT = 50;
    const int KNOB_WIDTH = sizeKnob.getWidth(), KNOB_HEIGHT = sizeKnob.getHeight();

    const int xOffset = KNOB_WIDTH + 25;
    
    sizeKnob.setTopLeftPosition(currWidth/4 - xOffset, TOP_HEIGHT);
    dampKnob.setTopLeftPosition(2*currWidth / 4 - xOffset, TOP_HEIGHT);

    freezeButton.setBounds((currWidth + MID_GAP) / 2 - KNOB_WIDTH/2, TOP_HEIGHT, KNOB_WIDTH, KNOB_HEIGHT);

    widthKnob.setTopLeftPosition(3*currWidth / 4 - xOffset + MID_GAP, TOP_HEIGHT);
    mixKnob.setTopLeftPosition(currWidth - xOffset + MID_GAP, TOP_HEIGHT);

    logo.setBounds(bounds);
    logo.setTopLeftPosition(0, 20);
}
