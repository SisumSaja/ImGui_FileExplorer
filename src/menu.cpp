#include "menu.hpp"


bool WindowClass::Initialize(GLFWwindow *window)
{

    //Initialize window

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // set imgui to for openGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    //load font
    io.Fonts-> AddFontFromMemoryTTF(font_roboto, sizeof(font_roboto), 16.f );

    static const ImWchar icon_ranges[]{ 0xf000, 0xf3ff, 0 };
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.OversampleH = 3;
    icons_config.OversampleV = 3;

     io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 19.5f, &icons_config, icon_ranges);

    // Customize ImGui style
    ImGuiStyle& style = ImGui::GetStyle();
    auto& colors = style.Colors;

    style.ScrollbarRounding = 0;
    style.WindowRounding = 4.0f;

    colors[ImGuiCol_ResizeGrip] = ImColor(0, 0, 0, 0);
    colors[ImGuiCol_ResizeGripActive] = ImColor(0, 0, 0, 0);
    colors[ImGuiCol_ResizeGripHovered] = ImColor(0, 0, 0, 0);

    colors[ImGuiCol_Button] = ImColor(18, 18, 18, 100);
    colors[ImGuiCol_ButtonActive] = ImColor(21, 21, 21, 100);
    colors[ImGuiCol_ButtonHovered] = ImColor(21, 21, 21, 100);

    colors[ImGuiCol_CheckMark] = ImColor(0, 189, 0, 255);

    colors[ImGuiCol_FrameBg] = ImColor(24, 24, 24);
    colors[ImGuiCol_FrameBgActive] = ImColor(26, 26, 26);
    colors[ImGuiCol_FrameBgHovered] = ImColor(26, 26, 26);

    return true;

    return false;
}
