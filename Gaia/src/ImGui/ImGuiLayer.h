#pragma once
#include "imgui.h"

#include <GLFW/glfw3.h>

#include "mbgl/style/layer.hpp"

namespace mbgl {
    class Map;
}

class ImGuiLayer
{
public:
    ImGuiLayer(GLFWwindow* window, mbgl::Map* map);
    virtual ~ImGuiLayer() = default;
    void OnDetach();
    void Begin();
    void End();
    void Update();
    bool OnMouseClick(int button, int action, int mods);
    bool OnKeyPressed(int key, int action, int mods);
private:
    void AddLayerVisibilityItem(mbgl::style::Layer *layer);
private:
    mbgl::Map* m_Map;
    bool m_BlockEvents;
    int m_Scaler;
    ImVec4 m_Color;
};
