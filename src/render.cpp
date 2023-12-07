// render.cpp
#include <iostream>
#include <fmt/format.h>
#include <implot.h>

#include "render.hpp"
#include "font.hpp"
#include "font_awesome.h"
#include "imgui_impl_opengl3_loader.h"

void WindowClass::Draw(std::string_view label)
{
    constexpr static auto windowFlags =
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
    // set ImGUI size
    constexpr static auto windowSize = ImVec2(1280.0f, 720.0f);
    // set ImGUI position
    constexpr static auto windowsPos = ImVec2(0.0f, 0.0f);

    // ImGUI size
    ImGui::SetNextWindowSize(windowSize);
    // ImGUI position
    ImGui::SetNextWindowPos(windowsPos);
    ImGui::Begin(label.data(), nullptr, windowFlags);

    DrawMenu();
    DrawContent();
    DrawActions();
    DrawFilter();

    ImGui::End();
}

ImFont* WindowClass::InitializeFonts()
{
    ImGuiIO &io = ImGui::GetIO();
    io.LogFilename = nullptr;
    io.IniFilename = nullptr;
    io.Fonts->AddFontFromMemoryTTF(font_roboto, sizeof(font_roboto), 18.0f);
    
    ImFontConfig iconsConfig;
    iconsConfig.MergeMode = true;
    iconsConfig.PixelSnapH = true;
    iconsConfig.OversampleH = 3;
    iconsConfig.OversampleV = 3;

    static const ImWchar iconRanges[]{0xf00, 0xf3ff, 0};
    return io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 18.0f, &iconsConfig, iconRanges);
}


void WindowClass::DrawMenu()
{
    if (ImGui::Button("Go up"))
    {
        if (m_CurrentPath.has_parent_path())
        {
            m_CurrentPath = m_CurrentPath.parent_path();
        }
    }

    // current location
    ImGui::TextColored(ImVec4(0.f, 255.f, 255.f, 1.f), "Current Directory: %s", m_CurrentPath.string().c_str());
}

void WindowClass::DrawContent()
{
    
    for (auto &entry : fs::directory_iterator(m_CurrentPath)) {
        const bool b_Directory = entry.is_directory();
        const bool b_File = entry.is_regular_file();
        const bool b_Selected = entry.path() == m_SelectedEntry;
        std::string entryName = entry.path().filename().string();
        
        if (b_Directory) {

            ImGui::PushFont(iconsFont);
            ImGui::TextColored(ImVec4(255.f, 255.f, 0.f, 1.f), "%s ", ICON_FA_FOLDER);
            ImGui::PopFont();

            ImGui::SameLine();
            entryName = entryName;
        } else if (b_File) {

            ImGui::PushFont(iconsFont);
            ImGui::TextColored(ImVec4(0.f, 0.f, 255.f, 1.f), "%s ", ICON_FA_FILE);
            ImGui::PopFont();

            ImGui::SameLine();
            entryName = entryName;
        }
        if (ImGui::Selectable(entryName.c_str(), b_Selected))
        {
            if (b_Directory){
                m_CurrentPath /= entry.path();
            }
            m_SelectedEntry = entry.path();
        }
    }
}

void WindowClass::DrawActions()
{
}

void WindowClass::DrawFilter()
{
}

void WindowClass::CleanupFonts()
{
    ImGuiIO &io = ImGui::GetIO();
    io.Fonts->Clear();
}

WindowClass::~WindowClass()
{
    CleanupFonts();
}

void render(WindowClass &window_obj)
{
    window_obj.Draw("File Explorer");

}
