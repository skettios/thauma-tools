#ifndef NUMINA_APP_H
#define NUMINA_APP_H

#include "Defines.h"
#include "AppResources.h"
#include "AppLayer.h"

#include <unordered_map>
#include <typeindex>

namespace tt
{
class NUMINA_API App
{
public:
  App();
  ~App();

  void Update(float);
  void ImGuiUpdate();
  void Render();

  void InsertResource(AppResource *);
  void PushLayer(AppLayer *);

  template <typename T> T &GetResource() const
  {
    return static_cast<T &>(*m_Resources.at(std::type_index(typeid(T))));
  }

  AppLayer *PopLayer();

private:
  std::unordered_map<std::type_index, AppResource *> m_Resources;
  std::vector<AppLayer *> m_Layers;
};
} // namespace tt

#endif // NUMINA_APP_H
