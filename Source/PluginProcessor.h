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
                                        private juce::Timer //JOELwindows7: da Timer as in Tutorial of Midi Message
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
    void timerCallback() override;

    bool getUseEntireTracks(); // JOELwindows7: get setter of use entire tracks
    bool getUseOwnTransport(); // JOELwindows7: get setter of use entire tracks

private:
    //==============================================================================
    /** Sends Note Off / Controller Off / Sound Off on all the MIDI channels */
    void sendAllNotesOff(juce::MidiBuffer& midiMessages);

    //==============================================================================
    juce::CriticalSection processLock;

    //==============================================================================
    juce::MidiFile theMIDIFile;                       // The current MIDI file content
    bool isPlayingSomething;                    // Tells if the last audio buffer included some MIDI content to play
    bool trackHasChanged = false;
    bool useEntireTracks = false;               // tells if all tracks should be used instead
    bool useOwnTransportInstead = false;        // tells if we should use own transport instead of plugin host's Transport
                                                // very useful if your plugin host doesn't have legitimate Play Stop control buttons
                                                // such as Bespoke Synth (the Transport there plugin is not Play Stop), JUCE AudioPlugin demo, etc.
    bool myOwnIsPlaying = false;                // Own Transport Press Play mode.
    juce::AudioPlayHead::CurrentPositionInfo thePositionInfo; //JOELwindows7: make position info global!
    //juce::AudioPlayHead myPlayHead; //JOELwindows7: Host's playhead!
    juce::AudioTransportSource ownTransportSource; //JOELwindows7: this very Transport own thingy

    const juce::MidiMessageSequence* entireSequences[16]; //JOELwindows7: globalize entire sequences
    
    std::atomic<int> currentTrack;              // Current MIDI file track that is played
    std::atomic<int> numTracks;                 // Current MIDI file number of tracks
    double ownStartTime;                        // JOELwindows7: start time for own transport
    double traverseEndTime;        // JOELwindows7: Overall MIDI end time traversing sequence by sequence. who's the highest end time?
    
    double nextStartTime = -1.0;                // The start time in seconds of the next audio buffer
                                                // That information is used to know when the transport bar position 
                                                // has been moved by the user or the looping system in the DAW, so
                                                // we can call sendAllNotesOff there

    //JOELwindows7: f8888ing reset messages that is f8888ing hard to find online
    // found in LINK
    // and kuzu / OpenMIDI / Sekaiju guy Project's MIDI Tester app
    unsigned char initialSysExGM [16] =     {0xf0,0x7e,0x7f,0x09,0x01,0xf7};
    unsigned char initialSysExGMOff [16] =  {0xf0,0x7e,0x7f,0x09,0x02,0xf7};
    unsigned char initialSysExG2 [16] =     {0xf0,0x7e,0x7f,0x09,0x03,0xf7};
    unsigned char initialSysExXG [16] =     {0xf0,0x43,0x10,0x4c,0x00,0x00, 0x7e, 0x00, 0xf7 };
    unsigned char initialSysExGS [16] =     {0xf0,0x41,0x10,0x42,0x12,0x40, 0x00, 0x7f, 0x00, 0x41, 0xf7 };
    unsigned char initialSysEx88 [16] =     {0xf0,0x41,0x10,0x42,0x12,0x40, 0x00, 0x7f, 0x00, 0x01, 0xf7 };

    //JOELwindows7: flags for signalizations
    bool tellPlayNow = false;
    bool tellStopNow = false;
    bool tellRecordNow = false;
    bool tellRewindNow = false;
    bool tellWorkaroundFirst = false;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleMidiplayerAudioProcessor)
};
