#include "render.hpp"

bool WindowClass::Initialize() {
    // Initialize window
    IMGUI_CHECKVERSION();
    ImGuiIO& io = ImGui::GetIO();

    io.LogFilename = nullptr;
    io.IniFilename = nullptr;

    // Load font
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(nullptr, exePath, MAX_PATH);
    fs::path fontPath = fs::path(exePath).parent_path().parent_path() / "icons" / "Roboto-Regular.ttf";
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

    return true;
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

    // Create columns
    ImGui::Columns(2, "InfoColumns", false);

    // Column 1: Draw Content
    ImGui::Text("File Explorer Content:");
    ImGui::Separator();
    DrawContent();

    // Column 2: CPU and Memory Information
    ImGui::NextColumn();

    ImGui::Text("System Information:");
    ImGui::Separator();

    // End columns
    ImGui::Columns(1);

    ImGui::End();
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
    ImGui::TextColored(ImColor(0, 255, 255, 255).Value,"Current directory: %s", m_CurrentPath.string().c_str());
}

void WindowClass::DrawContent() {
    for (const auto &entry : fs::directory_iterator(m_CurrentPath))
    {
        const auto is_selected = entry.path() == m_SelectedPath;
        const auto is_directory = entry.is_directory();
        const auto is_file = entry.is_regular_file();
        auto entryName = entry.path().filename().string();

        if (is_directory) {
            ImGui::PushFont(iconsFont);
            ImGui::TextColored(ImVec4(255.f, 255.f, 0.f, 1.f), "%s ", ICON_FA_FOLDER);
            ImGui::PopFont();
            ImGui::SameLine();
            entryName = entryName;
        }
        else if (is_file){
            ImGui::PushFont(iconsFont);
            ImGui::TextColored(ImVec4(0.f, 0.f, 255.f, 1.f), "%s ", ICON_FA_FILE);
            ImGui::PopFont();
            ImGui::SameLine();
            entryName = entryName;
        }


        if (ImGui::Selectable(entryName.c_str(), is_selected))
        {
            if (is_directory)
                m_CurrentPath /= entry.path().filename();

            m_SelectedPath = entry.path();
        }
    }
}


//Main Render for the WindowClass
void WindowClass::render(WindowClass &window) {
    window.Draw("Sum Explorer");
}


