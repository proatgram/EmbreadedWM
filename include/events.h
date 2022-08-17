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

#include <cstdlib>
#include <cstdio>
#include <unordered_set>

#include <X11/Xlib.h>

class Events {
    public:
        static void DoCreateEvent(const XCreateWindowEvent& event, Display* display) {
            std::fprintf(stdout, "Got window create event for Window %ld\n", event.window);
        }

        static void DoDestroyEvent(const XDestroyWindowEvent& event, Display* display) {

        }

        static void DoReparentEvent(const XReparentEvent& event, Display* display) {

        }
        
        static void DoConfigureRequestEvent(const XConfigureRequestEvent& event, Display* display) {
            XWindowChanges change;

            change.x = event.x;
            change.y = event.y;
            change.width = event.width;
            change.height = event.height;
            change.border_width = event.border_width;
            change.sibling = event.above;
            change.stack_mode = event.detail;

            XConfigureWindow(display, event.window, event.value_mask, &change);
        }
        static void DoMapRequestEvent(const XMapRequestEvent& event, Display* display, std::unordered_set<Window>& managedWindows) {
            XMapWindow(display, event.window);
            managedWindows.insert(event.window);
            XAddToSaveSet(display, event.window);
        }
        static void DoUnmapNotify(const XUnmapEvent& event, Display* display, std::unordered_set<Window>& managedWindows) {
            if (!managedWindows.count(event.window)) {
                std::fprintf(stdout, "Not unmaping unmap request for window %ld. Reason: Non-managed window.\n", event.window);
                return;
            }
            XUnmapWindow(display, event.window);
            XDestroyWindow(display, event.window);
            managedWindows.erase(event.window);
            XRemoveFromSaveSet(display, event.window);
        }
};
