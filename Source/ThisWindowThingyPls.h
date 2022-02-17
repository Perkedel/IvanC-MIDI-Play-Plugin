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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ThisWindowThingyPls  : public juce::Component,
                             public juce::Button::Listener,
                             public juce::ComboBox::Listener
{
public:
    //==============================================================================
    ThisWindowThingyPls ();
    ~ThisWindowThingyPls() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void visibilityChanged() override;
    void moved() override;
    void parentHierarchyChanged() override;
    void parentSizeChanged() override;
    void lookAndFeelChanged() override;
    bool hitTest (int x, int y) override;
    void broughtToFront() override;
    void handleCommandMessage (int commandId) override;
    void childrenChanged() override;
    void enablementChanged() override;
    void mouseMove (const juce::MouseEvent& e) override;
    void mouseEnter (const juce::MouseEvent& e) override;
    void mouseExit (const juce::MouseEvent& e) override;
    void mouseDown (const juce::MouseEvent& e) override;
    void mouseDrag (const juce::MouseEvent& e) override;
    void mouseUp (const juce::MouseEvent& e) override;
    void mouseDoubleClick (const juce::MouseEvent& e) override;
    void mouseWheelMove (const juce::MouseEvent& e, const juce::MouseWheelDetails& wheel) override;
    bool keyPressed (const juce::KeyPress& key) override;
    bool keyStateChanged (bool isKeyDown) override;
    void modifierKeysChanged (const juce::ModifierKeys& modifiers) override;
    void focusGained (FocusChangeType cause) override;
    void focusLost (FocusChangeType cause) override;
    void focusOfChildComponentChanged (FocusChangeType cause) override;
    void inputAttemptWhenModal() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::TextButton> juce__textButton;
    std::unique_ptr<juce::TextButton> juce__textButton2;
    std::unique_ptr<juce::TextButton> juce__textButton3;
    std::unique_ptr<juce::ToggleButton> juce__toggleButton;
    std::unique_ptr<juce::ToggleButton> juce__toggleButton2;
    std::unique_ptr<juce::ComboBox> juce__comboBox;
    std::unique_ptr<juce::TextEditor> juce__textEditor;
    std::unique_ptr<juce::ToggleButton> juce__toggleButton3;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ThisWindowThingyPls)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

