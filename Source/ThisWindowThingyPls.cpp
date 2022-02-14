/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "ThisWindowThingyPls.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ThisWindowThingyPls::ThisWindowThingyPls ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    juce__textButton.reset (new juce::TextButton ("PlayButton"));
    addAndMakeVisible (juce__textButton.get());
    juce__textButton->setButtonText (TRANS("Play"));
    juce__textButton->setConnectedEdges (juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight | juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    juce__textButton->addListener (this);

    juce__textButton->setBounds (16, 64, 150, 24);

    juce__textButton2.reset (new juce::TextButton ("StopButton"));
    addAndMakeVisible (juce__textButton2.get());
    juce__textButton2->setTooltip (TRANS("Stop"));
    juce__textButton2->setButtonText (TRANS("Stop"));
    juce__textButton2->setConnectedEdges (juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    juce__textButton2->addListener (this);

    juce__textButton2->setBounds (176, 64, 150, 24);

    juce__textButton3.reset (new juce::TextButton ("LoadFileButton"));
    addAndMakeVisible (juce__textButton3.get());
    juce__textButton3->setTooltip (TRANS("Load a MIDI file"));
    juce__textButton3->setButtonText (TRANS("Load MIDI File"));
    juce__textButton3->setConnectedEdges (juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    juce__textButton3->addListener (this);

    juce__textButton3->setBounds (16, 32, 150, 24);

    juce__toggleButton.reset (new juce::ToggleButton ("EntireTrackCheck"));
    addAndMakeVisible (juce__toggleButton.get());
    juce__toggleButton->setButtonText (TRANS("Entire Tracks"));
    juce__toggleButton->setConnectedEdges (juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnBottom);
    juce__toggleButton->addListener (this);
    juce__toggleButton->setToggleState (true, juce::dontSendNotification);

    juce__toggleButton->setBounds (16, 96, 150, 24);

    juce__toggleButton2.reset (new juce::ToggleButton ("OwnTransportCheck"));
    addAndMakeVisible (juce__toggleButton2.get());
    juce__toggleButton2->setButtonText (TRANS("Override Host\'s PlayHead"));
    juce__toggleButton2->setConnectedEdges (juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnBottom);
    juce__toggleButton2->addListener (this);

    juce__toggleButton2->setBounds (176, 96, 150, 24);

    juce__comboBox.reset (new juce::ComboBox ("TracksCombo"));
    addAndMakeVisible (juce__comboBox.get());
    juce__comboBox->setTooltip (TRANS("Select Track to play"));
    juce__comboBox->setEditableText (false);
    juce__comboBox->setJustificationType (juce::Justification::centredLeft);
    juce__comboBox->setTextWhenNothingSelected (TRANS("Tracks"));
    juce__comboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    juce__comboBox->addListener (this);

    juce__comboBox->setBounds (16, 128, 304, 24);

    juce__textEditor.reset (new juce::TextEditor ("StatusTextEdit"));
    addAndMakeVisible (juce__textEditor.get());
    juce__textEditor->setMultiLine (true);
    juce__textEditor->setReturnKeyStartsNewLine (true);
    juce__textEditor->setReadOnly (true);
    juce__textEditor->setScrollbarsShown (true);
    juce__textEditor->setCaretVisible (false);
    juce__textEditor->setPopupMenuEnabled (true);
    juce__textEditor->setText (TRANS("Hello World\n"));

    juce__textEditor->setBounds (16, 168, 304, 328);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ThisWindowThingyPls::~ThisWindowThingyPls()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    juce__textButton = nullptr;
    juce__textButton2 = nullptr;
    juce__textButton3 = nullptr;
    juce__toggleButton = nullptr;
    juce__toggleButton2 = nullptr;
    juce__comboBox = nullptr;
    juce__textEditor = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ThisWindowThingyPls::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ThisWindowThingyPls::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ThisWindowThingyPls::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == juce__textButton.get())
    {
        //[UserButtonCode_juce__textButton] -- add your button handler code here..
        //[/UserButtonCode_juce__textButton]
    }
    else if (buttonThatWasClicked == juce__textButton2.get())
    {
        //[UserButtonCode_juce__textButton2] -- add your button handler code here..
        //[/UserButtonCode_juce__textButton2]
    }
    else if (buttonThatWasClicked == juce__textButton3.get())
    {
        //[UserButtonCode_juce__textButton3] -- add your button handler code here..
        //[/UserButtonCode_juce__textButton3]
    }
    else if (buttonThatWasClicked == juce__toggleButton.get())
    {
        //[UserButtonCode_juce__toggleButton] -- add your button handler code here..
        //[/UserButtonCode_juce__toggleButton]
    }
    else if (buttonThatWasClicked == juce__toggleButton2.get())
    {
        //[UserButtonCode_juce__toggleButton2] -- add your button handler code here..
        //[/UserButtonCode_juce__toggleButton2]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void ThisWindowThingyPls::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == juce__comboBox.get())
    {
        //[UserComboBoxCode_juce__comboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_juce__comboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void ThisWindowThingyPls::visibilityChanged()
{
    //[UserCode_visibilityChanged] -- Add your code here...
    //[/UserCode_visibilityChanged]
}

void ThisWindowThingyPls::moved()
{
    //[UserCode_moved] -- Add your code here...
    //[/UserCode_moved]
}

void ThisWindowThingyPls::parentHierarchyChanged()
{
    //[UserCode_parentHierarchyChanged] -- Add your code here...
    //[/UserCode_parentHierarchyChanged]
}

void ThisWindowThingyPls::parentSizeChanged()
{
    //[UserCode_parentSizeChanged] -- Add your code here...
    //[/UserCode_parentSizeChanged]
}

void ThisWindowThingyPls::lookAndFeelChanged()
{
    //[UserCode_lookAndFeelChanged] -- Add your code here...
    //[/UserCode_lookAndFeelChanged]
}

bool ThisWindowThingyPls::hitTest (int x, int y)
{
    //[UserCode_hitTest] -- Add your code here...
    return true;
    //[/UserCode_hitTest]
}

void ThisWindowThingyPls::broughtToFront()
{
    //[UserCode_broughtToFront] -- Add your code here...
    //[/UserCode_broughtToFront]
}

void ThisWindowThingyPls::filesDropped (const juce::StringArray& filenames, int mouseX, int mouseY)
{
    //[UserCode_filesDropped] -- Add your code here...
    //[/UserCode_filesDropped]
}

void ThisWindowThingyPls::handleCommandMessage (int commandId)
{
    //[UserCode_handleCommandMessage] -- Add your code here...
    //[/UserCode_handleCommandMessage]
}

void ThisWindowThingyPls::childrenChanged()
{
    //[UserCode_childrenChanged] -- Add your code here...
    //[/UserCode_childrenChanged]
}

void ThisWindowThingyPls::enablementChanged()
{
    //[UserCode_enablementChanged] -- Add your code here...
    //[/UserCode_enablementChanged]
}

void ThisWindowThingyPls::mouseMove (const juce::MouseEvent& e)
{
    //[UserCode_mouseMove] -- Add your code here...
    //[/UserCode_mouseMove]
}

void ThisWindowThingyPls::mouseEnter (const juce::MouseEvent& e)
{
    //[UserCode_mouseEnter] -- Add your code here...
    //[/UserCode_mouseEnter]
}

void ThisWindowThingyPls::mouseExit (const juce::MouseEvent& e)
{
    //[UserCode_mouseExit] -- Add your code here...
    //[/UserCode_mouseExit]
}

void ThisWindowThingyPls::mouseDown (const juce::MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    //[/UserCode_mouseDown]
}

void ThisWindowThingyPls::mouseDrag (const juce::MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
    //[/UserCode_mouseDrag]
}

void ThisWindowThingyPls::mouseUp (const juce::MouseEvent& e)
{
    //[UserCode_mouseUp] -- Add your code here...
    //[/UserCode_mouseUp]
}

void ThisWindowThingyPls::mouseDoubleClick (const juce::MouseEvent& e)
{
    //[UserCode_mouseDoubleClick] -- Add your code here...
    //[/UserCode_mouseDoubleClick]
}

void ThisWindowThingyPls::mouseWheelMove (const juce::MouseEvent& e, const juce::MouseWheelDetails& wheel)
{
    //[UserCode_mouseWheelMove] -- Add your code here...
    //[/UserCode_mouseWheelMove]
}

bool ThisWindowThingyPls::keyPressed (const juce::KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyPressed]
}

bool ThisWindowThingyPls::keyStateChanged (bool isKeyDown)
{
    //[UserCode_keyStateChanged] -- Add your code here...
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyStateChanged]
}

void ThisWindowThingyPls::modifierKeysChanged (const juce::ModifierKeys& modifiers)
{
    //[UserCode_modifierKeysChanged] -- Add your code here...
    //[/UserCode_modifierKeysChanged]
}

void ThisWindowThingyPls::focusGained (FocusChangeType cause)
{
    //[UserCode_focusGained] -- Add your code here...
    //[/UserCode_focusGained]
}

void ThisWindowThingyPls::focusLost (FocusChangeType cause)
{
    //[UserCode_focusLost] -- Add your code here...
    //[/UserCode_focusLost]
}

void ThisWindowThingyPls::focusOfChildComponentChanged (FocusChangeType cause)
{
    //[UserCode_focusOfChildComponentChanged] -- Add your code here...
    //[/UserCode_focusOfChildComponentChanged]
}

void ThisWindowThingyPls::inputAttemptWhenModal()
{
    //[UserCode_inputAttemptWhenModal] -- Add your code here...
    //[/UserCode_inputAttemptWhenModal]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ThisWindowThingyPls" componentName=""
                 parentClasses="public juce::Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <METHODS>
    <METHOD name="visibilityChanged()"/>
    <METHOD name="moved()"/>
    <METHOD name="parentHierarchyChanged()"/>
    <METHOD name="parentSizeChanged()"/>
    <METHOD name="lookAndFeelChanged()"/>
    <METHOD name="hitTest (int x, int y)"/>
    <METHOD name="broughtToFront()"/>
    <METHOD name="filesDropped (const juce::StringArray&amp; filenames, int mouseX, int mouseY)"/>
    <METHOD name="handleCommandMessage (int commandId)"/>
    <METHOD name="childrenChanged()"/>
    <METHOD name="enablementChanged()"/>
    <METHOD name="mouseMove (const juce::MouseEvent&amp; e)"/>
    <METHOD name="mouseEnter (const juce::MouseEvent&amp; e)"/>
    <METHOD name="mouseExit (const juce::MouseEvent&amp; e)"/>
    <METHOD name="mouseDown (const juce::MouseEvent&amp; e)"/>
    <METHOD name="mouseDrag (const juce::MouseEvent&amp; e)"/>
    <METHOD name="mouseUp (const juce::MouseEvent&amp; e)"/>
    <METHOD name="mouseDoubleClick (const juce::MouseEvent&amp; e)"/>
    <METHOD name="mouseWheelMove (const juce::MouseEvent&amp; e, const juce::MouseWheelDetails&amp; wheel)"/>
    <METHOD name="keyPressed (const juce::KeyPress&amp; key)"/>
    <METHOD name="keyStateChanged (bool isKeyDown)"/>
    <METHOD name="modifierKeysChanged (const juce::ModifierKeys&amp; modifiers)"/>
    <METHOD name="focusGained (FocusChangeType cause)"/>
    <METHOD name="focusLost (FocusChangeType cause)"/>
    <METHOD name="focusOfChildComponentChanged (FocusChangeType cause)"/>
    <METHOD name="inputAttemptWhenModal()"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff323e44"/>
  <TEXTBUTTON name="PlayButton" id="18f226847460574c" memberName="juce__textButton"
              virtualName="" explicitFocusOrder="0" pos="16 64 150 24" buttonText="Play"
              connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="StopButton" id="fad637526056a815" memberName="juce__textButton2"
              virtualName="" explicitFocusOrder="0" pos="176 64 150 24" tooltip="Stop"
              buttonText="Stop" connectedEdges="13" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="LoadFileButton" id="84778581d625cb8f" memberName="juce__textButton3"
              virtualName="" explicitFocusOrder="0" pos="16 32 150 24" tooltip="Load a MIDI file"
              buttonText="Load MIDI File" connectedEdges="12" needsCallback="1"
              radioGroupId="0"/>
  <TOGGLEBUTTON name="EntireTrackCheck" id="6f47d113c51a74c0" memberName="juce__toggleButton"
                virtualName="" explicitFocusOrder="0" pos="16 96 150 24" buttonText="Entire Tracks"
                connectedEdges="9" needsCallback="1" radioGroupId="0" state="1"/>
  <TOGGLEBUTTON name="OwnTransportCheck" id="63e4392b21ed02a8" memberName="juce__toggleButton2"
                virtualName="" explicitFocusOrder="0" pos="176 96 150 24" buttonText="Override Host's PlayHead"
                connectedEdges="9" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="TracksCombo" id="3d32cea78c2e0d4c" memberName="juce__comboBox"
            virtualName="" explicitFocusOrder="0" pos="16 128 304 24" tooltip="Select Track to play"
            editable="0" layout="33" items="" textWhenNonSelected="Tracks"
            textWhenNoItems="(no choices)"/>
  <TEXTEDITOR name="StatusTextEdit" id="302b1f7a6e4b35f" memberName="juce__textEditor"
              virtualName="" explicitFocusOrder="0" pos="16 168 304 328" initialText="Hello World&#10;"
              multiline="1" retKeyStartsLine="1" readonly="1" scrollbars="1"
              caret="0" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

