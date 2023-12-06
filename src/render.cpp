#include <iostream>
#include <fmt/format.h>
#include <implot.h>

#include "render.hpp"
#include "font.hpp"
#include "font_awesome.cpp"
#include "font_awesome.h"



void WindowClass::Draw(std::string_view label)
{
    constexpr static auto windowFlags =
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
    //set ImGUI size
    constexpr static auto windowSize = ImVec2(1280.0f, 720.0f);
    //set ImGUI position
    constexpr static auto windowsPos = ImVec2(0.0f, 0.0f);

    //ImGUI size
    ImGui::SetNextWindowSize(windowSize);
    //ImGUI position
    ImGui::SetNextWindowPos(windowsPos);

    ImGui::Begin(label.data(), nullptr, windowFlags);

    DrawMenu();
    DrawContent();
    DrawActions();
    DrawFilter();

    ImGui::End();
}


void WindowClass::DrawMenu()
{
    if (ImGui::Button("Go up"))
    {
        if (m_currentPath.has_parent_path())
        {
            m_currentPath = m_currentPath.parent_path();
        }
    }

    //current location
    ImGui::TextColored(ImVec4(0.f, 255.f, 255.f, 1.f), "Current Directory: %s", m_currentPath.string().c_str());
}
void WindowClass::DrawContent()
{
    
    for (auto &entry : fs::directory_iterator(m_currentPath)) {
        const bool b_Directory = entry.is_directory();
        const bool b_File = entry.is_regular_file();
        const bool b_Selected = entry.path() == m_selectedEntry;
        std::string entryName = entry.path().filename().string();
        
        if (b_Directory) {
            ImGui::PushFont(m_IconFont);
            ImGui::TextColored(ImVec4(255.f, 255.f, 0.f, 1.f), "%s ", ICON_FA_FOLDER);
            ImGui::SameLine();
            entryName = entryName;
            ImGui::PopFont();
        } else if (b_File) {
            ImGui::PushFont(m_IconFont);
            ImGui::TextColored(ImVec4(0.f, 0.f, 255.f, 1.f), "%s ", ICON_FA_FILE);
            ImGui::SameLine();
            entryName = entryName;
            ImGui::PopFont();
        }
        if (ImGui::Selectable(entryName.c_str(), b_Selected))
        {
            if (b_Directory){
                m_currentPath /= entry.path();
            }
            m_selectedEntry = entry.path();
        }
    }
    
}
void WindowClass::DrawActions()
{

}
void WindowClass::DrawFilter()
{

}


void render(WindowClass &window_obj)
{
    window_obj.Draw("File Explorer");
}

void WindowClass::LoadFont()
{
    ImGuiIO &io = ImGui::GetIO();

    io.LogFilename = nullptr;
    io.IniFilename = nullptr;

    io.Fonts->AddFontFromMemoryTTF(font_roboto,
                                             sizeof(font_roboto),
                                             16.0f);
    static constexpr ImWchar icon_ranges[]{0xf000, 0xf3ff, 0};
    ImFontConfig icon_config;
    icon_config.MergeMode = true;
    icon_config.PixelSnapH = true;
    icon_config.OversampleH = 3;
    icon_config.OversampleV = 3;

    m_IconFont = io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data,
                                                font_awesome_size,
                                                18.0f,
                                                &icon_config,
                                                icon_ranges);


}