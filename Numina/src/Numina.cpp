#include "Numina/Defines.h"
#include "Numina/App.h"

#include <glad/gl.h>
#include <SDL.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

namespace tt
{
static SDL_Window *g_Window = nullptr;
static SDL_GLContext g_GLContext = nullptr;
static ImGuiContext *g_ImGuiContext = nullptr;

static bool g_Running = true;

ImGuiContext NUMINA_API *Numina_GetImGuiContext()
{
  return g_ImGuiContext;
}

GLADapiproc NUMINA_API Numina_GL_GetProcAddress(const char *name)
{
  return (GLADapiproc)SDL_GL_GetProcAddress(name);
}

int NUMINA_API Numina_Initialize(App *app)
{
  WindowDescriptor window_descriptor = app->GetResource<WindowDescriptor>();
  ClearColor clear_color = app->GetResource<ClearColor>();

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    return -1;

  g_Window = SDL_CreateWindow(window_descriptor.m_Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              window_descriptor.m_Width, window_descriptor.m_Height, SDL_WINDOW_OPENGL);
  if (!g_Window)
    return -2;

  SDL_GLContext dummy_context = SDL_GL_CreateContext(g_Window);
  if (!dummy_context)
    return -3;

  gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

  int32_t major, minor;
  glGetIntegerv(GL_MAJOR_VERSION, &major);
  glGetIntegerv(GL_MINOR_VERSION, &minor);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  g_GLContext = SDL_GL_CreateContext(g_Window);
  if (!g_GLContext)
    return -4;

  SDL_GL_MakeCurrent(g_Window, g_GLContext);
  SDL_GL_DeleteContext(dummy_context);

  gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

  glClearColor(clear_color.m_Red, clear_color.m_Green, clear_color.m_Blue, 1.f);

  IMGUI_CHECKVERSION();
  g_ImGuiContext = ImGui::CreateContext();
  ImGui_ImplSDL2_InitForOpenGL(g_Window, g_GLContext);
  ImGui_ImplOpenGL3_Init("#version 150");

  return 0;
}

void NUMINA_API Numina_Run(App *app)
{
  double last_time = SDL_GetPerformanceCounter();
  double delta_time = 0, now_time = 0;

  while (g_Running)
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      ImGui_ImplSDL2_ProcessEvent(&event);
      switch (event.type)
      {
      case SDL_QUIT:
        g_Running = false;
        break;
      default:
        break;
      }
    }

    now_time = SDL_GetPerformanceCounter();
    delta_time = (now_time - last_time) / SDL_GetPerformanceFrequency();
    last_time = now_time;

    app->Update(delta_time);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    app->ImGuiUpdate();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    app->Render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(g_Window);
  }
}

void NUMINA_API Numina_Quit(App *app)
{
  SDL_GL_DeleteContext(g_GLContext);

  SDL_DestroyWindow(g_Window);

  SDL_Quit();
}
} // namespace tt
