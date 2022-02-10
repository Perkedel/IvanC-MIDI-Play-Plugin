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
class SimpleMidiplayerAudioProcessor  : public juce::AudioProcessor
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
    juce::AudioPlayHead::CurrentPositionInfo thePositionInfo; //JOELwindows7: make position info global!
    
    std::atomic<int> currentTrack;              // Current MIDI file track that is played
    std::atomic<int> numTracks;                 // Current MIDI file number of tracks
    
    double nextStartTime = -1.0;                // The start time in seconds of the next audio buffer
                                                // That information is used to know when the transport bar position 
                                                // has been moved by the user or the looping system in the DAW, so
                                                // we can call sendAllNotesOff there

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleMidiplayerAudioProcessor)
};
