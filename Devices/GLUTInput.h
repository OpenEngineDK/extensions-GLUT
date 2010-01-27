// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------
#ifndef _OE_GLUT_INPUT_H_
#define _OE_GLUT_INPUT_H_

#include <Devices/IMouse.h>
#include <Devices/IKeyboard.h>
#include <Devices/IJoystick.h>
#include <Core/QueuedEvent.h>
#include <Core/Event.h>
#include <Core/IModule.h>



namespace OpenEngine {
namespace Devices {

/**
 * Short description.
 *
 * @class GLUTInput GLUTInput.h ons/GLUT/Devices/GLUTInput.h
 */
class GLUTInput 
    : public IKeyboard
    , public IMouse
    , public IJoystick
    , public Core::IModule {
private:


    Core::QueuedEvent<KeyboardEventArg>       keyEvent;
    Core::QueuedEvent<MouseMovedEventArg>     mouseMovedEvent;
    Core::QueuedEvent<MouseButtonEventArg>    mouseButtonEvent;
    Core::Event<JoystickButtonEventArg> joystickButtonEvent;
    Core::Event<JoystickAxisEventArg>   joystickAxisEvent;

public:
    GLUTInput();
    ~GLUTInput();

    // IModule methods
    void Handle(Core::InitializeEventArg arg);
    void Handle(Core::ProcessEventArg arg);
    void Handle(Core::DeinitializeEventArg arg);

    // Event lists
    Core::IEvent<KeyboardEventArg>&       KeyEvent();
    Core::IEvent<MouseMovedEventArg>&     MouseMovedEvent();
    Core::IEvent<MouseButtonEventArg>&    MouseButtonEvent();
    Core::IEvent<JoystickButtonEventArg>& JoystickButtonEvent();
    Core::IEvent<JoystickAxisEventArg>&	  JoystickAxisEvent();

    // IMouse methods
    void HideCursor();
    void ShowCursor();
    void SetCursor(int x, int y);
    MouseState GetState();
    
    // Glut haxx
    MouseState state;
    
};

} // NS Devices
} // NS OpenEngine

#endif
