#include "FreezeButton.h"
#include "LookAndFeel.h"
#include <BinaryData.h>

FreezeButton::FreezeButton(juce::AudioProcessorValueTreeState& apvts, const juce::String parameterID)
    : attachment(*apvts.getParameter(parameterID), [&](float v) { updateState(static_cast<bool> (v)); }, nullptr)
{
    setWantsKeyboardFocus(true);
    setRepaintsOnMouseActivity(true);
    setColour(onColourId, Colours::Knob::trackActive);
    setColour(offColourId, Colours::textColour);
    setColour(focusColourId, Colours::textColour.brighter(0.25f));

    const auto svg = juce::Drawable::createFromImageData(BinaryData::freezeIcon_svg, BinaryData::freezeIcon_svgSize);
    jassert(svg != nullptr);

    if (svg != nullptr)
        iconPath = svg->getOutlineAsPath();

    attachment.sendInitialUpdate();
}

void FreezeButton::resized()
{
    iconBounds = getLocalBounds().toFloat();
    iconPath.applyTransform(iconPath.getTransformToScaleToFit(iconBounds, true));
}

void FreezeButton::paint(juce::Graphics& g)
{
    g.setColour(findColour(state ? onColourId : hasKeyboardFocus(true) ? focusColourId : offColourId));
    g.fillPath(iconPath);
}

void FreezeButton::mouseDown(const juce::MouseEvent& e)
{
    juce::ignoreUnused(e);

    attachment.setValueAsCompleteGesture(!state);

    const auto centre = iconBounds.getCentre();
    iconPath.applyTransform(juce::AffineTransform::scale(0.95f, 0.95f, centre.x, centre.y));
}

void FreezeButton::mouseUp(const juce::MouseEvent& e)
{
    juce::ignoreUnused(e);
    iconPath.applyTransform(iconPath.getTransformToScaleToFit(iconBounds, true));
}

void FreezeButton::focusGained(FocusChangeType cause)
{
    juce::ignoreUnused(cause);
    repaint();
}

void FreezeButton::focusLost(FocusChangeType cause)
{
    juce::ignoreUnused(cause);
    repaint();
}

bool FreezeButton::keyPressed(const juce::KeyPress& key)
{
    if (key == juce::KeyPress::returnKey)
    {
        attachment.setValueAsCompleteGesture(!state);
        return true;
    }

    return false;
}

void FreezeButton::updateState(bool newState)
{
    state = newState;
    repaint();
}