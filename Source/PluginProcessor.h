/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


//==============================================================================
/**
*/
class SimpleMidiplayerAudioProcessor  : public juce::AudioProcessor, 
                                        private juce::Timer//, //JOELwindows7: da Timer as in Tutorial of Midi Message
                                        //public juce::Thread //JOELwindows7: rosshoyt Threaden MIDI play
{
public:
    //==============================================================================
    SimpleMidiplayerAudioProcessor();
    ~SimpleMidiplayerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    /** This function can be called to load a MIDI file so that it can be played. */
    void loadMIDIFile(juce::File fileMIDI);
    
    /** Returns the number of tracks in the MIDI file. */
    int getNumTracks();

    /** Sets the current track from the MIDI file that needs to be played. */
    void setCurrentTrack(int value);

    /** Returns the MIDI file track currently played. */
    int getCurrentTrack();

    /** Callbacks for Play / Pause & Stop button*/
    //JOELwindows7: here define play / pause & stop button press callbacks. what if
    //we just hack the AudioPlayHead, yeah that host's play head!
    void pressPlayPauseButton();
    void pressStopButton();
    void pressAllTracksCheckBox(bool stateNow);
    void pressOwnTransportCheckBox(bool stateNow);
    void pressLoopCheckBox(bool stateNow);
    void pressSpacerCheckBox(bool stateNow);
    void timerCallback() override;

    bool getUseEntireTracks(); // JOELwindows7: getter of use entire tracks
    bool getUseOwnTransport(); // JOELwindows7: getter of use entire tracks
    bool getDoLoop(); // JOELwindows7: getter of use loop
    bool getDoSpacer(); // JOELwindows7: getter of doSpacer

    //void handoverInfoLabel(juce::Label& thing);
    juce::String getFillYourInfoHere(); //JOELwindows7: screw this! let editor harvest it itself!

    //void threadenOwnPlayMidi(); //JOELwindows7: rosshoyt threaded play MIDI file standalone
    //void stopThreadenOwnPlayMidi(); //JOELwindows7 the stop of it.

private:
    //==============================================================================
    /** Sends Note Off / Controller Off / Sound Off on all the MIDI channels */
    void sendAllNotesOff(juce::MidiBuffer& midiMessages);

    //==============================================================================
    juce::CriticalSection processLock;

    //==============================================================================
    // JOELwindows7: da window pls
    juce::ScopedPointer<juce::Component> thisWindowThingy;           // Component you should be able to customize.
    //ThisWindowThingyPls thisWindowThingy;           // Component you should be able to customize.

    //==============================================================================
    juce::MidiFile theMIDIFile;                       // The current MIDI file content
    bool isPlayingSomething;                    // Tells if the last audio buffer included some MIDI content to play
    bool trackHasChanged = false;
    bool useEntireTracks = true;               // tells if all tracks should be used instead
    bool useOwnTransportInstead = false;        // tells if we should use own transport instead of plugin host's Transport
                                                // very useful if your plugin host doesn't have legitimate Play Stop control buttons
                                                // such as Bespoke Synth (the Transport there plugin is not Play Stop), JUCE AudioPlugin demo, etc.
    bool myOwnIsPlaying = false;                // Own Transport Press Play mode.
    bool doLoop = false;                        // Should we loop automatically?
    bool doSpacer = true;                       // Should we space 3 second at the total end?
    juce::AudioPlayHead::CurrentPositionInfo thePositionInfo; //JOELwindows7: make position info global!
    //juce::AudioPlayHead myPlayHead; //JOELwindows7: Host's playhead!
    juce::AudioTransportSource ownTransportSource; //JOELwindows7: this very Transport own thingy

    const juce::MidiMessageSequence* entireSequences[16]; //JOELwindows7: globalize entire sequences
    //juce::MidiBuffer& daMidiBuffer; //JOELwindows7: The globalized midi buffer to be filled by process block. REQUIRES INIT
    //juce::AudioBuffer<float>& daAudioBuffer; //JOELwindows7: The globalized audio buffer to be filled by process block. REQUIRES INIT
    
    std::atomic<int> currentTrack;              // Current MIDI file track that is played
    std::atomic<int> numTracks;                 // Current MIDI file number of tracks
    std::atomic<int> totalNumEvents;
    double ownStartTime;                        // JOELwindows7: start time for own transport
    double traverseEndTime;        // JOELwindows7: Overall MIDI end time traversing sequence by sequence. who's the highest end time?
    double ownElapsedTime;                      // JOELwindows7: to be ++ every timer callbacks
    double lastSampleStartTime;                 // JOELwindows7: for position pulling here purpose & loop. see https://forum.juce.com/t/how-to-loop-midi-file/33837/10?u=joelwindows
    double loop;                                // JOELwindows7: loop final calculations
    double nextStartTime = -1.0;                // The start time in seconds of the next audio buffer
                                                // That information is used to know when the transport bar position 
                                                // has been moved by the user or the looping system in the DAW, so
                                                // we can call sendAllNotesOff there
    int transpose = 0;                          // JOELwindows7: adissu had transposer. it starts from 0 & typically adjustable from -12 to 12.
    bool haveBeenSpaced = false;                // JOELwindows7: tell if the traverse end time have been spaced.

    //JOELwindows7: f8888ing reset messages that is f8888ing hard to find online
    // found in LINK
    // and kuzu / OpenMIDI / Sekaiju guy Project's MIDI Tester app
    const unsigned char initialSysExGM [16] =     {0xf0,0x7e,0x7f,0x09,0x01,0xf7};
    const unsigned char initialSysExGMOff [16] =  {0xf0,0x7e,0x7f,0x09,0x02,0xf7};
    const unsigned char initialSysExG2 [16] =     {0xf0,0x7e,0x7f,0x09,0x03,0xf7};
    const unsigned char initialSysExXG [16] =     {0xf0,0x43,0x10,0x4c,0x00,0x00, 0x7e, 0x00, 0xf7 };
    const unsigned char initialSysExGS [16] =     {0xf0,0x41,0x10,0x42,0x12,0x40, 0x00, 0x7f, 0x00, 0x41, 0xf7 };
    const unsigned char initialSysEx88 [16] =     {0xf0,0x41,0x10,0x42,0x12,0x40, 0x00, 0x7f, 0x00, 0x01, 0xf7 };

    //JOELwindows7: make them as a MidiMessage for convenience
    juce::MidiMessage initMessageGM = juce::MidiMessage::createSysExMessage(initialSysExGM, 16);
    juce::MidiMessage initMessageGMOff = juce::MidiMessage::createSysExMessage(initialSysExGMOff, 16);
    juce::MidiMessage initMessageG2 = juce::MidiMessage::createSysExMessage(initialSysExG2, 16);
    juce::MidiMessage initMessageXG = juce::MidiMessage::createSysExMessage(initialSysExXG, 16);
    juce::MidiMessage initMessageGS = juce::MidiMessage::createSysExMessage(initialSysExGS, 16);
    juce::MidiMessage initMessage88 = juce::MidiMessage::createSysExMessage(initialSysEx88, 16);

    //JOELwindows7: flags for signalizations
    bool tellPlayNow = false;
    bool tellStopNow = false;
    bool tellRecordNow = false;
    bool tellRewindNow = false;
    bool tellWorkaroundFirst = false;
    bool tellLoopPull = false;

    // JOELwindows7: handovers
    //juce::Label& giveMeInfoLabel;
    //SimpleMidiplayerAudioProcessorEditor& giveMeEditor;
    juce::String fillYourInfoHere;

    //JOELwindows7: itself instance
    //SimpleMidiplayerAudioProcessorEditor *editor; //circular dependency
    //SimpleMidiplayerAudioProcessorEditor &editorRef; // circular dependency

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleMidiplayerAudioProcessor)
};
