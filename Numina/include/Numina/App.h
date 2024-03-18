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

  void ProcessSDLEvents(SDL_Event *);
  void Update(float);
  void ImGuiUpdate();
  void Render();

  void InsertResource(AppResource *);
  void PushLayer(AppLayer *);

  template <typename T> T &GetResource() const
  {
    return static_cast<T &>(*m_Resources.at(std::type_index(typeid(T))));
  }

  template <typename T> bool HasResource() const
  {
    return m_Resources.find(std::type_index(typeid(T))) != m_Resources.end();
  }

  AppLayer *PopLayer();

private:
  std::unordered_map<std::type_index, AppResource *> m_Resources;
  std::vector<AppLayer *> m_Layers;
};
} // namespace tt

#endif // NUMINA_APP_H
