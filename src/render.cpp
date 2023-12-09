#include <Windows.h>
#include <vector>
#include <string>

#include "render.hpp"

WindowClass::WindowClass() :
        iconsFont(nullptr),
        m_CurrentPath(fs::current_path()),
        m_SelectedPath(fs::path{})
{

}

void WindowClass::Draw(std::string_view label)
{
    constexpr static auto window_flags =
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;

    constexpr static auto window_size = ImVec2(1280.0F, 720.0F);
    constexpr static auto window_pos = ImVec2(0.0F, 0.0F);

    ImGui::SetNextWindowSize(window_size);
    ImGui::SetNextWindowPos(window_pos);

    ImGui::Begin(label.data(), nullptr, window_flags);

    DrawMenu();
    ImGui::Separator();
    DrawContent();

    ImGui::End();
}

bool WindowClass::Initialize() {
    // Initialize window
    IMGUI_CHECKVERSION();
    ImGuiIO& io = ImGui::GetIO();

    io.LogFilename = nullptr;
    io.IniFilename = nullptr;

    // Load font. CMAKE_CURRENT_BINARY_DIR defined on CMakelist
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(nullptr, exePath, MAX_PATH);
    fs::path CMAKE_CURRENT_BINARY_DIR;
    auto fontPath = fs::path(CMAKE_CURRENT_BINARY_DIR) / "Roboto.ttf";
    io.Fonts->AddFontFromFileTTF(fontPath.string().c_str(), 18.0f);

    //Load Icon from Fontawesome
    static const ImWchar icon_ranges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.OversampleH = 3;
    icons_config.OversampleV = 3;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    iconsFont = io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 19.5f, &icons_config, icon_ranges);

    ImGuiStyle style = ImGui::GetStyle();
    auto& colors = style.Colors;

    return true;
}

void WindowClass::DrawMenu()
{
    if (ImGui::Button("Go Up"))
    {
        if (m_CurrentPath.has_parent_path())
        {
            m_CurrentPath = m_CurrentPath.parent_path();
        }
    }
    
    ImGui::SameLine();
    
    // Make the current directory copyable
    static char copyBuffer[256];
    strcpy(copyBuffer, m_CurrentPath.string().c_str());
    
    if (ImGui::InputText("##CurrentDirectory", copyBuffer, sizeof(copyBuffer),
                         ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_AutoSelectAll))
    {
        ImGui::SetClipboardText(copyBuffer);
    }

}

void WindowClass::DrawContent()
{
    for (const auto &entry : fs::directory_iterator(m_CurrentPath))
    {
        const auto is_selected = entry.path() == m_SelectedPath;
        const auto is_directory = entry.is_directory();
        const auto is_file = entry.is_regular_file();
        auto entryName = entry.path().filename().string();

        ImGui::PushID(entryName.c_str());

        if (is_directory)
        {
            ImGui::PushFont(iconsFont);
            ImGui::TextColored(ImVec4(255.f, 255.f, 0.f, 1.f), "%s ", ICON_FA_FOLDER);
            ImGui::PopFont();
            ImGui::SameLine();
            entryName = entryName;
        }
        else if (is_file)
        {
            ImGui::PushFont(iconsFont);
            ImGui::TextColored(ImVec4(0.f, 0.f, 255.f, 1.f), "%s ", ICON_FA_FILE);
            ImGui::PopFont();
            ImGui::SameLine();
            entryName = entryName;
        }

        if (ImGui::IsMouseClicked(1)) // Check for right mouse button click
        {
            m_SelectedPath = entry.path();
            ImGui::OpenPopup("ContextMenu");
        }

        if (ImGui::BeginPopupContextItem("ContextMenu"))
        {
            if (ImGui::MenuItem("Open with VS Code"))
            {
                OpenWithVSCode(entry.path());
            }
            ImGui::EndPopup();
        }

        if (ImGui::Selectable(entryName.c_str(), is_selected))
        {
            if (is_directory)
                m_CurrentPath /= entry.path().filename();

            m_SelectedPath = entry.path();
        }

        ImGui::PopID();
    }
}

void WindowClass::OpenWithVSCode(const fs::path& filePath)
{
     if (fs::exists(filePath))
    {
        // Use the path directly, no need to check if it's a directory or file
        std::wstring command = L"code \"" + filePath.wstring() + L"\"";
        ShellExecuteW(nullptr, L"open", L"code", command.c_str(), nullptr, SW_SHOWNORMAL);
    }
}



//Main Render for the WindowClass
void WindowClass::Render(WindowClass &window) {
    window.Draw("Sum Explorer");
}
