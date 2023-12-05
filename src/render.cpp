#include <iostream>
#include <fmt/format.h>
#include <implot.h>

#include "render.hpp"
#include "font.hpp"
#include "font_awesome.h"
#include "font_awesome.cpp"


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

void WindowClass::LoadFont()
{
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    auto& colors = style.Colors;
    io.LogFilename = nullptr;
    io.IniFilename = nullptr;

    //Load font from memory
    io.Fonts->AddFontFromMemoryTTF(font_roboto, sizeof(font_roboto), 25.0f);
    //Load font from file
    //io.Fonts->AddFontFromFileTTF("D\\Project\\FileExplorer\\icons\\roboto.ttf", 16.f);

    static const ImWchar iconRanges[]{0xf000, 0xf3ff, 0};
    ImFontConfig iconConfig;
    iconConfig.MergeMode = true;
    iconConfig.PixelSnapH = true;
    iconConfig.OversampleH = 3;
    iconConfig.OversampleV = 3;
    io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 20.f, &iconConfig, iconRanges);
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
    ImGui::SameLine();
    if (ImGui::Button("Previous Path"))
    {
        if (!m_currentPath.empty())
        {
            m_currentPath = m_previousPath.top();
            m_previousPath.pop();
        }
    }
    ImGui::Text("Current Directory: %s", m_currentPath.string().c_str());
}
void WindowClass::DrawContent()
{
    for (auto &entry : fs::directory_iterator(m_currentPath))
    {
        const auto b_isDirectory = entry.is_directory();
        const auto b_isFile = entry.is_regular_file();
        std::string entryName = entry.path().filename().string();
        if (b_isDirectory)
        {
            ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "%s %s",FONT_FA, entryName.c_str());
        } else if(b_isFile)
        {
            ImGui::TextColored(ImVec4(1.0f, 0.84f, 0.0f, 1.0f), "%s %s", "[F]", entryName.c_str());
        }
        ImGui::Text("%s", entryName.c_str());
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
