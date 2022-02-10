/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SimpleMidiplayerAudioProcessorEditor::SimpleMidiplayerAudioProcessorEditor (SimpleMidiplayerAudioProcessor& p)
    : juce::AudioProcessorEditor (&p), processor (p)
{
    // -------------------------------------------------------------------------
    // Click on this button to select a MIDI file to play in the processor
    addAndMakeVisible(buttonLoadMIDIFile = new juce::TextButton("Load a MIDI file"));
    buttonLoadMIDIFile->addListener(this);

    // JOELwindows7: Click on this button to play / pause, and another to stop.
    addAndMakeVisible(buttonPlayNow = new juce::TextButton("Play / Pause"));
    addAndMakeVisible(buttonStopNow = new juce::TextButton("Stop"));
    buttonPlayNow->addListener(this);
    buttonStopNow->addListener(this);

    // Click on this combo box to select the track that needs to be played
    addAndMakeVisible(comboTrack = new juce::ComboBox());
    comboTrack->addListener(this);
    updateTrackComboBox();
    
    // -------------------------------------------------------------------------
    setSize (400, 300);
}

SimpleMidiplayerAudioProcessorEditor::~SimpleMidiplayerAudioProcessorEditor()
{
}

void SimpleMidiplayerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void SimpleMidiplayerAudioProcessorEditor::resized()
{
    juce::Rectangle<int> rect = getLocalBounds();
    
    buttonLoadMIDIFile->setBounds(rect.removeFromTop(rect.getHeight() / 2).withSizeKeepingCentre(200, 24));
    comboTrack->setBounds(rect.withSizeKeepingCentre(200, 24));
}

void SimpleMidiplayerAudioProcessorEditor::buttonClicked(juce::Button * button)
{
    // JOELwindows7: unfortunately folks, Switch case only works on integral or enum type.
    if (button == buttonLoadMIDIFile)
    {
        juce::FileChooser theFileChooser("Find a MIDI file", juce::File(), "*.mid*");
        
        // JOELwindows7: You must add `JUCE_MODAL_LOOPS_PERMITTED=1` into project setting,
        // preprocessor definitions.
        if (theFileChooser.browseForFileToOpen()) 
        {
            processor.loadMIDIFile(theFileChooser.getResult());
            updateTrackComboBox();
        }
    }
    else if (button == buttonPlayNow) {
        //JOELwindows7: peck!! I have to do this nasty else ifs??!??!?
        processor.pressPlayPauseButton();
    }
    else if (button == buttonStopNow) {
        // JOELwindows7: ah damn!
        processor.pressStopButton();
    }
}

void SimpleMidiplayerAudioProcessorEditor::comboBoxChanged(juce::ComboBox* combo)
{
    if (combo == comboTrack)
    {
        processor.setCurrentTrack(combo->getSelectedId() - 1);
    }
}

void SimpleMidiplayerAudioProcessorEditor::updateTrackComboBox()
{
    comboTrack->clear();

    for (auto i = 0; i < processor.getNumTracks(); i++)
        comboTrack->addItem("Track number " + juce::String(i + 1), i + 1);

    comboTrack->setSelectedId(processor.getCurrentTrack() + 1, juce::dontSendNotification);
}