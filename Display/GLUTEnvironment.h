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

#include <Logging/Logger.h>

namespace OpenEngine {
namespace Display {

/**
 * Short description.
 *
 * @class GLUTEnvironment GLUTEnvironment.h ons/GLUT/Display/GLUTEnvironment.h
 */
class GLUTEnvironment : public IEnvironment {
private:
    // default values
    int w, h, d;
    FrameOption o;
    // GLUTFrame* frame;
    Devices::GLUTInput* input;

    list<GLUTFrame*> frames;

public:
   
    GLUTEnvironment(int w,int h,int d=32,FrameOption options = FrameOption())
        : w(w), h(h), d(d), o(options)
    {
        // Meta setup?
        // frame = new GLUTFrame(w,h,d,options);
        input = new Devices::GLUTInput();
    }
 

    void Handle(Core::InitializeEventArg arg) {
        list<GLUTFrame*>::iterator i = frames.begin();
        for (; i != frames.end(); ++i) {
            (*i)->Handle(arg);
        }
        input->Handle(arg);
    }
    void Handle(Core::ProcessEventArg arg) {
        list<GLUTFrame*>::iterator i = frames.begin();
        for (; i != frames.end(); ++i)
            (*i)->Handle(arg);
        input->Handle(arg);
    }
    void Handle(Core::DeinitializeEventArg arg) {
        list<GLUTFrame*>::iterator i = frames.begin();
        for (; i != frames.end(); ++i)
            (*i)->Handle(arg);
        input->Handle(arg);
    }

    IFrame& CreateFrame() { GLUTFrame* f = new GLUTFrame(w, h, d, o); frames.push_back(f); return *f; }
    Devices::IMouse*    GetMouse()    { return input; }
    Devices::IKeyboard* GetKeyboard() { return input; }
    Devices::IJoystick* GetJoystick() { return input; }


};

} // NS Display
} // NS OpenEngine

#endif
