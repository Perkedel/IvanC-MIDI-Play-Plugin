/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
//JOELwindows7: contruct now
SimpleMidiplayerAudioProcessorEditor::SimpleMidiplayerAudioProcessorEditor(SimpleMidiplayerAudioProcessor& p) 
    : juce::AudioProcessorEditor(&p),
    processor(p)
{
    buildDaUI();
}

SimpleMidiplayerAudioProcessorEditor::SimpleMidiplayerAudioProcessorEditor (SimpleMidiplayerAudioProcessor& p, juce::ScopedPointer<juce::Component> componento)
    : juce::AudioProcessorEditor (&p), 
    processor (p)
{
    handedOverFacemask = componento;
    buildDaUI();
}

void SimpleMidiplayerAudioProcessorEditor::putFaceMaskInstead() {
    // TODO: use handedOverFacemask GUI instead
}

void SimpleMidiplayerAudioProcessorEditor::buildDaUI() {
    //JOELwindows7: I believe this thing is called everytime you open this VSTi window.

    //TODO / IDEA: if (handedOverFaceMask != nullptr(){ /* place this instead & return? */}

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
    addAndMakeVisible(buttonPanicNow = new juce::TextButton("PANIK!!! CPR"));
    addAndMakeVisible(checkBoxAllTracks);
    addAndMakeVisible(checkBoxOwnTransport);
    addAndMakeVisible(checkBoxLoop);
    addAndMakeVisible(checkBoxSpacer);
    addAndMakeVisible(infoLabel);

    infoLabel.setMultiLine(true, true);
    infoLabel.setReadOnly(true);

    buttonPlayNow->addListener(this);
    buttonStopNow->addListener(this);
    buttonPanicNow->addListener(this);
    
    buttonPlayNow->setTooltip("Play the song (for Override Playhead) & Signal Pull the loop start");
    buttonStopNow->setTooltip("Stop the song (for Override Playhead) & Cancel signaling pull the loop start");
    buttonPanicNow->setTooltip("Send all notes OFF on all channels.\nif you have hung notes & events, press this button to shock the \"heart\" & stop fibrilation.\n Or Valsava Manuver when playing");

    //checkBoxAllTracks->addListener(this);
    checkBoxAllTracks.setButtonText("Entire Tracks");
    checkBoxAllTracks.setTooltip("Toggle whether should all tracks plays");
    //checkBoxAllTracks.setToggleState(true, juce::dontSendNotification);
    checkBoxAllTracks.setToggleState(processor.getUseEntireTracks(), juce::dontSendNotification);
    checkBoxAllTracks.onClick = [this] {
        // JOELwindows7: hey .onClick callback!
        processor.pressAllTracksCheckBox(checkBoxAllTracks.getToggleState());
    };
    checkBoxOwnTransport.setButtonText("Override Host's Play/Stop head");
    checkBoxOwnTransport.setTooltip("Toggle whether should to use own playhead instead of host's play head");
    checkBoxOwnTransport.setToggleState(processor.getUseOwnTransport(), juce::dontSendNotification);
    checkBoxOwnTransport.onClick = [this] {
        processor.pressOwnTransportCheckBox(checkBoxOwnTransport.getToggleState());
    };
    checkBoxLoop.setButtonText("Loop");
    checkBoxLoop.setTooltip("Toggle whether should the play loops");
    checkBoxLoop.setToggleState(processor.getDoLoop(), juce::dontSendNotification);
    checkBoxLoop.onClick = [this] {
        processor.pressLoopCheckBox(checkBoxLoop.getToggleState());
    };
    checkBoxSpacer.setButtonText("3 second space at end");
    checkBoxSpacer.setTooltip("Toggle whether should to add 3 second space at the end\nWithout this ON, some MIDI files will end with immediate silence (perfectly cut meme)");
    checkBoxSpacer.setToggleState(processor.getDoSpacer(), juce::dontSendNotification);
    checkBoxSpacer.onClick = [this] {
        processor.pressSpacerCheckBox(checkBoxSpacer.getToggleState());
    };

    // Click on this combo box to select the track that needs to be played
    addAndMakeVisible(comboTrack = new juce::ComboBox());
    comboTrack->addListener(this);
    updateTrackComboBox();
    infoLabel.setText("Hello World\nLoad your MIDI here. Only MIDI Type 0 (Single Track) & 1 (Multi Track) works, 2 bug & crash.\nPlease help me make PluginProcessor.cpp edit this TextEditor here where\nThis thing was defined in PluginEditor.cpp\n also pls! I need playhead override, HOW to do that?!?\nSome host lacks playhead, so I need ways to play MIDI without relying on Host's playhead.\nThancc. cool and good\n (JOELwindows7) \nPerkedel Technologies & IvanC | GNU GPL v3");


    // -------------------------------------------------------------------------
    // JOELwindows7: add resizer
    // LINK HERE
    setResizable(true, true);
    setResizeLimits(400, 300, 1280, 720);
    setSize(800, 600);

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
    //JOELwindows7: remove all callbacks & listener in this destructor (destroy)
    // this destructor calls everytime you close this window, I think.
    buttonLoadMIDIFile->removeListener(this);
    buttonPlayNow->removeListener(this);
    buttonStopNow->removeListener(this);
    buttonPanicNow->removeListener(this);
    checkBoxAllTracks.onClick = NULL;
    checkBoxOwnTransport.onClick = NULL;
    checkBoxLoop.onClick = NULL;
    checkBoxSpacer.onClick = NULL;
    comboTrack->removeListener(this);
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
    juce::Rectangle<int> rect = getLocalBounds().reduced(4); // legacy
    

    //JOELwindows7: copy from demo of Graphics Demo header.
    int daHeight = 22; // da button height
    auto columns = rect.removeFromTop(daHeight * 5);
    auto col = columns.removeFromLeft(200); // IDEA: (rect.getWidth() / 2) + 200
    
    //JOELwindows7: here's new way!
    //for (auto thing : buttonsOfStuffs) {
        /*auto index = buttonsOfStuffs.indexOf(thing);

        if (topRow.getWidth() < 10 || index == loadChooser)
            topRow = area.removeFromTop(26);

        if (index == progressWindow)
            area.removeFromTop(20);

        thing->setBounds(topRow.removeFromLeft(area.getWidth() / 2).reduced(4, 2));*/
    //}

    //buttonLoadMIDIFile->setBounds(rect.removeFromTop((rect.getHeight() / 2)-10).withSizeKeepingCentre(200, 24));
    buttonLoadMIDIFile->setBounds(col.removeFromTop(daHeight));
    //comboTrack->setBounds(rect.withSizeKeepingCentre(200, 24));
    //comboTrack->setBounds(rect.removeFromTop((rect.getHeight() / 2) - 18).withSizeKeepingCentre(200, 24));
    //comboTrack->setBounds(col.removeFromTop(daHeight));
    //JOELwindows7: don't forget resize
    //buttonPlayNow->setBounds(rect.removeFromTop(rect.getHeight() / 2 - 30).withSizeKeepingCentre(200, 24));
    //buttonStopNow->setBounds(rect.removeFromTop(rect.getHeight() / 2 - 25).withSizeKeepingCentre(200, 24));
    //buttonPlayNow->setBounds(rect.withSizeKeepingCentre(200, 50));
    //buttonStopNow->setBounds(rect.withSizeKeepingCentre(200, 100));
    //buttonPlayNow->setBounds(rect.removeFromTop((rect.getHeight() / 2) - 30).withSizeKeepingCentre(200, 24));
    //buttonStopNow->setBounds(rect.removeFromTop((rect.getHeight() / 2) - 25).withSizeKeepingCentre(200, 24));
    buttonPlayNow->setBounds(col.removeFromTop(daHeight));
    buttonStopNow->setBounds(col.removeFromTop(daHeight));
    buttonPanicNow->setBounds(col.removeFromTop(daHeight));
    
    // JOELwindows7: begin separate Column like in graphics demo
    columns.removeFromLeft(20);
    col = columns.removeFromLeft(200);
    
    //checkBoxAllTracks.setBounds(rect.withSizeKeepingCentre(200, 150));
    //checkBoxAllTracks.setBounds(rect.removeFromTop((rect.getHeight() / 2) - 20).withSizeKeepingCentre(200, 150));
    checkBoxAllTracks.setBounds(col.removeFromTop(daHeight));
    //checkBoxOwnTransport.setBounds(rect.withSizeKeepingCentre(200, 150));
    //checkBoxOwnTransport.setBounds(rect.removeFromTop((rect.getHeight() / 2) - 15).withSizeKeepingCentre(200, 150));
    checkBoxOwnTransport.setBounds(col.removeFromTop(daHeight));
    //checkBoxAllTracks.setBounds(rect.removeFromTop(rect.getHeight() / 2 - 20));
    checkBoxLoop.setBounds(col.removeFromTop(daHeight));
    checkBoxSpacer.setBounds(col.removeFromTop(daHeight));

    // JOELwindows7: graphic demo removes more rect grid spots
    rect.removeFromBottom(7);
    comboTrack->setBounds(rect.removeFromTop(daHeight));
    // copy from demo of Box2D
    //auto widePutin = rect.removeFromBottom(6); //area to fill
    //widePutin.removeFromTop(daHeight);
    //infoLabel.setBounds(widePutin);
    infoLabel.setBounds(rect.removeFromTop(400));
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
    else if (button == buttonPanicNow) {
        processor.pressPanicButton();
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

//JOELwindows7: da text label set & get
void SimpleMidiplayerAudioProcessorEditor::setInfoLabelText(juce::String daNewText) {
    infoLabel.setText(daNewText,juce::dontSendNotification);
}

juce::String SimpleMidiplayerAudioProcessorEditor::getInfoLabelText() {
    return infoLabel.getText();
}

//JOELwindows7: get instance static
//SimpleMidiplayerAudioProcessorEditor SimpleMidiplayerAudioProcessorEditor::getInstance() {
//    return this;
//}