#pragma once
#include "imgui.h"

#include <GLFW/glfw3.h>

class ImGuiLayer 
{
public:
    ImGuiLayer(GLFWwindow* window);
    virtual ~ImGuiLayer() = default;
    void OnDetach();
    void Begin();
    void End();
    void Update(void *data);

    bool OnMouseClick(int button, int action, int mods);

    bool OnKeyPressed(int key, int action, int mods);
private:
    bool m_BlockEvents;
    int m_Scaler;
    ImVec4 m_Color;
};