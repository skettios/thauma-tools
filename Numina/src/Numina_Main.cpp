#include <SDL_main.h>
#include <glad/gl.h>
#include <imgui.h>

#include <cassert>
#include <cstdint>
#include <iostream>

extern int Numina_Main(int, char **);

namespace tt
{
extern int Numina_Initialize(class App *);
extern void Numina_Run(class App *);
extern void Numina_Quit(class App *);

extern ImGuiContext *Numina_GetImGuiContext();
extern App *Numina_GetApplication();

extern GLADapiproc Numina_GL_GetProcAddress(const char *);
} // namespace tt

int main(int argc, char **argv)
{
  int32_t app_result = Numina_Main(argc, argv);
  if (app_result != 0)
    return app_result;

  std::cout << "Numina" << std::endl;
  assert(tt::Numina_GetApplication() != nullptr && "Application not set");

  tt::App *application = tt::Numina_GetApplication();

  int32_t engine_result = tt::Numina_Initialize(application);
  if (engine_result != 0)
    return engine_result;

  gladLoadGL((GLADloadfunc)tt::Numina_GL_GetProcAddress);

  ImGui::SetCurrentContext(tt::Numina_GetImGuiContext());

  tt::Numina_Run(application);

  tt::Numina_Quit(application);

  return 0;
}
