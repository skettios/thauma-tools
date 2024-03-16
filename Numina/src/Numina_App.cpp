#include "Numina.h"

#include <iostream>
#include <assert.h>

namespace tt
{
App *g_Application = nullptr;

App *Numina_GetApplication()
{
  return g_Application;
}

App::App()
{
  assert(g_Application == nullptr && "Cannot have 2 applications running at the same time!");

  g_Application = this;

  InsertResource(new WindowDescriptor);
  InsertResource(new ClearColor);
}

App::~App()
{
  g_Application = nullptr;
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

} // namespace tt

