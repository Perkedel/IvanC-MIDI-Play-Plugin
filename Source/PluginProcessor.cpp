/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ThisWindowThingyPls.h"

//JOELwindows7: pls count to 3, people

//==============================================================================
SimpleMidiplayerAudioProcessor::SimpleMidiplayerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
        //IDEA: JOELwindows7: moar audio outs for
        // - Soundfonteh all MIDI channels
        // - Soundfonteh each MIDI channel has a pair.
    ),
#endif
    ownStartTime(juce::Time::getMillisecondCounterHiRes() * 0.001),
    //daMidiBuffer(initMessageGS),daAudioBuffer(),
    //editorRef(new SimpleMidiplayerAudioProcessorEditor(*this)) // Circular dependency
    //Thread("rosshoyt MIDI Player Thread") // werror! thread abstract causes This class abstract not allowed instancing
    //Thread("anThreaden"), // werror! thread abstract causes This class abstract not allowed instancing
    thisWindowThingy(new ThisWindowThingyPls()),
    daInfoTextBox(new juce::TextEditor),
    daTimerLabel(new juce::Label("Timer","0:00 / 0:00"))
{
    // JOELwindows7: component pls
    //thisWindowThingy = new ThisWindowThingyPls();

    //JOELwindows7: init da thingy
    juce::AudioTransportSource ownTransportSource(); // to construct non-pointer in C++, looks like this.

    //JOELwindows7: reference pls
    // don't forget follow MIDI demo received message sets for that info text box!
    daInfoTextBox->setReturnKeyStartsNewLine(false);
    daInfoTextBox->setMultiLine(true);
    daInfoTextBox->setReadOnly(true);
    daInfoTextBox->setScrollbarsShown(true);
    daInfoTextBox->setCaretVisible(true);
    daInfoTextBox->setPopupMenuEnabled(false);
    daInfoTextBox->setText(fillYourInfoHere, juce::dontSendNotification);
    daTimerLabel->setText(fillYourTimerHere, juce::dontSendNotification);
    daTimerLabel->setSize(100, 50);
    
    //JOELwindows7: radio buttoning to be refered by editor. push them to arrays.
    // use demo of look and feel
    for (int i = 0; i < radioButtoningsSay.size(); i++)
    {
        auto* b = radioButtonings.add(new juce::TextButton(radioButtoningsSay[i], radioButtoningsTooltips[i]));

        //int whereModeSet = i;
        //tempFillOutSetMode = i;

        b->setRadioGroupId(77);
        b->setClickingTogglesState(true);
        b->setTooltip(radioButtoningsTooltips[i]); // I said, THE PECKING TOOLTIPS!!!
        //b->setComponentID(juce::String(i));
        b->onClick = std::bind([this](int a) {
            tellInfoModes = a;
            pressRadioButtonings(a);
            }, i);

        //Okay that look & feel demo's edging is not procedural! pick from Widgets demo!!! Buttons page.
        b->setConnectedEdges(
            ((i != 0) ? juce::Button::ConnectedOnLeft : 0) 
            | 
            ((i != radioButtoningsSay.size()-1) ? juce::Button::ConnectedOnRight : 0))
            ;
    }

    numTracks.store(0);
    //startTimer(1);
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

    //JOELwindows7: receive tell signals
    if (tellPlayNow)
    {
        //thePositionInfo.transportPlay(true);
        if (useOwnTransportInstead) {
            //ownTransportSource.start();
            ownStopPlaying = false;
            ownIsPlaying = !ownIsPlaying;
            if (ownIsPlaying) {

            }
            else {

            }
        }
        else {
            //getPlayHead()->transportPlay(true);
        }
        tellPlayNow = false;
    }

    if (tellStopNow)
    {
        if (useOwnTransportInstead){
            //ownTransportSource.stop();
            ownIsPlaying = false;
            ownStopPlaying = true;
        }
        else{
            //getPlayHead()->transportPlay(false);
        }

        tellStopNow = false;
    }

    if (tellRecordNow)
    {
        tellRecordNow = false;
    }

    if (tellRewindNow) {
        tellRewindNow = false;
    }

    if (tellPanic) {
        // PANIK ATTACK!!!

        sendAllNotesOff(midiMessages);
        tellPanic = false;
    }

    if (tellWorkaroundFirst) {

    }
    else {
        //Globalize MIDI buffer
        //daMidiBuffer = midiMessages;
        //daAudioBuffer = buffer;

        //Enable GM first, very important!
        initMessageGM.setTimeStamp(0);
        midiMessages.addEvent(initMessageGM, 0);

        //Yamaha S-YXG2006LE not drum on not XG proper MIDI
        auto daDrumPatch = juce::MidiMessage::programChange(10, 127); //incorrecta, this is gunshot! GM, activate drum mode!!
        daDrumPatch.setTimeStamp(0);
        // use GS because this Roland's reset is almost same as GM but bit extended.
        // okay fine how about GM2 instead? Can't! not all compatible.
        auto daSysEx = juce::MidiMessage::createSysExMessage(initialSysExG2, 16);
        daSysEx.setTimeStamp(0);
        //midiMessages.addEvent(daDrumPatch,2);
        midiMessages.addEvent(daSysEx, 0);

        //Flip signal
        tellWorkaroundFirst = true;
    }

    if (myScopedLock.isLocked())
    {
        /*juce::AudioPlayHead::CurrentPositionInfo thePositionInfo;*/
        getPlayHead()->getCurrentPosition(thePositionInfo);
        //ownTransportSource.getCurrentPosition(thePositionInfo);
        
        if (numTracks.load() > 0)
        {
            
            // The MIDI file is played only when the transport is active
            // TODO: JOELwindows7: point of transport override. add ignore transport and use own transport
            if (useOwnTransportInstead) {
                if (ownIsPlaying) {
                    // playing
                    const juce::MidiMessageSequence* theSequence = theMIDIFile.getTrack(currentTrack.load());

                    ownOffsetTime = fmod(ownStartTime, traverseEndTime);
                    ownStartTime = thePositionInfo.timeInSeconds - ownOffsetTime;
                    ownElapsedTime += 0;
                }
                else {
                    // paused or maybe stop
                    // add offset by frame time!
                    ownOffsetTime = thePositionInfo.timeInSeconds;
                }

                //oldeh
                /*
                if (Timer::isTimerRunning()) {
                    const juce::MidiMessageSequence* theSequence = theMIDIFile.getTrack(currentTrack.load());

                    //auto startTime = ownTransportSource.getCurrentPosition();
                    auto startTime = ownStartTime * 1000;
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
                } */
                // end oldeh
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
                    //auto endTime = startTime + buffer.getNumSamples() / getSampleRate();

                    //JOELwindows7: adissu's loop land offset.
                    // https://forum.juce.com/t/how-to-loop-midi-file/33837/10?u=joelwindows7
                    double loopOffset = fmod(startTime, traverseEndTime); // do repull here instead?
                    loop = startTime - loopOffset;
                    auto sampleStartTime = startTime - (doLoop? loop: 0.0);

                    // JOELwindows7: abisu reseton
                    if (lastSampleStartTime > sampleStartTime)
                    {
                        sampleStartTime = 0.0; // set to 0 if new loop starts
                        tellLoopPull = false;
                    }

                    lastSampleStartTime = sampleStartTime;
                    auto sampleEndTime = sampleStartTime + buffer.getNumSamples() / getSampleRate();
                    auto sampleLength = 1.0 / getSampleRate(); // sample length is here!

                    // If the transport bar position has been moved by the user or because of looping
                    //if (std::abs(startTime - nextStartTime) > sampleLength && nextStartTime > 0.0)
                    if (std::abs(sampleStartTime - nextStartTime) > sampleLength && nextStartTime > 0.0)
                        sendAllNotesOff(midiMessages);

                    //nextStartTime = endTime;
                    nextStartTime = sampleEndTime;

                    //JOELwindows7: now use 2 different modes. PAIN IS TEMPORARY, GLORY IS FOREVER
                    // If the MIDI file doesn't contain any event anymore
                    if (isPlayingSomething && sampleStartTime >= traverseEndTime)
                        sendAllNotesOff(midiMessages);
                    else
                    {
                        // Called when the user changes the track during playback
                        if (trackHasChanged)
                        {
                            trackHasChanged = false;
                            // but this time don't send all note off!
                            //nvm here you go
                            if (!useEntireTracks)
                                sendAllNotesOff(midiMessages);
                        }
                        int curTranspose = transpose, lastTranspose = transpose; //JOELwindows7: adissu had this.

                        for (int i = 0; i < (useEntireTracks? numTracks.load() : 1); i++) {
                            // copy playback from bellow
                            for (auto j = 0; j < (useEntireTracks? entireSequences[i]->getNumEvents() : theSequence->getNumEvents()); j++) {
                                juce::MidiMessageSequence::MidiEventHolder* event = useEntireTracks? entireSequences[i]->getEventPointer(j) : theSequence->getEventPointer(j);

                                //if (event->message.getTimeStamp() >= startTime && event->message.getTimeStamp() < endTime)
                                if (event->message.getTimeStamp() >= sampleStartTime && event->message.getTimeStamp() < sampleEndTime)
                                {
                                    //auto samplePosition = juce::roundToInt((event->message.getTimeStamp() - startTime) * getSampleRate());
                                    auto samplePosition = juce::roundToInt((event->message.getTimeStamp() - sampleStartTime) * getSampleRate());
                                    midiMessages.addEvent(event->message, samplePosition);
                                    insertMessageLog(juce::String(samplePosition) + "\t\t -> " + juce::String(event->message.getDescription()));
                                    if (event->message.isTextMetaEvent())
                                        insertLyricLog(event->message.getTextFromTextMetaEvent());
                                    // help, this is laggy! I need to off buffer it somehow.

                                    //JOELwindows7: adissu workaround loop 1st element avoid
                                    /* to avoid that the first element of the next loop will be missed because it has to be sent in the same time frame, send it in the same time frame.
                                    Needs to be improved:
                                    - only send the first event, if it really is part of the same time frame
                                    - could also be more the one event.
                                    */
                                    //if ((fmod(startTime, traverseEndTime) > fmod(sampleEndTime, traverseEndTime)) && thePositionInfo.timeInSeconds != 0)
                                    if (fmod(startTime, traverseEndTime) > fmod(sampleEndTime, traverseEndTime))
                                    {
                                        juce::MidiMessageSequence::MidiEventHolder event2 = useEntireTracks? *entireSequences[i]->getEventPointer(0) : *theSequence->getEventPointer(0);
                                        auto samplePosition = juce::roundToInt((event2.message.getTimeStamp()) * getSampleRate());
                                        midiMessages.addEvent(event2.message, samplePosition);
                                    }

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
    /*
    else if (useOwnTransportInstead) {
        //JOELwindows7: if using own transport instead.
        if (Timer::isTimerRunning()) {
            const juce::MidiMessageSequence* theSequence = theMIDIFile.getTrack(currentTrack.load());

            //auto startTime = ownTransportSource.getCurrentPosition();
            auto startTime = ownStartTime * 1000;
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
    }
    */
    else
    {
        // If we have just opened a MIDI file with no content
        if (isPlayingSomething)
            sendAllNotesOff(midiMessages);        
    }

    // JOELwindows7: insert all info here
    fillYourInfoHere = "Perkedel IvanC MIDI Player\n";
    fillYourInfoHere += ("\nYeah\n");
    fillYourInfoHere += ("Play status = " + juce::String(isPlayingSomething ? "PLAYING" : "STOPPED") + "\n");
    //fillYourInfoHere += ("Positions = "+ juce::String(thePositionInfo.timeInSeconds)+"\n");
    fillYourInfoHere += "MIDI file = "+ lastFilePath +"\n";
    fillYourInfoHere += "Using Own Transport = "+ juce::String(useOwnTransportInstead ? "YES" : "NO") + "\n";
    fillYourInfoHere += "Using Entire Track = "+ juce::String(useEntireTracks ? "YES" : "NO") + "\n";
    fillYourInfoHere += "Total Tracks = " + juce::String(numTracks.load()) + "\n";
    fillYourInfoHere += "Chosen Track = "+ juce::String(currentTrack.load()) + "\n";
    //fillYourInfoHere += "Timer is running = "+ juce::String(Timer::isTimerRunning() ? "YES" : "NO") + "\n";
    //fillYourInfoHere += "Own Start Time = "+ juce::String(ownStartTime) + "\n";
    //fillYourInfoHere += "Last Sample Start Time = "+ juce::String(lastSampleStartTime) + "\n";
    //fillYourInfoHere += "Next Start Time = "+ juce::String(nextStartTime) + "\n";
    fillYourInfoHere += "Total End time = "+ juce::String(traverseEndTime) + "\n";
    fillYourInfoHere += "Radio button selected = " + juce::String(tellInfoModes) + "\n";

    fillYourTimerHere = "Playhead Time \t\t= " + juce::String(thePositionInfo.timeInSeconds) + "\nSample Start Time \t\t= " + juce::String(lastSampleStartTime) + " / " + juce::String(traverseEndTime);

    //if(editor != nullptr)
        //editor->setInfoLabelText(fillYourInfoHere);
    /*if (editorRef != NULL)
        editorRef.setInfoLabelText(fillYourInfoHere);*/

    //JOELwindows7: damn it!! how do I juce::String thiser = switch(){default:break;}; bla bla bla?!??!?!
    juce::String yoWhatToShow = "";
    switch (tellInfoModes) {
    case 0:
        yoWhatToShow = fillYourInfoHere;
        break;
    case 1:
        yoWhatToShow = fillYourMessageHere;
        break;
    case 2:
        yoWhatToShow = fillYourLyricHere;
        break;
    default:
        yoWhatToShow = fillYourInfoHere;
        break;
    }

    if(tellInfoModes == 0)
        daInfoTextBox->setText(yoWhatToShow, juce::dontSendNotification); // Finally, I hope this works!
    daTimerLabel->setText(fillYourTimerHere, juce::dontSendNotification); // also don't hog up! use smaller text label!
    // This is inefficient & heavy
}

//==============================================================================
bool SimpleMidiplayerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SimpleMidiplayerAudioProcessor::createEditor()
{
    //editor = new SimpleMidiplayerAudioProcessorEditor(*this); //globalize editor instance!!!
    //return editor;
    //return editorRef;
    //return new SimpleMidiplayerAudioProcessorEditor(*this);
    return new SimpleMidiplayerAudioProcessorEditor(*this, thisWindowThingy);
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
    // JOELwindows7: fill last filename!
    //lastFilePath = theStream.getFile().getFullPathName(); // No, there are Hololive YouTubers. what if their user account name
    // got leaked online??!
    lastFilePath = theStream.getFile().getFileName(); //Yeah, this is better, but big cavea.. idk. nvm.

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
    traverseEndTime = theMIDIFile.getLastTimestamp() + (doSpacer? 3.00 : 0.00); // AH PECKING FOUND IT!!! THE LENGTH OF MIDI FILE!!!
    haveBeenSpaced = doSpacer;
    totalNumEvents = 0; // reset num events total
    fillYourMessageHere = "MIDI file = " + lastFilePath;
    fillYourLyricHere = "\n===========================\n" + lastFilePath + "\n===========================\n\n";
    pressRadioButtonings(tellInfoModes); // I think this is how to refresh the text box??
    //entireSequences.clear();
    //help how do I clear all array in const!!!???
    //for (int i = 0; i < 15; i++)
    //{
    //    //entireSequences[i] = NULL;
    //}

    // JOELwindows7: Now fill all of the tracks!
    for (int i = 0; i < numTracks.load(); i++)
    {
        entireSequences[i] = theMIDIFile.getTrack(i);
        totalNumEvents += entireSequences[i]->getNumEvents();
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
    //wait, that's a value. put that in addEvent on that midiMessages!!!

    tellWorkaroundFirst = false;
}

//JOELwindows7: press play button
void SimpleMidiplayerAudioProcessor::pressPlayPauseButton() {
    //const juce::ScopedLock myScopedLock(processLock);
    if (useOwnTransportInstead) {
        /*if (ownTransportSource.isPlaying()) {

        }
        else {
            ownTransportSource.start();
        }*/
        if (Timer::isTimerRunning())
        {

        }
        else {
            printf("Play lah!");
            DBG("Play lah!");
            //startTimer(1);
        }
    }
    tellPlayNow = true;

    //Just pull it up!
    tellLoopPull = true;
}

//JOELwindows7: press stop button
void SimpleMidiplayerAudioProcessor::pressStopButton() {
    //const juce::ScopedLock myScopedLock(processLock);
    if (useOwnTransportInstead) {
        //ownTransportSource.stop();
        //ownTransportSource.setPosition(0);
        stopTimer();
    }
    tellStopNow = true;
    tellLoopPull = false;
}

//JOELwindows7: panic button
void SimpleMidiplayerAudioProcessor::pressPanicButton() {
    tellPanic = true;
}

//JOELwindows7: clear log button
void SimpleMidiplayerAudioProcessor::pressClearLogButton() {
    fillYourInfoHere.clear();
    fillYourLyricHere.clear();
    fillYourMessageHere.clear();

    daInfoTextBox->clear();
}

void SimpleMidiplayerAudioProcessor::pressAllTracksCheckBox(bool stateNow) {
    useEntireTracks = stateNow;
    //sendAllNotesOff(midiMessages);
}

void SimpleMidiplayerAudioProcessor::pressOwnTransportCheckBox(bool stateNow) {
    useOwnTransportInstead = stateNow;
    //sendAllNotesOff(midiMessages);
}

void SimpleMidiplayerAudioProcessor::pressLoopCheckBox(bool stateNow) {
    doLoop = stateNow;
    tellLoopPull = doLoop;
    //sendAllNotesOff(midiMessages);
}

void SimpleMidiplayerAudioProcessor::pressSpacerCheckBox(bool stateNow) {
    doSpacer = stateNow;
    //traverseEndTime = doSpacer ? traverseEndTime + 3.00 : traverseEndTime;
    if (haveBeenSpaced)
        traverseEndTime = doSpacer ? traverseEndTime - 3 : traverseEndTime; // if has been spaced, remove spacer if haven't already
    else
        traverseEndTime = doSpacer ? traverseEndTime + 3 : traverseEndTime; // if not been spaced, add spacer if haven't already
    haveBeenSpaced = doSpacer; // re update last have been spaced.
    //sendAllNotesOff(midiMessages);
}

void SimpleMidiplayerAudioProcessor::pressRadioButtonings(int WhichPressed)
{
    DBG("Pressed" + WhichPressed);
    switch (WhichPressed) {
    case 0:
        daInfoTextBox->setText(fillYourInfoHere, juce::dontSendNotification);
        break;
    case 1:
        daInfoTextBox->setText(fillYourMessageHere, juce::dontSendNotification);
        break;
    case 2:
        daInfoTextBox->setText(fillYourLyricHere, juce::dontSendNotification);
        break;
    default:
        daInfoTextBox->setText(fillYourInfoHere, juce::dontSendNotification);
        break;
    }
    daInfoTextBox->setCaretPosition(daInfoTextBox->getText().length());
}

bool SimpleMidiplayerAudioProcessor::getUseEntireTracks() {
    return useEntireTracks;
}

bool SimpleMidiplayerAudioProcessor::getUseOwnTransport() {
    return useOwnTransportInstead;
}

bool SimpleMidiplayerAudioProcessor::getDoLoop() {
    return doLoop;
}

bool SimpleMidiplayerAudioProcessor::getDoSpacer() {
    return doSpacer;
}

int SimpleMidiplayerAudioProcessor::getNumTracks()
{
    return numTracks.load();
}

//juce::OwnedArray<juce::TextButton> SimpleMidiplayerAudioProcessor::getRadioButtonings()
//{
//    return radioButtonings;
//}

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
    tellLoopPull = false;
}

//JOELwindows7: da callback from Midi Message Tutorial, PIP header number 2
void SimpleMidiplayerAudioProcessor::timerCallback()
{
    /*
    if (useOwnTransportInstead) {
        if (useEntireTracks)
        {
            if (!daMidiBuffer.isEmpty()) {
                const juce::MidiMessageSequence* theSequence = theMIDIFile.getTrack(currentTrack.load());

                //auto startTime = ownTransportSource.getCurrentPosition();
                auto startTime = ownStartTime * 1000;
                auto endTime = startTime + daAudioBuffer.getNumSamples() / getSampleRate();
                auto sampleLength = 1.0 / getSampleRate();

                // If the transport bar position has been moved by the user or because of looping
                if (std::abs(startTime - nextStartTime) > sampleLength && nextStartTime > 0.0)
                    sendAllNotesOff(daMidiBuffer);

                nextStartTime = endTime;

                //JOELwindows7: now use 2 different modes
                if (useEntireTracks)
                {
                    // If the MIDI file doesn't contain any event anymore
                    if (isPlayingSomething && startTime >= traverseEndTime)
                        sendAllNotesOff(daMidiBuffer);
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
                                    daMidiBuffer.addEvent(event->message, samplePosition);

                                    isPlayingSomething = true;
                                }
                            }
                        }
                    }
                }
                else {
                    // If the MIDI file doesn't contain any event anymore
                    if (isPlayingSomething && startTime >= theSequence->getEndTime())
                        sendAllNotesOff(daMidiBuffer);

                    else
                    {
                        // Called when the user changes the track during playback
                        if (trackHasChanged)
                        {
                            trackHasChanged = false;
                            sendAllNotesOff(daMidiBuffer);
                        }

                        // Iterating through the MIDI file contents and trying to find an event that
                        // needs to be called in the current time frame
                        for (auto i = 0; i < theSequence->getNumEvents(); i++)
                        {
                            juce::MidiMessageSequence::MidiEventHolder* event = theSequence->getEventPointer(i);

                            if (event->message.getTimeStamp() >= startTime && event->message.getTimeStamp() < endTime)
                            {
                                auto samplePosition = juce::roundToInt((event->message.getTimeStamp() - startTime) * getSampleRate());
                                daMidiBuffer.addEvent(event->message, samplePosition);

                                isPlayingSomething = true;
                            }
                        }
                    }
                }
            }
        }
    }
    */

    ownElapsedTime++;
}

//JOELwindows7: handover the label
//void SimpleMidiplayerAudioProcessor::handoverInfoLabel(juce::Label& thing) {
//    giveMeInfoLabel = thing;
//}

//JOELwindows7: screw this
juce::String SimpleMidiplayerAudioProcessor::getFillYourInfoHere() {
    return fillYourInfoHere;
}

//JOELwindows7: attempt to have more return type of this. WIndow thingy
juce::ScopedPointer<juce::Component> SimpleMidiplayerAudioProcessor::getThisWindowThingy()
{
    return thisWindowThingy;
}

//JOELwindows7: rosshoyt style countered MIDI play thread
//void SimpleMidiplayerAudioProcessor::threadenOwnPlayMidi() {
//    int numTrackEvents = totalNumEvents;
//    int i = 0;
//    juce::SortedSet<int> channelNoteMap;
//    //std::vector<MidiMessage*> channelNoteMap;
//    //std::unordered_multimap<int, int> channelMap;
//    //ChannelNoteMap channelNoteMap;
//    bool sustainOn = false;
//    while (i < numTrackEvents && !threadShouldExit())
//    {
//        
//        i++;
//    }
//    DBG("Closing Play() thread");
//}
//
//void SimpleMidiplayerAudioProcessor::stopThreadenOwnPlayMidi() {
//    DBG("Stopping MidiFilePlayer");
//    stopThread(20);
//    //keyboardState.allNotesOff(1);
//}

//JOELwindows7: da insert message logs
juce::String SimpleMidiplayerAudioProcessor::insertMessageLog(juce::String whatToAppend)
{
    fillYourMessageHere << juce::String(whatToAppend) << "\n"; // hehe C++ way of shift insertion.
    //fillYourMessageHere += juce::String(whatToAppend) + "\n"; // NO! it doesn't work properly! wait no, it was the caret positioner

    //insert at caret position like JUCE MIDI IN / OUT demo. handle async update
    if (tellInfoModes == 1)
        daInfoTextBox->insertTextAtCaret("\n" + juce::String(whatToAppend));

    return whatToAppend;
}

juce::String SimpleMidiplayerAudioProcessor::insertLyricLog(juce::String syllable)
{
    fillYourLyricHere << syllable;
    //fillYourLyricHere += syllable;

    if (tellInfoModes == 2)
        daInfoTextBox->insertTextAtCaret(syllable);

    return syllable;
}