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
#include <Display/ICanvas.h>
#include <string>

namespace OpenEngine {
namespace Display {
    using std::string;
/**
 * GLUT implementation of IFrame
 *
 * @class GLUTFrame GLUTFrame.h Display/GLUTFrame.h
 */
class GLUTFrame : public IFrame {
private:
    class FrameCanvas: public ICanvas {
    private:
        IFrame& frame;
    public:
        FrameCanvas(IFrame& frame): frame(frame) {}
        virtual ~FrameCanvas() {}
        unsigned int GetWidth() const { return frame.GetWidth(); }
        unsigned int GetHeight() const { return frame.GetHeight(); }
        void SetWidth(const unsigned int width) { frame.SetWidth(width); }
        void SetHeight(const unsigned int height) { frame.SetHeight(height); }

        void Handle(Display::InitializeEventArg arg) {}
        void Handle(Display::DeinitializeEventArg arg) {}
        void Handle(Display::ProcessEventArg arg) {}
        void Handle(Display::ResizeEventArg arg) {}

        ITexture2DPtr GetTexture() { return ITexture2DPtr(); }
    };    
    ICanvas* canvas;
    FrameCanvas fc;
    int window;
    string name;
    unsigned int width, height, depth;
    FrameOption options;
    bool init;
    void InitFrame();

    // dirty callback hack.
    static void display();
    static void reshape(int w, int h);

public:
    GLUTFrame(int w = 640, int h = 480, int d = 32, FrameOption options = FrameOption());
    ~GLUTFrame();

    bool IsFocused() const;

    string GetName() const;
    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    unsigned int GetDepth() const;
    FrameOption GetOptions() const;
    bool GetOption(const FrameOption option) const;

    void SetName(string name);
    void SetWidth(const unsigned int width);
    void SetHeight(const unsigned int height);
    void SetDepth(const unsigned int depth);
    void SetOptions(const FrameOption options);
    void ToggleOption(const FrameOption option);

    void Handle(Core::InitializeEventArg arg);
    void Handle(Core::ProcessEventArg arg);
    void Handle(Core::DeinitializeEventArg arg);

    void SetCanvas(ICanvas* canvas) { this->canvas = canvas; }
    ICanvas* GetCanvas() { return canvas; }
};

} // NS Display
} // NS OpenEngine

#endif
