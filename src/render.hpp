#pragma once
#include "include.h"

namespace fs = std::filesystem;

class WindowClass
{

public:
    WindowClass() :
        iconsFont(nullptr),
        m_CurrentPath(fs::current_path()),
        m_SelectedPath(fs::path{})
    {

    }
public:
    void Draw(std::string_view label);
    static void render(WindowClass &window_obj);
    bool Initialize();

private:
    ImFont* iconsFont;
    fs::path m_CurrentPath;
    fs::path m_SelectedPath;


protected:
    void DrawMenu();
    void DrawContent();

};


