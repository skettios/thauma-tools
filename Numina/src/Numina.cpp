#include "Numina.h"
#include <iostream>

#include "Numina/Main.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace tt
{
static GLFWwindow *g_Window = nullptr;
static ImGuiContext *g_ImGuiContext = nullptr;

ImGuiContext NUMINA_API *Numina_GetImGuiContext()
{
  return g_ImGuiContext;
}

int NUMINA_API Numina_Initialize(App *app)
{
  WindowDescriptor window_descriptor = app->GetResource<WindowDescriptor>();
  ClearColor clear_color = app->GetResource<ClearColor>();

  if (!glfwInit())
  {
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  g_Window = glfwCreateWindow(window_descriptor.m_Width, window_descriptor.m_Height, window_descriptor.m_Title.c_str(),
                              NULL, NULL);
  if (!g_Window)
    return -2;

  glfwMakeContextCurrent(g_Window);
  gladLoadGL((GLADloadfunc)glfwGetProcAddress);

  glfwShowWindow(g_Window);

  glClearColor(clear_color.m_Red, clear_color.m_Green, clear_color.m_Blue, 1.f);

  IMGUI_CHECKVERSION();
  g_ImGuiContext = ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(g_Window, true);
  ImGui_ImplOpenGL3_Init("#version 150");

  return 0;
}

void NUMINA_API Numina_Run(App *app)
{
  double last_time = glfwGetTimerValue();
  double delta_time = 0, now_time = 0;

  while (!glfwWindowShouldClose(g_Window))
  {
    now_time = glfwGetTimerValue();
    delta_time = (now_time - last_time) / glfwGetTimerFrequency();
    last_time = now_time;

    glfwPollEvents();

    app->Update(delta_time);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    app->ImGuiUpdate();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    app->Render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(g_Window);
  }
}

void NUMINA_API Numina_Quit(App *app)
{
  glfwDestroyWindow(g_Window);
  glfwTerminate();
}
} // namespace tt
