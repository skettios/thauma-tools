#include "Numina.h"

#include <iostream>
#include <assert.h>

namespace tt
{
App *g_Application = nullptr;

App NUMINA_API *Numina_GetApplication()
{
  return g_Application;
}

App::App()
{
  assert(g_Application == nullptr && "Cannot have 2 applications running at the same time!");

  InsertResource(new WindowDescriptor);
  InsertResource(new ClearColor);

  g_Application = this;
}

App::~App()
{
  g_Application = nullptr;
}

void App::Update(float delta_time)
{
  for (auto layer : m_Layers)
    layer->OnUpdate(delta_time);
}

void App::ImGuiUpdate()
{
  for (auto layer : m_Layers)
    layer->OnImGui();
}

void App::Render()
{
  for (auto layer : m_Layers)
    layer->OnRender();
}

void App::InsertResource(AppResource *resource)
{
  auto it = m_Resources.find(std::type_index(typeid(*resource)));
  if (it != m_Resources.end())
  {
    delete it->second;
    m_Resources.erase(it);
  }

  m_Resources.insert(std::pair<std::type_index, AppResource *>(std::type_index(typeid(*resource)), resource));
}

void App::PushLayer(AppLayer *layer)
{
  m_Layers.push_back(layer);
}

AppLayer *App::PopLayer()
{
  AppLayer *back = m_Layers.back();

  m_Layers.pop_back();

  return back;
}

App &AppLayer::GetApp()
{
  return *g_Application;
}

} // namespace tt
