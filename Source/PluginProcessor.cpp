/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//JOELwindows7: pls count to 3, people

//==============================================================================
SimpleMidiplayerAudioProcessor::SimpleMidiplayerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
    ownStartTime(juce::Time::getMillisecondCounterHiRes() * 0.001)
{
    //JOELwindows7: init da thingy
    juce::AudioTransportSource ownTransportSource(); // to construct non-pointer in C++, looks like this.

    numTracks.store(0);
}

SimpleMidiplayerAudioProcessor::~SimpleMidiplayerAudioProcessor()
{
    //ownTransportSource.setSource(nullptr);
}

//==============================================================================
const juce::String SimpleMidiplayerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleMidiplayerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleMidiplayerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleMidiplayerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimpleMidiplayerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleMidiplayerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleMidiplayerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleMidiplayerAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused(index);
}

const juce::String SimpleMidiplayerAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused(index);
    return {};
}

void SimpleMidiplayerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused(index);
    juce::ignoreUnused(newName);
}

//==============================================================================
void SimpleMidiplayerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(sampleRate);
    juce::ignoreUnused(samplesPerBlock);

    nextStartTime = -1.0;
}

void SimpleMidiplayerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleMidiplayerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SimpleMidiplayerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // -------------------------------------------------------------------------
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // -------------------------------------------------------------------------
    // We clear all the incoming audio here
    for (auto i = 0; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // -------------------------------------------------------------------------
    const juce::ScopedTryLock myScopedLock(processLock);

    // JOELwindows7: attempt to transport get next audio block
    // https://talktopoorni.medium.com/developing-audio-plugin-with-integrated-file-player-in-juce-929d5525988d
    ownTransportSource.getNextAudioBlock(juce::AudioSourceChannelInfo(buffer));

    // JOELwindows7: moar, DSP filtering
    // same article as above
    // taken from https://docs.juce.com/master/tutorial_playing_sound_files.html
    // the JUCE tutorial itself, but that above adds Plugined support
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        //DSP Filtering code comes here
    }

    if (myScopedLock.isLocked())
    {
        /*juce::AudioPlayHead::CurrentPositionInfo thePositionInfo;*/
        getPlayHead()->getCurrentPosition(thePositionInfo);
        //ownTransportSource.getCurrentPosition(thePositionInfo);
        
        if (numTracks.load() > 0)
        {
            //JOELwindows7: receive tell signals
            if (tellPlayNow)
            {
                //thePositionInfo.transportPlay(true);
                /*if (useOwnTransportInstead)
                    ownTransportSource.start();
                else
                    getPlayHead()->transportPlay(true);*/
                tellPlayNow = false;
            }

            if (tellStopNow)
            {
                /*if (useOwnTransportInstead)
                    ownTransportSource.stop();
                else
                    getPlayHead()->transportPlay(false);*/
                tellStopNow = false;
            }

            if (tellRecordNow)
            {
                tellRecordNow = false;
            }

            if (tellRewindNow) {
                tellRewindNow = false;
            }

            if (tellWorkaroundFirst) {

            }
            else {
                //Yamaha S-YXG2006LE not drum on not XG proper MIDI
                auto daDrumPatch = juce::MidiMessage::programChange(10, 127);
                daDrumPatch.setTimeStamp(0);
                //auto daSysEx = juce::MidiMessage::createSysExMessage(&0xf0f7);
                midiMessages.addEvent(daDrumPatch,0);
                //midiMessages.addEvent(juce::MidiMessage::createSysExMessage(0xf04310));

                //Flip signal
                tellWorkaroundFirst = true;
            }

            // The MIDI file is played only when the transport is active
            // TODO: JOELwindows7: point of transport override. add ignore transport and use own transport
            if (useOwnTransportInstead) {
                if (ownTransportSource.isPlaying()) {
                    const juce::MidiMessageSequence* theSequence = theMIDIFile.getTrack(currentTrack.load());

                    auto startTime = ownTransportSource.getCurrentPosition();
                    auto endTime = startTime + buffer.getNumSamples() / getSampleRate();
                    auto sampleLength = 1.0 / getSampleRate();

                    // If the transport bar position has been moved by the user or because of looping
                    if (std::abs(startTime - nextStartTime) > sampleLength && nextStartTime > 0.0)
                        sendAllNotesOff(midiMessages);

                    nextStartTime = endTime;

                    //JOELwindows7: now use 2 different modes
                    if (useEntireTracks)
                    {
                        // If the MIDI file doesn't contain any event anymore
                        if (isPlayingSomething && startTime >= traverseEndTime)
                            sendAllNotesOff(midiMessages);
                        else
                        {
                            // Called when the user changes the track during playback
                            if (trackHasChanged)
                            {
                                trackHasChanged = false;
                                // but this time don't send all note off!
                            }

                            for (int i = 0; i < (numTracks.load()); i++) {
                                // copy playback from bellow
                                for (auto j = 0; j < entireSequences[i]->getNumEvents(); j++) {
                                    juce::MidiMessageSequence::MidiEventHolder* event = entireSequences[i]->getEventPointer(j);

                                    if (event->message.getTimeStamp() >= startTime && event->message.getTimeStamp() < endTime)
                                    {
                                        auto samplePosition = juce::roundToInt((event->message.getTimeStamp() - startTime) * getSampleRate());
                                        midiMessages.addEvent(event->message, samplePosition);

                                        isPlayingSomething = true;
                                    }
                                }
                            }
                        }
                    }
                    else {
                        // If the MIDI file doesn't contain any event anymore
                        if (isPlayingSomething && startTime >= theSequence->getEndTime())
                            sendAllNotesOff(midiMessages);

                        else
                        {
                            // Called when the user changes the track during playback
                            if (trackHasChanged)
                            {
                                trackHasChanged = false;
                                sendAllNotesOff(midiMessages);
                            }

                            // Iterating through the MIDI file contents and trying to find an event that
                            // needs to be called in the current time frame
                            for (auto i = 0; i < theSequence->getNumEvents(); i++)
                            {
                                juce::MidiMessageSequence::MidiEventHolder* event = theSequence->getEventPointer(i);

                                if (event->message.getTimeStamp() >= startTime && event->message.getTimeStamp() < endTime)
                                {
                                    auto samplePosition = juce::roundToInt((event->message.getTimeStamp() - startTime) * getSampleRate());
                                    midiMessages.addEvent(event->message, samplePosition);

                                    isPlayingSomething = true;
                                }
                            }
                        }
                    }
                }
                else {
                    // If the transport isn't active anymore
                    if (isPlayingSomething)
                        sendAllNotesOff(midiMessages);
                }
            } else{
                if (thePositionInfo.isPlaying)
                {
                    const juce::MidiMessageSequence* theSequence = theMIDIFile.getTrack(currentTrack.load());
                    //const juce::MidiMessageSequence* entireSequence[16] = {}; //JOELwindows7: help me!

                    /*for (int i = 0; i < theMIDIFile.getNumTracks()-1; i++)
                    {
                        entireSequences[i] = theMIDIFile.getTrack(i);
                    }*/

                    auto startTime = thePositionInfo.timeInSeconds;
                    auto endTime = startTime + buffer.getNumSamples() / getSampleRate();
                    auto sampleLength = 1.0 / getSampleRate();

                    // If the transport bar position has been moved by the user or because of looping
                    if (std::abs(startTime - nextStartTime) > sampleLength && nextStartTime > 0.0)
                        sendAllNotesOff(midiMessages);

                    nextStartTime = endTime;

                    //JOELwindows7: now use 2 different modes
                    if (useEntireTracks)
                    {
                        // If the MIDI file doesn't contain any event anymore
                        if (isPlayingSomething && startTime >= traverseEndTime)
                            sendAllNotesOff(midiMessages);
                        else
                        {
                            // Called when the user changes the track during playback
                            if (trackHasChanged)
                            {
                                trackHasChanged = false;
                                // but this time don't send all note off!
                            }

                            for (int i = 0; i < (numTracks.load()); i++) {
                                // copy playback from bellow
                                for (auto j = 0; j < entireSequences[i]->getNumEvents(); j++) {
                                    juce::MidiMessageSequence::MidiEventHolder* event = entireSequences[i]->getEventPointer(j);

                                    if (event->message.getTimeStamp() >= startTime && event->message.getTimeStamp() < endTime)
                                    {
                                        auto samplePosition = juce::roundToInt((event->message.getTimeStamp() - startTime) * getSampleRate());
                                        midiMessages.addEvent(event->message, samplePosition);

                                        isPlayingSomething = true;
                                    }
                                }
                            }
                        }
                    }
                    else {
                        // If the MIDI file doesn't contain any event anymore
                        if (isPlayingSomething && startTime >= theSequence->getEndTime())
                            sendAllNotesOff(midiMessages);

                        else
                        {
                            // Called when the user changes the track during playback
                            if (trackHasChanged)
                            {
                                trackHasChanged = false;
                                sendAllNotesOff(midiMessages);
                            }

                            // Iterating through the MIDI file contents and trying to find an event that
                            // needs to be called in the current time frame
                            for (auto i = 0; i < theSequence->getNumEvents(); i++)
                            {
                                juce::MidiMessageSequence::MidiEventHolder* event = theSequence->getEventPointer(i);

                                if (event->message.getTimeStamp() >= startTime && event->message.getTimeStamp() < endTime)
                                {
                                    auto samplePosition = juce::roundToInt((event->message.getTimeStamp() - startTime) * getSampleRate());
                                    midiMessages.addEvent(event->message, samplePosition);

                                    isPlayingSomething = true;
                                }
                            }
                        }
                    }
                }
                else
                {
                    // If the transport isn't active anymore
                    if (isPlayingSomething)
                        sendAllNotesOff(midiMessages);
                }
            }
        }
    }
    else
    {
        // If we have just opened a MIDI file with no content
        if (isPlayingSomething)
            sendAllNotesOff(midiMessages);        
    }
}

//==============================================================================
bool SimpleMidiplayerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SimpleMidiplayerAudioProcessor::createEditor()
{
    return new SimpleMidiplayerAudioProcessorEditor (*this);
}

//==============================================================================
void SimpleMidiplayerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::ignoreUnused(destData);
}

void SimpleMidiplayerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    juce::ignoreUnused(data);
    juce::ignoreUnused(sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleMidiplayerAudioProcessor();
}

//==============================================================================
void SimpleMidiplayerAudioProcessor::loadMIDIFile(juce::File fileMIDI)
{
    const juce::ScopedLock myScopedLock(processLock);

    theMIDIFile.clear();
    
    juce::FileInputStream theStream(fileMIDI);
    theMIDIFile.readFrom(theStream);

    /** This function call means that the MIDI file is going to be played with the
        original tempo and signature.

        To play it at the host tempo, we might need to do it manually in processBlock
        and retrieve all the time the current tempo to track tempo changes.
    */
    theMIDIFile.convertTimestampTicksToSeconds();
    
    numTracks.store(theMIDIFile.getNumTracks());
    currentTrack.store(0);
    trackHasChanged = false;

    //JOELwindows7: now load them up to sequences!
    //traverseEndTime = 0.00; // reset end time
    traverseEndTime = theMIDIFile.getLastTimestamp() + 3.00; // AH PECKING FOUND IT!!! THE LENGTH OF MIDI FILE!!!
    //entireSequences.clear();
    //help how do I clear all array in const!!!???
    //for (int i = 0; i < 15; i++)
    //{
    //    //entireSequences[i] = NULL;
    //}

    for (int i = 0; i < numTracks.load(); i++)
    {
        entireSequences[i] = theMIDIFile.getTrack(i);
        //traverseEndTime = std::max(traverseEndTime, theMIDIFile.getTrack(i)->getEndTime());
        //JOELwindows7: perhaps it doesn't work?
        /*if (theMIDIFile.getTrack(i)->getEndTime() >= traverseEndTime) {
            traverseEndTime = theMIDIFile.getTrack(i)->getEndTime();
        }*/
    }

    //JOELwindows7: workarounds for VSTis
    // Yamaha S-YXG2006LE default init state did not even set drum on Ch. 10 properly.
    // must manually set it. Dude, not all MIDI does that, it's initiative for XG ASMR MIDIs typically.
    // on on any other bland potatoes MIDIs.
    juce::MidiMessage::programChange(10, 127); // GM drum

    tellWorkaroundFirst = false;
}

//JOELwindows7: press play button
void SimpleMidiplayerAudioProcessor::pressPlayPauseButton() {
    //const juce::ScopedLock myScopedLock(processLock);
    if (useOwnTransportInstead) {
        if (ownTransportSource.isPlaying()) {

        }
        else {
            ownTransportSource.start();
        }
    }
    tellPlayNow = true;
}

//JOELwindows7: press stop button
void SimpleMidiplayerAudioProcessor::pressStopButton() {
    //const juce::ScopedLock myScopedLock(processLock);
    if (useOwnTransportInstead) {
        ownTransportSource.stop();
        ownTransportSource.setPosition(0);
    }
    tellStopNow = true;
}

void SimpleMidiplayerAudioProcessor::pressAllTracksCheckBox(bool stateNow) {
    useEntireTracks = stateNow;
    //sendAllNotesOff(midiMessages);
}

void SimpleMidiplayerAudioProcessor::pressOwnTransportCheckBox(bool stateNow) {
    useOwnTransportInstead = stateNow;
    //sendAllNotesOff(midiMessages);
}

bool SimpleMidiplayerAudioProcessor::getUseEntireTracks() {
    return useEntireTracks;
}

bool SimpleMidiplayerAudioProcessor::getUseOwnTransport() {
    return useOwnTransportInstead;
}

int SimpleMidiplayerAudioProcessor::getNumTracks()
{
    return numTracks.load();
}

void SimpleMidiplayerAudioProcessor::setCurrentTrack(int value)
{
    jassert(value >= 0 && value < numTracks.load());
    
    if (numTracks.load() == 0)
        return;

    currentTrack.store(value);
    trackHasChanged = true;
}

int SimpleMidiplayerAudioProcessor::getCurrentTrack()
{
    if (numTracks.load() == 0)
        return -1;

    else
        return currentTrack.load();
}

void SimpleMidiplayerAudioProcessor::sendAllNotesOff(juce::MidiBuffer& midiMessages)
{
    for (auto i = 1; i <= 16; i++)
    {
        midiMessages.addEvent(juce::MidiMessage::allNotesOff(i), 0);
        midiMessages.addEvent(juce::MidiMessage::allSoundOff(i), 0);
        midiMessages.addEvent(juce::MidiMessage::allControllersOff(i), 0);
    }

    isPlayingSomething = false;
    tellWorkaroundFirst = false;
}
