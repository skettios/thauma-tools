#ifndef NUMINA_APP_H
#define NUMINA_APP_H

#include "Defines.h"

namespace tt
{
class NUMINA_API App
{
public:
  App();
  ~App();

  virtual void OnUpdate() = 0;
  virtual void OnRender() = 0;

private:
};
} // namespace tt

#endif // NUMINA_APP_H
