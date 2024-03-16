#include "Numina.h"

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
}

App::~App()
{
  g_Application = nullptr;
}
} // namespace tt

