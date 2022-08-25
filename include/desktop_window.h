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

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <memory>

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/overlay.h>
#include <gdkmm/pixbuf.h>
#include <gtkmm/container.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/icontheme.h>
#include <gtkmm/iconinfo.h>
#include <deskentry/deskentry.h>

#include "ExecutableButton.h"

class Desktop : public Gtk::Window {
    public:
        Desktop();
	~Desktop();
        int populateApps();

	Desktop(const Desktop&) = delete;
	Desktop& operator=(const Desktop&) = delete;
    private:
        
        unsigned int m_rows;

        unsigned int m_columns;

        int scanApps();
        
    protected:
       
        std::vector<std::shared_ptr<ExecutableButton>> m_buttons;

	std::unique_ptr<Gtk::Grid> m_appGrid;

        Gtk::ScrolledWindow m_scrollable;

        Gtk::Overlay m_overlay;
};
