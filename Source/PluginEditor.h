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
    SimpleMidiplayerAudioProcessorEditor (SimpleMidiplayerAudioProcessor&,juce::ScopedPointer<juce::Component>);
    ~SimpleMidiplayerAudioProcessorEditor();
    void buildDaUI();
    void putFaceMaskInstead();

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    //==============================================================================
    void buttonClicked(juce:: Button* button) override;
    //void checkBoxChanged(juce::ToggleButton* checkBox) override;
    void comboBoxChanged(juce::ComboBox* combo) override;

    void setInfoLabelText(juce::String daNewText);
    juce::String getInfoLabelText();

    //static SimpleMidiplayerAudioProcessorEditor getInstance();

private:
    //==============================================================================
    void updateTrackComboBox();

    //JOELwindows7: here define play / pause & stop button press callbacks. what if
    //we just hack the AudioPlayHead, yeah that host's play head!
    /*void pressPlayPauseButton();
    void pressStopButton();*/

    //=============================================================================
    //JOELwindows7: handovered component you must paste here in your face

    //TODO: juce::Component &myMaskOn; //Or maybe2, try hacker class instead (empty bridge). nvm, not working this way I suppose.
    
    //==============================================================================
    //juce::OwnedArray<juce::TextButton> buttonsOfStuffs; //JOELwindows7: holding buttons

    juce::ScopedPointer<juce::TextButton> buttonLoadMIDIFile;
    juce::ScopedPointer<juce::ComboBox> comboTrack;

    //JOELwindows7: okay, WHY THERE IS NO PLAY BUTTON??! WHY I HAVE TO RELY ON HOST'S PLAY BUTTON??!?
    juce::ScopedPointer<juce::TextButton>   buttonPlayNow, // Play / Pause
                                            buttonStopNow // Stop
                                            ;
    juce::ToggleButton                      checkBoxAllTracks, // ON / OFF play all tracks at once
                                            checkBoxOwnTransport, // ON / OFF use own transport
                                            checkBoxLoop, // ON / OFF use loop
                                            checkBoxSpacer // ON / OFF space 3 second after the end.
                                            ;
    juce::TextEditor                        infoLabel // Comprehensive infolabels
                                            ;
    
    //==============================================================================
    SimpleMidiplayerAudioProcessor& processor;
    juce::ScopedPointer<juce::Component> handedOverFacemask;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleMidiplayerAudioProcessorEditor)
};
