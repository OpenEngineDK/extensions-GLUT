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
    
    Time _time;

    unsigned int approx = 0;
    for (int i=0;i<10;i++) 
        approx += loops[i];
    approx = approx / 10;

    process.Notify(ProcessEventArg(time,approx));
    
    _time = Timer::GetTime();
    loops[index] = (_time - time).AsInt();
    time = _time;

    index = (index + 1) % 10;
    
}

void GLUTEngine::Start() {
    initialize.Notify(InitializeEventArg());

    // Use idle or timer?
    engine = this;
    
    // Ready the approx calculation
    index = 0;
    for (int i=0;i<10;i++) 
        loops[i] = 50;

    time = Timer::GetTime();

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
