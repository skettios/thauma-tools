#include <iostream>

#include <Numina.h>
#include <Numina/Main.h>

#include <imgui.h>
#include <glad/gl.h>

class TestLayer : public tt::AppLayer
{
public:
  void OnImGui() override
  {
    ImGui::Begin("Test");
    ImGui::Text("Hello, World!");
    ImGui::End();
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
