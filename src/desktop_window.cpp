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

#include "desktop_window.h"

Desktop::Desktop() :
    m_appPages(Gtk::Adjustment::create(0, 0, 0, 0, 0, 0), Gtk::Adjustment::create(2, 1, 5)),
    m_backgroundPages()

{
    set_title("EmbreadedTop");
    set_default_size(240, 240);
    scanApps();
}

int Desktop::populateApps() {

    return 0;
}

int Desktop::scanApps() {
    std::string exec;
    for (auto const& it : std::filesystem::recursive_directory_iterator(std::filesystem::path("/usr/share/applications"))) {
        try {
            exec = DeskEntry::getEntries(it.path()).at("Exec");
        }
        catch (std::out_of_range) {
            exec = "";
        }
        std::printf("%s\n", exec.c_str());
    }
    return 0;
}
