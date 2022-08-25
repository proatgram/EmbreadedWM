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

#include "AppPage.h"

Page::Page(int maxHeight, int maxWidth) :
    m_maxRows(maxWidth),
    m_maxColumns(maxHeight),
    m_rows(0),
    m_columns(0)
{
    
}

int Page::addApp(std::string icon, std::string exec) {
    std::printf("%d %d, %s\n", m_rows, m_columns, exec.c_str());
    if (m_rows == m_maxRows) {
        if (m_columns != m_maxColumns - 1) {
            m_columns++;
            m_appGrid.insert_column(m_columns);
        }
        else {
            return MAX_ITEMS;
        }
        m_rows = 0;
    }
    m_rows++;
    std::shared_ptr<ExecutableButton> button = std::make_shared<ExecutableButton>(exec, icon);
    m_appGrid.attach(button->returnButton(), m_columns, m_rows);
    m_apps.push_back(button);
    return 0;
}

int Page::addApp(std::shared_ptr<ExecutableButton> app) {
    if (m_rows == m_maxRows) {
        if (m_columns != m_maxColumns) {
            m_columns++;
            m_appGrid.insert_column(m_columns);
        }
        else {
            return MAX_ITEMS;
        }
        m_rows = 0;
    }
    m_rows++;
    m_appGrid.attach(app->returnButton(), m_rows, m_columns);
    m_apps.push_back(app);
    return 0;
}

Gtk::Grid& Page::getGrid() {
    return m_appGrid;
}
