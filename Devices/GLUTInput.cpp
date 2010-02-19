// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Devices/GLUTInput.h>
#include <Meta/GLUT.h>
#include <Logging/Logger.h>

namespace OpenEngine {
namespace Devices {

using Core::Event;
using Core::InitializeEventArg;
using Core::ProcessEventArg;
using Core::DeinitializeEventArg;

static GLUTInput* input;

Key specialToKey(unsigned int s) {
    switch (s) {
    case GLUT_KEY_UP: return KEY_UP;
    case GLUT_KEY_DOWN: return KEY_DOWN;
    case GLUT_KEY_LEFT: return KEY_LEFT;
    case GLUT_KEY_RIGHT: return KEY_RIGHT;
        
    }
    return KEY_LAST;
}

void specialKeyDown(int key, int x, int y) {
    // TODO, this call is repeated.
    
    if (input) {
        KeyboardEventArg arg;
        arg.type = EVENT_PRESS;
        arg.sym = specialToKey(key);
        
        input->KeyEvent().Notify(arg);
    }
}

void specialKeyUp(int key, int x, int y) {
    if (input) {
        KeyboardEventArg arg;
        arg.type = EVENT_RELEASE;
        arg.sym = specialToKey(key);

        input->KeyEvent().Notify(arg);
    }
}


void keyDown(unsigned char key, int x, int y) {
    // TODO, this call is repeated.
    
    if (input) {
        KeyboardEventArg arg;
        arg.type = EVENT_PRESS;
        arg.sym = (Key)key;
        
        input->KeyEvent().Notify(arg);
    }
}

void keyUp(unsigned char key, int x, int y) {
    if (input) {
        KeyboardEventArg arg;
        arg.type = EVENT_RELEASE;
        arg.sym = (Key)key;

        input->KeyEvent().Notify(arg);
    }
}


void mouseDown(int btn, int st, int x, int y) {
    if (input) {
        MouseButtonEventArg arg;
        arg.type = (st == GLUT_DOWN)?EVENT_PRESS:EVENT_RELEASE;

        switch(btn) {
        case GLUT_LEFT_BUTTON: arg.button = BUTTON_LEFT; break;
        case GLUT_RIGHT_BUTTON: arg.button = BUTTON_RIGHT; break;
        case GLUT_MIDDLE_BUTTON: arg.button = BUTTON_MIDDLE; break;            
        }

        if (st == GLUT_DOWN)
            input->state.buttons = MouseButton(input->state.buttons | arg.button); // Set
        else 
            input->state.buttons = MouseButton(input->state.buttons & ~arg.button); // Unset


        input->MouseButtonEvent().Notify(arg);        

    }
}
void mouseMove(int x, int y) {
    if (input) {                
        MouseMovedEventArg arg;
        
        arg.x = x;
        arg.y = y;

        arg.dx = input->state.x - x;        
        arg.dy = input->state.y - y;        

        
        input->state.x = x;
        input->state.y = y;

        
        arg.buttons = input->state.buttons;

        // We need Dx ad Dy

        input->MouseMovedEvent().Notify(arg);        
    }
}

GLUTInput::GLUTInput()
    : IKeyboard()
    , IMouse()
    , IJoystick() {


}

GLUTInput::~GLUTInput() {}

void GLUTInput::Handle(InitializeEventArg arg) {
    // Move to initialize?
    input = this;
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);

    glutSpecialFunc(specialKeyDown);
    glutSpecialUpFunc(specialKeyUp);


    glutMouseFunc(mouseDown);
    glutPassiveMotionFunc(mouseMove);
    glutMotionFunc(mouseMove);

}
void GLUTInput::Handle(ProcessEventArg arg) {
    keyEvent.Release();
    mouseMovedEvent.Release();
    mouseButtonEvent.Release();

}
void GLUTInput::Handle(DeinitializeEventArg arg) {

}


// Events

IEvent<KeyboardEventArg>& GLUTInput::KeyEvent() {
    return this->keyEvent;
}

IEvent<MouseMovedEventArg>& GLUTInput::MouseMovedEvent() {
    return this->mouseMovedEvent;
}

IEvent<MouseButtonEventArg>& GLUTInput::MouseButtonEvent() {
    return this->mouseButtonEvent;
}

IEvent<JoystickButtonEventArg>& GLUTInput::JoystickButtonEvent() {
    return this->joystickButtonEvent;
}

IEvent<JoystickAxisEventArg>& GLUTInput::JoystickAxisEvent() {
    return this->joystickAxisEvent;
}


// IMouse
void GLUTInput::HideCursor() {
    throw "hide";
}

void GLUTInput::ShowCursor() {
    throw "show";
}

void GLUTInput::SetCursor(int x, int y) {
    throw "set";
}


MouseState GLUTInput::GetState() {
    return state;
}



} // NS Devices
} // NS OpenEngine
