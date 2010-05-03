// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Meta/OpenGL.h>

#include <Display/GLUTFrame.h>
#include <Display/ViewingVolume.h>
#include <Display/StereoCamera.h>
#include <Meta/GLUT.h>
#include <Logging/Logger.h>
#include <sstream>
#include <map>


namespace OpenEngine {
namespace Display {

using std::map;

// evil callback hack
static bool glutIsInitialized = false;
static map<int, GLUTFrame*> windows;

void GLUTFrame::display() {
    // logger.info << "window: " << glutGetWindow() << logger.end;
    // glutSwapBuffers();
}

void GLUTFrame::reshape(int w, int h) {
    GLUTFrame* f = windows[glutGetWindow()];
    f->width = w;
    f->height = h;
    ((IListener<Display::ResizeEventArg>*)f->canvas)->Handle(Display::ResizeEventArg(f->fc));
    //    logger.info << "reshape: " << glutGetWindow() << logger.end;
}

GLUTFrame::GLUTFrame(int w,int h,int d,FrameOption opts)
    : canvas(NULL)
    , fc(FrameCanvas(*this))
    , width(w)
    , height(h)
    , depth(d)
    , options(FrameOption(opts|FRAME_OPENGL)) 
    , init(false)
{
}

GLUTFrame::~GLUTFrame() {
}

bool GLUTFrame::IsFocused() const {
    throw "focus";
    return true;
}

string GLUTFrame::GetName() const {
    return name;
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

void GLUTFrame::SetName(const string name) {
    this->name = name;
    if (init) glutSetWindowTitle(name.c_str());
}

void GLUTFrame::SetWidth(const unsigned int width) {
    this->width = width;
    if (init) glutReshapeWindow(width, height);
}

void GLUTFrame::SetHeight(const unsigned int height) {
    this->height = height;
    if (init) glutReshapeWindow(width, height);
}

void GLUTFrame::SetDepth(const unsigned int depth) {
    this->depth = depth;
}

void GLUTFrame::SetOptions(const FrameOption options) {    
    this->options = options;
}

void GLUTFrame::ToggleOption(const FrameOption option) {
    FrameOption opt = FrameOption(options ^ option);
    SetOptions(opt);
}

void GLUTFrame::Handle(Core::InitializeEventArg arg) {
    // Initialize the video frame
    int argc = 1;
    char *argv[] = {"hest"};
    logger.info << "Initialize GLUT" << logger.end;
    glutInit(&argc,argv);
    unsigned int mode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH; 
    if (IsOptionSet(FRAME_STEREO))
        mode |= GLUT_STEREO;
    glutInitDisplayMode(mode);
    glutInitWindowSize (width, height);
    if (IsOptionSet(FRAME_FULLSCREEN)) {
        std::ostringstream os;
        os << width << "x" << height << ":" << depth;
        glutGameModeString( os.str().c_str() );
        if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE) == 0) 
            logger.info << "GLUT: Game mode not possible." << logger.end;
        logger.info << "GLUT: Enter game mode: " << os.str() << logger.end;
        glutEnterGameMode();
        window = glutGetWindow();
    }
    else {
        window = glutCreateWindow(name.c_str());
        windows[window] = this;
    }
    init = true;
    glutReshapeFunc(GLUTFrame::reshape);
}

void GLUTFrame::Handle(Core::ProcessEventArg arg) {
    #ifdef OE_SAFE
    if (!init) throw new Exception("GLUTFrame not initialized");
    #endif

    // if (IsOptionSet(FRAME_STEREO)) {
    //     IViewingVolume* vol = vv;
    //     vv = stereo->GetLeft();
    //     glDrawBuffer(GL_BACK_LEFT);
    //     glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //     redrawEvent.Notify(RedrawEventArg(*this, arg.start, arg.approx));
    //     vv = stereo->GetRight();
    //     glDrawBuffer(GL_BACK_RIGHT);
    //     glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //     redrawEvent.Notify(RedrawEventArg(*this, arg.start, arg.approx));
    //     vv = vol;
    // }
    // else {
        // glDrawBuffer(GL_BACK);
        // glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    ((IListener<Display::ProcessEventArg>*)canvas)->Handle(Display::ProcessEventArg(fc, arg.start, arg.approx));
    // }
    glutSwapBuffers();
}

void GLUTFrame::Handle(Core::DeinitializeEventArg arg) {
    if (IsOptionSet(FRAME_FULLSCREEN))
        glutLeaveGameMode();
    ((IListener<Display::DeinitializeEventArg>*)canvas)->Handle(Display::DeinitializeEventArg(fc));
    windows.erase(window);
    glutDestroyWindow(window);
}

} // NS Display
} // NS OpenEngine
