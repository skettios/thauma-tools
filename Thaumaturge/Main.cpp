#include <iostream>

#include <Numina.h>
#include <Numina/Main.h>

#include <imgui.h>

class TestLayer : public tt::AppLayer
{
public:
  void OnImGui() override
  {
    ImGui::Begin("Test");
    ImGui::End();
  }
};

int main(int argc, char **argv)
{
  std::cout << "Thaumaturge" << std::endl;
  tt::App *app = new tt::App();
  app->InsertResource(new tt::WindowDescriptor{"Thaumaturge"});

  app->PushLayer(new tt::DebugLayer);
  app->PushLayer(new TestLayer);

  return 0;
}
