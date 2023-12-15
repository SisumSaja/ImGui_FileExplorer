#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include "imgui_impl_opengl3_loader.h"
#include <imgui.h>
#include <filesystem>

namespace fs = std::filesystem;

class WindowClass
{

public:
    WindowClass();
public:
    void Draw(std::string_view label);
    static void Render(WindowClass &window_obj);
    bool Initialize();

private:
    ImFont* iconsFont;
    fs::path m_CurrentPath;
    fs::path m_SelectedPath;


protected:
    void DrawMenu();
    void DrawContent();
    void OpenWithVSCode(const fs::path& filePath);

};


