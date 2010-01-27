// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------
#ifndef _OE_GLUT_FRAME_H_
#define _OE_GLUT_FRAME_H_

#include <Display/IFrame.h>

namespace OpenEngine {
namespace Display {

using OpenEngine::Core::InitializeEventArg;
using OpenEngine::Core::ProcessEventArg;
using OpenEngine::Core::DeinitializeEventArg;


/**
 * GLUT implementation of IFrame
 *
 * @class GLUTFrame GLUTFrame.h Display/GLUTFrame.h
 */
class GLUTFrame : public IFrame {
private:
    unsigned int width, height, depth;
    FrameOption options;

public:
    GLUTFrame(int w = 640, int h = 480, int d = 32, FrameOption options = FrameOption());
    ~GLUTFrame();

    bool IsFocused() const;

    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    unsigned int GetDepth() const;
    FrameOption GetOptions() const;
    bool GetOption(const FrameOption option) const;

    void SetWidth(const int width);
    void SetHeight(const int height);
    void SetDepth(const int depth);
    void SetOptions(const FrameOption options);
    void ToggleOption(const FrameOption option);

    void Handle(InitializeEventArg arg);
    void Handle(ProcessEventArg arg);
    void Handle(DeinitializeEventArg arg);

};

} // NS Display
} // NS OpenEngine

#endif
