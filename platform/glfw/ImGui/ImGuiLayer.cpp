#include "ImGuiLayer.h"

#include <imgui.h>
#include <iostream>
#include <ostream>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <misc/cpp/imgui_stdlib.h>
#include <__format/format_functions.h>

#include "mbgl/map/map.hpp"
#include "mbgl/style/layer_impl.hpp"
#include "mbgl/style/style.hpp"

namespace mbgl {
    class Map;
}

ImGuiLayer::ImGuiLayer(GLFWwindow* window, mbgl::Map* map)
    : m_Map(map)
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

    // float fontSize = 18.0f;// *2.0f;
    // io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", fontSize);
    // io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", fontSize);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");
}

void ImGuiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::End()
{
    // ImGuiIO& io = ImGui::GetIO();

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    // {
    //     GLFWwindow* backup_current_context = glfwGetCurrentContext();
    //     ImGui::UpdatePlatformWindows();
    //     ImGui::RenderPlatformWindowsDefault();
    //     glfwMakeContextCurrent(backup_current_context);
    // }

    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
}

void ImGuiLayer::Update()
{
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x - 300, main_viewport->WorkPos.y + 20), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_Once);
    ImGui::Begin("GAIA");

    if (ImGui::CollapsingHeader("Layers"))
    {
        for (mbgl::style::Layer *layer: m_Map->getStyle().getLayers())
        {
            if (layer->isVisible)
            {
                layer->setVisibility(mbgl::style::VisibilityType::Visible);
            }
            else
            {
                layer->setVisibility(mbgl::style::VisibilityType::None);
            }

            ImGui::Checkbox(layer->baseImpl.get()->id.c_str(), &(layer->isVisible));
        }
    }

    ImGui::End();
}

bool ImGuiLayer::OnMouseClick(int button, int action, int mods)
{
    ImGuiIO& io = ImGui::GetIO();
    return io.WantCaptureMouse;
}

bool ImGuiLayer::OnKeyPressed(int key, int action, int mods)
{
    ImGuiIO& io = ImGui::GetIO();
    return io.WantCaptureKeyboard;
}
