// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_GLUT_ENVIRONMENT_H_
#define _OE_GLUT_ENVIRONMENT_H_

#include <Display/IEnvironment.h>

#include <Display/GLUTFrame.h>
#include <Devices/GLUTInput.h>

namespace OpenEngine {
namespace Display {

/**
 * Short description.
 *
 * @class GLUTEnvironment GLUTEnvironment.h ons/GLUT/Display/GLUTEnvironment.h
 */
class GLUTEnvironment : public IEnvironment {
private:

    GLUTFrame* frame;
    Devices::GLUTInput* input;

public:
   
    GLUTEnvironment() {
        // Meta setup?
        
        frame = new GLUTFrame();
        input = new Devices::GLUTInput();
    }
 

    void Handle(Core::InitializeEventArg arg) {
        frame->Handle(arg);
        input->Handle(arg);
    }
    void Handle(Core::ProcessEventArg arg) {
        frame->Handle(arg);
        input->Handle(arg);
    }
    void Handle(Core::DeinitializeEventArg arg) {
        frame->Handle(arg);
        input->Handle(arg);
    }

    IFrame&             GetFrame()    { return *frame; }
    Devices::IMouse*    GetMouse()    { return input; }
    Devices::IKeyboard* GetKeyboard() { return input; }
    Devices::IJoystick* GetJoystick() { return input; }


};

} // NS Display
} // NS OpenEngine

#endif
