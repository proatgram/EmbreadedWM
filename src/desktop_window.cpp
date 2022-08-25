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
    m_overlay()

{
    set_title("EmbreadedTop");
    set_default_size(240, 240);
   
    m_overlay.add_overlay(m_stack);

    m_overlay.show_all();

    add(m_overlay);
}

Desktop::~Desktop() {

}

int Desktop::populateApps() {
    std::string exec;
    std::string icon;
    std::string hide;
    std::map<std::string, std::string> info;
    for (auto const& it : std::filesystem::recursive_directory_iterator(std::filesystem::path("/usr/share/applications"))) {
        info = DeskEntry::getEntries(it.path());
        try {
            exec = info.at("Exec");
            std::string::size_type i = exec.find("%f");
            if (i != std::string::npos) {
                exec.erase(i, 2);
            }
            i = exec.find("%F");
            if (i != std::string::npos) {
                exec.erase(i, 2);
            }
            i = exec.find("%U");
            if (i != std::string::npos) {
                exec.erase(i, 2);
            }
            i = exec.find("%u");
            if (i != std::string::npos) {
                exec.erase(i, 2);
            }
        }
        catch (std::out_of_range) {
            exec = "";
        }
        try {
            icon = info.at("Icon");
        }
        catch (std::out_of_range) {
            icon = "";
        }
        if (exec != "") {
        try {
            hide = info.at("NoDisplay");
        }
        catch (std::out_of_range) {
            hide = "";
        }
            if (hide != "true") {
                if (m_pages.size() == 0) {
                    m_pages.emplace_back(5, 5);
                }

                if (m_pages.at(m_pages.size() - 1).addApp(icon, exec) == m_pages.at(m_pages.size() - 1).MAX_ITEMS) {
                    m_pages.emplace_back(5, 5);
                }
            }
        }
    }
    for (unsigned int i = 0; i < m_pages.size(); i++) {
        m_stack.add(m_pages.at(i).getGrid());
    }
    m_stack.show_all();
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
