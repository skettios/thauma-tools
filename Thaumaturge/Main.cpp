#include <iostream>

#include <Numina.h>
#include <Numina/Main.h>

#include <SDL_events.h>

#include <glad/gl.h>
#include <imgui.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

const char *vss = R"(
#version 330 core

layout (location = 0) in vec3 aPos;
void main()
{
  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

const char *fss = R"(
#version 330 core

out vec4 frag_color;

void main()
{
  frag_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

struct Vertex
{
  glm::vec2 position;
  glm::vec3 color;
};

class TestLayer : public tt::AppLayer
{
  uint32_t vbo, vao;
  uint32_t shader_program;

public:
  void OnBuild() override
  {
    float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    auto PrintStatus = [](uint32_t shader, bool is_program = false) {
      int32_t success;
      char info_log[512];
      if (is_program)
      {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
          glGetProgramInfoLog(shader, 512, NULL, info_log);
          std::cout << info_log << std::endl;
        }
      }
      else
      {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
          glGetShaderInfoLog(shader, 512, NULL, info_log);
          std::cout << info_log << std::endl;
        }
      }
    };

    uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vss, NULL);
    glCompileShader(vertex_shader);
    PrintStatus(vertex_shader);

    uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fss, NULL);
    glCompileShader(fragment_shader);
    PrintStatus(fragment_shader);

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    PrintStatus(shader_program, true);
  }

  bool OnSDLEvent(SDL_Event *event) override
  {
    if (event->type == SDL_KEYUP)
    {
      if (event->key.keysym.sym == SDLK_ESCAPE)
      {
        GetApp().Exit();
        return false;
      }
      if (event->key.keysym.sym == SDLK_F8)
      {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        return false;
      }
      if (event->key.keysym.sym == SDLK_F9)
      {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        return false;
      }
    }
    return true;
  }

  void OnImGui() override
  {
    ImGui::Begin("Test");
    ImGui::Text("Hello, World!");
    ImGui::End();
  }

  void OnRender() override
  {
    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }
};

int main(int argc, char **argv)
{
  std::cout << "Thaumaturge" << std::endl;
  tt::App *app = new tt::App();
  app->InsertResource(new tt::WindowDescriptor{"Thaumaturge"});
  app->InsertResource(new tt::ClearColor{100 / 255.f, 149 / 255.f, 237 / 255.f});

  app->PushLayer(new tt::DebugLayer);
  app->PushLayer(new TestLayer);

  return 0;
}
