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
  tt::App *app = new tt::Thaumaturge;

  return 0;
}
