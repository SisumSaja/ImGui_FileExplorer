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
        m_CurrentPath(fs::current_path()),
        m_SelectedEntry(fs::path{}),
        m_IconFont(nullptr)
    {

    }
    void Draw(std::string_view label);

private:
    void DrawMenu();
    void DrawContent();
    void DrawActions();
    void DrawFilter();

private:
    fs::path m_CurrentPath;
    fs::path m_SelectedEntry;
    std::stack<fs::path> m_PreviousPath;
    ImFont *m_IconFont;
};

void render(WindowClass &window_obj);
