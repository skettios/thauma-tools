#include "Numina/AppLayer.h"

#include <imgui.h>

namespace tt
{
AppLayer::~AppLayer()
{
}

void AppLayer::OnPush()
{
}

void AppLayer::OnPop()
{
}

void AppLayer::OnBuild()
{
}

bool AppLayer::OnSDLEvent(SDL_Event *event)
{
  return true;
}

void AppLayer::OnUpdate(float)
{
}

void AppLayer::OnImGui()
{
}

void AppLayer::OnRender()
{
}

void DebugLayer::OnUpdate(float delta_time)
{
  static float accumulator = 1.f;
  accumulator += delta_time;

  if (accumulator >= 0.5f)
  {
    accumulator -= 0.5f;

    m_FPS = static_cast<uint32_t>(1.f / delta_time);
    m_FrameTime = delta_time * 1000.f;
  }
}

void DebugLayer::OnImGui()
{
  ImGui::Begin("Debug Overlay", 0,
               ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar |
                   ImGuiWindowFlags_NoCollapse);

  ImGui::SetWindowPos({10, 10});
  ImGui::SetWindowSize({200, 50});

  ImGui::TextColored({0.f, 1.f, 0.f, 1.f}, "FPS: %d", m_FPS);
  ImGui::TextColored({0.f, 1.f, 0.f, 1.f}, "Frame Time: %.2f ms", m_FrameTime);

  ImGui::End();
}

} // namespace tt
