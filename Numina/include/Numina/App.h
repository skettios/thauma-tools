#ifndef NUMINA_APP_H
#define NUMINA_APP_H

#include "Defines.h"
#include "AppResources.h"

#include <unordered_map>
#include <typeindex>

namespace tt
{
class NUMINA_API App
{
public:
  App();
  ~App();

  virtual void OnUpdate() = 0;
  virtual void OnRender() = 0;

  void InsertResource(AppResource *);

  template <typename T> T &GetResource() const
  {
    return static_cast<T &>(*m_Resources.at(std::type_index(typeid(T))));
  }

private:
  std::unordered_map<std::type_index, AppResource *> m_Resources;
};
} // namespace tt

#endif // NUMINA_APP_H
