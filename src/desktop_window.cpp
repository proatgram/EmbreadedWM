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
    m_appGrid(std::make_unique<Gtk::Grid>()),
    m_scrollable(),
    m_overlay(),
    m_buttons()

{
    set_title("EmbreadedTop");
    set_default_size(240, 240);
    
    m_scrollable.set_border_width(10);
    m_scrollable.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);

    m_appGrid->set_row_spacing(8);
    m_appGrid->set_column_spacing(8);

    m_appGrid->set_column_homogeneous(true);
    m_appGrid->set_row_homogeneous(true);

    m_scrollable.add(*m_appGrid.get());

    m_overlay.add_overlay(m_scrollable);

    m_overlay.show_all();

    add(m_overlay);
}

Desktop::~Desktop() {
   m_appGrid.reset();
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
            std::printf("%s\n", exec.c_str());
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
                std::shared_ptr<ExecutableButton> btn = std::make_shared<ExecutableButton>(exec, icon);
                m_buttons.push_back(btn);
                if (m_rows >= 5) {
                    m_columns++;
                    m_rows = 0;
                    m_appGrid->insert_column(m_columns);
                    m_appGrid->attach(btn->returnButton(), m_columns, m_rows + 1);
                }
                else {
                    m_appGrid->attach(btn->returnButton(), m_columns, m_rows + 1);

                }
                m_rows++;
            }
        }
    }
    m_appGrid->show_all();
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
