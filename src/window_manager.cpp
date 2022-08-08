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

#include "window_manager.h"

#include <sysexits.h>
#include <cstdlib>
#include <cstdio>

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
    m_rootWindow(DefaultRootWindow(m_display))

{

}

WindowManager::~WindowManager(){
    XCloseDisplay(m_display);
    std::fprintf(stdout, "Connection to the X server was terminated.\n");
}

int WindowManager::run() {

}
