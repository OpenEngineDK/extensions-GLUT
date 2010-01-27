// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_GLUT_ENGINE_H_
#define _OE_GLUT_ENGINE_H_

#include <Core/IEngine.h>
#include <Core/IEvent.h>
#include <Core/Event.h>


namespace OpenEngine {
namespace Core {

/**
 * Short description.
 *
 * @class GLUTEngine GLUTEngine.h ons/GLUT/Core/GLUTEngine.h
 */
class GLUTEngine : public IEngine {
private:
    Event<InitializeEventArg>   initialize;
    Event<ProcessEventArg>      process;
    Event<DeinitializeEventArg> deinitialize;

public:
    GLUTEngine();    
    virtual void Start();
    virtual void Stop();
    virtual IEvent<InitializeEventArg>&   InitializeEvent();
    virtual IEvent<ProcessEventArg>&      ProcessEvent();
    virtual IEvent<DeinitializeEventArg>& DeinitializeEvent();

    void Tick();
};

} // NS Core
} // NS OpenEngine

#endif
