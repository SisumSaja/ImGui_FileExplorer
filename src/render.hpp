#pragma once

#include <cstdint>
#include <string_view>
#include <imgui.h>

//Added
#include <filesystem>
#include <stack>



//Usually this approach is not good, but for current purposes it's good and widely used from c++ community
namespace fs = std::filesystem;

class WindowClass
{
public:
    //Constructor, with empty function body
    WindowClass() :
        m_currentPath(fs::current_path()),
        m_selectedEntry(fs::path{})
    {

    }
    void Draw(std::string_view label);

private:
    void DrawMenu();
    void DrawContent();
    void DrawActions();
    void DrawFilter();

private:
    fs::path m_currentPath;
    fs::path m_selectedEntry;
    std::stack<fs::path>m_previousPath;
    ImFont *m_IconFont = nullptr;
};

void render(WindowClass &window_obj);
