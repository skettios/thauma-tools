#include "Numina.h"
#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace tt
{
static GLFWwindow *g_Window = nullptr;

int Numina_Initialize()
{
  if (!glfwInit())
  {
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  g_Window = glfwCreateWindow(1920, 1080, "Thaumaturge", NULL, NULL);
  if (!g_Window)
    return -2;

  glfwMakeContextCurrent(g_Window);
  gladLoadGL((GLADloadfunc)glfwGetProcAddress);

  glfwShowWindow(g_Window);

  glClearColor(0.f, 1.f, 1.f, 1.f);

  return 0;
}

void Numina_Run(App *app)
{
  double last_time = glfwGetTime(), timer = last_time;
  double delta_time = 0, now_time = 0;
  int frames = 0, updates = 0;

  while (!glfwWindowShouldClose(g_Window))
  {
    now_time = glfwGetTime();
    delta_time += (now_time - last_time) / (1.0 / 60.0);
    last_time = now_time;

    while (delta_time >= 1.0)
    {
      app->OnUpdate();
      updates++;
      delta_time--;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    app->OnRender();
    frames++;

    if (glfwGetTime() - timer > 1.0)
    {
      timer++;
      std::cout << "FPS: " << frames << " Updates: " << updates << std::endl;
      updates = 0, frames = 0;
    }

    glfwSwapBuffers(g_Window);
    glfwPollEvents();
  }
}

void Numina_Quit(App *app)
{
  glfwDestroyWindow(g_Window);
  glfwTerminate();
}
} // namespace tt
