#include <cstdint>
#include <iostream>

#include <imgui.h>

#include <assert.h>

extern int Numina_Main(int, char **);

namespace tt
{
extern int Numina_Initialize(class App *);
extern void Numina_Run(class App *);
extern void Numina_Quit(class App *);

extern ImGuiContext *Numina_GetImGuiContext();
extern App *Numina_GetApplication();
} // namespace tt

static int _Numina_Main(int argc, char **argv)
{
  int32_t app_result = Numina_Main(argc, argv);
  if (app_result != 0)
    return app_result;

  std::cout << "Numina" << std::endl;
  assert(tt::Numina_GetApplication() != nullptr && "Application not set");

  int32_t engine_result = tt::Numina_Initialize(tt::Numina_GetApplication());
  if (engine_result != 0)
    return engine_result;

  ImGui::SetCurrentContext(tt::Numina_GetImGuiContext());

  tt::Numina_Run(tt::Numina_GetApplication());

  tt::Numina_Quit(tt::Numina_GetApplication());

  return 0;
}

#if defined(TT_PLATFORM_WIN32)
#include <Windows.h>

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char *, int nShowCmd)
{
  return _Numina_Main(__argc, __argv);
}
#else
int main(int argc, char **argv)
{
  return _Numina_Main(argc, argv);
}
#endif
