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

#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <X11/extensions/XI2.h>
#include <X11/extensions/Xge.h>
#include <X11/extensions/Xfixes.h>
#include <memory>
#include <unordered_set>

class WindowManager {
    public:
        static std::unique_ptr<WindowManager> create();
        
        int run();

        ~WindowManager();
    private:
        WindowManager(Display* display);
        
        Display* m_display;

        const Window m_rootWindow;
        
        static int XError(Display* display, XErrorEvent* errorEvent);

        static int XDetectWM(Display* display, XErrorEvent* errorEvent);

        static bool m_wmDetected;

        std::unordered_set<Window> m_managedWindows;
};
