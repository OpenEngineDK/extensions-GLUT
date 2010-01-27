// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Core/GLUTEngine.h>
#include <Meta/GLUT.h>
#include <Logging/Logger.h>
#include <Utils/Timer.h>

namespace OpenEngine {
namespace Core {

using OpenEngine::Utils::Time;
using OpenEngine::Utils::Timer;

static GLUTEngine* engine = NULL;

void timer(int val) {
    if (engine) {
        engine->Tick();
    }
    glutTimerFunc(1,timer,1); // full speed! (could be changed?)
}

GLUTEngine::GLUTEngine() {
    
}

void GLUTEngine::Tick() {
    Time time = Timer::GetTime();
    
    process.Notify(ProcessEventArg(time,0));

}

void GLUTEngine::Start() {
    initialize.Notify(InitializeEventArg());

    // Use idle or timer?
    engine = this;
    glutTimerFunc(1,timer,1);

    // Lets hope for the best!
    glutMainLoop();
    deinitialize.Notify(DeinitializeEventArg());
}

void GLUTEngine::Stop() {
    // only way to end the glutMainLoop
    exit(0);
}


/**
 * @see IEngine::InitializeEvent()
 */
IEvent<InitializeEventArg>& GLUTEngine::InitializeEvent() {
    return initialize;
}

/**
 * @see IEngine::ProcessEvent()
 */
IEvent<ProcessEventArg>& GLUTEngine::ProcessEvent() {
    return process;
}

/**
 * @see IEngine::DeinitializeEvent()
 */
IEvent<DeinitializeEventArg>& GLUTEngine::DeinitializeEvent() {
    return deinitialize;
}


} // NS Core
} // NS OpenEngine
