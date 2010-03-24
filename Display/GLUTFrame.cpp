// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Display/GLUTFrame.h>
#include <Meta/GLUT.h>
#include <Logging/Logger.h>
#include <sstream>

namespace OpenEngine {
namespace Display {

void display() {
    glutSwapBuffers();
}


GLUTFrame::GLUTFrame(int w,int h,int d,FrameOption opts)
    : IFrame(w,h,d,opts) 
    , width(w)
    , height(h)
    , depth(d)
    , options(FrameOption(opts|FRAME_OPENGL)) {    
}

GLUTFrame::~GLUTFrame() {
}

bool GLUTFrame::IsFocused() const {
    throw "focus";
    return true;
}

unsigned int GLUTFrame::GetWidth() const {
    return width;
}

unsigned int GLUTFrame::GetHeight() const {
    return height;
}

unsigned int GLUTFrame::GetDepth() const {
    return depth;
}

FrameOption GLUTFrame::GetOptions() const {
    return options;
}
bool GLUTFrame::GetOption(const FrameOption option) const {
    return (option & GetOptions()) == option;
}

void GLUTFrame::SetWidth(const int width) {
    //if (!init) this->width = width;
}

void GLUTFrame::SetHeight(const int height) {
    //if (!init) this->height = height;
}

void GLUTFrame::SetDepth(const int depth) {
    //if (!init) this->depth = depth;
}

void GLUTFrame::SetOptions(const FrameOption options) {
    // bool reload = false;
    // if (options != this->options) reload = true;
    // this->options = options;
    // if (init && reload) {
    //     CreateSurface();
    // }
    throw 42;
}

void GLUTFrame::ToggleOption(const FrameOption option) {
    FrameOption opt = FrameOption(options ^ option);
    SetOptions(opt);
}


void GLUTFrame::Handle(InitializeEventArg arg) {
    // Initialize the video frame
    int argc = 1;
    char *argv[] = {"hest"};
    logger.info << "Initialize GLUT" << logger.end;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STEREO); 
    // non-stereo for main window
    
    // glutInitDisplayMode(GLUT_DOUBLE |
    //                     GLUT_RGB |
    //                     GLUT_DEPTH |
    //                     GLUT_STEREO); // non-stereo for main window
    



    if (IsOptionSet(FRAME_FULLSCREEN)) {
            std::ostringstream os;
            os << width << "x" << height << ":" << depth;
            

        glutGameModeString( os.str().c_str());// "1024x768:32@75" ); //the settings     
        glutEnterGameMode();
    } else {
        glutInitWindowSize (width, height);
        glutCreateWindow("GLUTStereo");
    }
        


    glutDisplayFunc(display);


    

    //if (GLUT_Init(GLUT_INIT_VIDEO) < 0 )
    //throw Exception("GLUT_Init: " + string(GLUT_GetError()));

    //CreateSurface();

    // Set the private initialization flag
    //init = true;
    //throw "handle";
}

void GLUTFrame::Handle(ProcessEventArg arg) {
    // Start by flipping the screen which is the
    // result from last engine loop.
    //if (IsOptionSet(FRAME_OPENGL))
    //GLUT_GL_SwapBuffers();
    glutPostRedisplay();
    //throw "process";
}

void GLUTFrame::Handle(DeinitializeEventArg arg) {
    //SDL_QuitSubSystem(SDL_INIT_VIDEO);
    if (IsOptionSet(FRAME_FULLSCREEN))
        glutLeaveGameMode();
}



} // NS Display
} // NS OpenEngine
