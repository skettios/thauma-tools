#ifndef NUMINA_APPLAYER_H
#define NUMINA_APPLAYER_H

#include "Defines.h"

#include <cstdint>

union SDL_Event;

namespace tt
{
class NUMINA_API AppLayer
{
public:
  virtual ~AppLayer();

  virtual void OnPush();
  virtual void OnPop();

  virtual bool OnSDLEvent(SDL_Event *);

  virtual void OnUpdate(float);
  virtual void OnRender();
  virtual void OnImGui();

protected:
  class App &GetApp();

private:
};

class NUMINA_API DebugLayer : public AppLayer
{
public:
  void OnUpdate(float delta_time) override;
  void OnImGui() override;

private:
  uint32_t m_FPS;
  float m_FrameTime;
};

} // namespace tt

#endif // NUMINA_APPLAYER_H
