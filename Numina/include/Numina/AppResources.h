#ifndef NUMINA_APPRESOURCES_H
#define NUMINA_APPRESOURCES_H

#include <cstdint>
#include <string>

namespace tt
{
struct AppResource
{
  virtual ~AppResource()
  {
  }
};

struct WindowDescriptor : AppResource
{
  std::string m_Title;
  uint32_t m_Width, m_Height;

  WindowDescriptor(std::string title = "NuminaApp", uint32_t width = 1920, uint32_t height = 1080)
      : m_Title(title), m_Width(width), m_Height(height)
  {
  }
};

struct ClearColor : AppResource
{
  float m_Red, m_Green, m_Blue;

  ClearColor(float r = 0.f, float g = 0.f, float b = 0.f) : m_Red(r), m_Green(g), m_Blue(b)
  {
  }
};

} // namespace tt

#endif // NUMINA_APPRESOURCES_H
