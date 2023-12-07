#include "imgui.h"
#include "imgui_internal.h"

#include <GLFW/glfw3.h>
#include <GLES2/gl2.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "font.hpp"
#include "font_awesome.h"

class ExplorerMenu
{
public:
    ExplorerMenu() :
        iconsFont(nullptr)
    {
    }

public:
    void Render();
    bool Initialize(GLFWwindow* window);

private:
    ImFont* iconsFont;
};
