/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class SimpleMidiplayerAudioProcessorEditor : public juce::AudioProcessorEditor,
    public juce::Button::Listener, public juce::ComboBox::Listener
{
public:
    //==============================================================================
    SimpleMidiplayerAudioProcessorEditor (SimpleMidiplayerAudioProcessor&);
    ~SimpleMidiplayerAudioProcessorEditor();

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    //==============================================================================
    void buttonClicked(juce:: Button* button) override;
    void comboBoxChanged(juce::ComboBox* combo) override;

private:
    //==============================================================================
    void updateTrackComboBox();

    //JOELwindows7: here define play / pause & stop button press callbacks. what if
    //we just hack the AudioPlayHead, yeah that host's play head!
    void pressPlayPauseButton();
    void pressStopButton();
    
    //==============================================================================
    juce::ScopedPointer<juce::TextButton> buttonLoadMIDIFile;
    juce::ScopedPointer<juce::ComboBox> comboTrack;

    //JOELwindows7: okay, WHY THERE IS NO PLAY BUTTON??! WHY I HAVE TO RELY ON HOST'S PLAY BUTTON??!?
    juce::ScopedPointer<juce::TextButton> buttonPlayNow; // Play / Pause
    juce::ScopedPointer<juce::TextButton> buttonStopNow; // Stop
    
    //==============================================================================
    SimpleMidiplayerAudioProcessor& processor;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleMidiplayerAudioProcessorEditor)
};
