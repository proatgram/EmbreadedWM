/*
Copyright (c) 2022 Timothy Hutchins

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <sysexits.h>
#include <cstdlib>
#include <cstdio>

#include "window_manager.h"
#include "events.h"

bool WindowManager::m_wmDetected = false;

std::unique_ptr<WindowManager> WindowManager::create() {
    Display* display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        std::fprintf(stderr, "Failed to open display %s\n", XDisplayName(nullptr));
        return nullptr;
    }

    return std::unique_ptr<WindowManager>(new WindowManager(display));
}

WindowManager::WindowManager(Display* display) :
    m_display(display),
    m_rootWindow(DefaultRootWindow(m_display)),
    m_managedWindows()

{

}

WindowManager::~WindowManager(){
    XCloseDisplay(m_display);
    std::fprintf(stdout, "Connection to the X server was terminated.\n");
}

int WindowManager::run() {
    m_wmDetected = false;
    XSetErrorHandler(&WindowManager::XDetectWM);
    XSelectInput(m_display, m_rootWindow, SubstructureRedirectMask | SubstructureNotifyMask);

    XSync(m_display, false);

    if (m_wmDetected) {
        std::fprintf(stderr, "Detected another active Window Manager on this display.\n");
        return 1;
    }
    XSetErrorHandler(&WindowManager::XError);
    XGrabServer(m_display);

    Window retRoot, retParent;
    Window* topWindows;
    unsigned int numberTopWin;

    XQueryTree(m_display, m_rootWindow, &retRoot, &retParent, &topWindows, &numberTopWin);

    for (unsigned int i = 0; i < numberTopWin; ++i) {
        XAddToSaveSet(m_display, topWindows[i]);
        XMapWindow(m_display, topWindows[i]);
        m_managedWindows.insert(topWindows[i]);
    }
    XFree(topWindows);
    XUngrabServer(m_display);
    for (;;) {
        XEvent event;
        XNextEvent(m_display, &event);

        switch (event.type) {
            case CreateNotify:
                Events::DoCreateEvent(event.xcreatewindow, m_display);
                break;
            case DestroyNotify:
                Events::DoDestroyEvent(event.xdestroywindow, m_display);
                break;
            case ReparentNotify:
                Events::DoReparentEvent(event.xreparent, m_display);
                break;
            case ConfigureRequest:
                Events::DoConfigureRequestEvent(event.xconfigurerequest, m_display);
                break;
            case MapRequest:
                Events::DoMapRequestEvent(event.xmaprequest, m_display, m_managedWindows);
                break;
            case UnmapNotify:
                Events::DoUnmapNotify(event.xunmap, m_display, m_managedWindows);
                break;
            default:

                break;
        }
    }
}

int WindowManager::XDetectWM(Display* display, XErrorEvent* errorEvent) {
    if (static_cast<int>(errorEvent->error_code) == BadAccess) {
        m_wmDetected = true;
    }

    return 0;
}

int WindowManager::XError(Display* display, XErrorEvent* errorEvent) {
    std::fprintf(stderr, "XError: %d Type: %d", errorEvent->error_code, errorEvent->type);
    return errorEvent->error_code;
}
