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
    //addAndMakeVisible(buttonsOfStuffs.add (buttonLoadMIDIFile = new juce::TextButton("Load a MIDI file")));
    addAndMakeVisible(buttonLoadMIDIFile = new juce::TextButton("Load a MIDI file"));
    buttonLoadMIDIFile->addListener(this);

    // JOELwindows7: Click on this button to play / pause, and another to stop.
    //addAndMakeVisible(buttonsOfStuffs.add(buttonPlayNow = new juce::TextButton("Play / Pause")));
    addAndMakeVisible(buttonPlayNow = new juce::TextButton("Play / Pause"));
    //addAndMakeVisible(buttonsOfStuffs.add(buttonStopNow = new juce::TextButton("Stop")));
    addAndMakeVisible(buttonStopNow = new juce::TextButton("Stop"));
    addAndMakeVisible(checkBoxAllTracks);
    buttonPlayNow->addListener(this);
    buttonStopNow->addListener(this);
    //checkBoxAllTracks->addListener(this);
    checkBoxAllTracks.setButtonText("Entire Tracks");
    //checkBoxAllTracks.setToggleState(true, juce::dontSendNotification);
    checkBoxAllTracks.setToggleState(processor.getUseEntireTracks(), juce::dontSendNotification);
    checkBoxAllTracks.onClick = [this] {
        // JOELwindows7: hey .onClick callback!
        processor.pressAllTracksCheckBox(checkBoxAllTracks.getToggleState());
    };

    // Click on this combo box to select the track that needs to be played
    addAndMakeVisible(comboTrack = new juce::ComboBox());
    comboTrack->addListener(this);
    updateTrackComboBox();
    
    // -------------------------------------------------------------------------
    // JOELwindows7: add resizer
    // LINK HERE
    setResizable(true, true);
    setSize (800, 600);

    // JOELwindows7: Copy from JUCE demo of `DialogsDemo.h
    juce::RuntimePermissions::request(juce::RuntimePermissions::readExternalStorage,
        [](bool granted)
        {
            if (!granted)
                juce::AlertWindow::showAsync(juce::MessageBoxOptions()
                    .withIconType(juce::MessageBoxIconType::WarningIcon)
                    .withTitle("Permissions warning")
                    .withMessage("External storage access permission not granted, some files"
                        " may be inaccessible.")
                    .withButton("OK"),
                    nullptr);
        });
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
    //JOELwindows7: rehaul to use Dialog Demo's way of resize
    //auto area = getLocalBounds().reduced(5, 15);
    //juce::Rectangle<int> topRow;
    juce::Rectangle<int> rect = getLocalBounds(); // legacy
    
    //JOELwindows7: here's new way!
    //for (auto thing : buttonsOfStuffs) {
        /*auto index = buttonsOfStuffs.indexOf(thing);

        if (topRow.getWidth() < 10 || index == loadChooser)
            topRow = area.removeFromTop(26);

        if (index == progressWindow)
            area.removeFromTop(20);

        thing->setBounds(topRow.removeFromLeft(area.getWidth() / 2).reduced(4, 2));*/
    //}

    buttonLoadMIDIFile->setBounds(rect.removeFromTop((rect.getHeight() / 2)-10).withSizeKeepingCentre(200, 24));
    //comboTrack->setBounds(rect.withSizeKeepingCentre(200, 24));
    comboTrack->setBounds(rect.removeFromTop((rect.getHeight() / 2) - 18).withSizeKeepingCentre(200, 24));
    //JOELwindows7: don't forget resize
    //buttonPlayNow->setBounds(rect.removeFromTop(rect.getHeight() / 2 - 30).withSizeKeepingCentre(200, 24));
    //buttonStopNow->setBounds(rect.removeFromTop(rect.getHeight() / 2 - 25).withSizeKeepingCentre(200, 24));
    //buttonPlayNow->setBounds(rect.withSizeKeepingCentre(200, 50));
    //buttonStopNow->setBounds(rect.withSizeKeepingCentre(200, 100));
    buttonPlayNow->setBounds(rect.removeFromTop((rect.getHeight() / 2) - 30).withSizeKeepingCentre(200, 24));
    buttonStopNow->setBounds(rect.removeFromTop((rect.getHeight() / 2) - 25).withSizeKeepingCentre(200, 24));
    checkBoxAllTracks.setBounds(rect.withSizeKeepingCentre(200, 150));
    //checkBoxAllTracks.setBounds(rect.removeFromTop(rect.getHeight() / 2 - 20));
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
    //else if (button == checkBoxAllTracks) {
    //    // JOELwindows7: hey .onClick callback!
    //    processor.pressAllTracksCheckBox(checkBoxAllTracks.getToggleState());
    //}
}

//void SimpleMidiplayerAudioProcessorEditor::checkBoxChanged(juce::ToggleButton* checkBox) {
//
//}

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