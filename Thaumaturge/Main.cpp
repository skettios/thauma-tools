#include <iostream>

#include <Numina.h>

namespace tt
{
class Thaumaturge : public App
{
public:
  void OnUpdate() override
  {
  }

  void OnRender() override
  {
  }
};
} // namespace tt

int main(int argc, char **argv)
{
  std::cout << "Thaumaturge" << std::endl;
  tt::App *app = new tt::Thaumaturge();
  app->InsertResource(new tt::WindowDescriptor{"Thaumaturge"});
  app->InsertResource(new tt::ClearColor{0.f, 1.f, 1.f});

  return 0;
}
