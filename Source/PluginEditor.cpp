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
    if (button == buttonLoadMIDIFile)
    {
        juce::FileChooser theFileChooser("Find a MIDI file", juce::File(), "*.mid*");
        
        if (theFileChooser.browseForFileToOpen())
        {
            processor.loadMIDIFile(theFileChooser.getResult());
            updateTrackComboBox();
        }
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