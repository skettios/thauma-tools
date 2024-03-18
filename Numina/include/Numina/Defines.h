#ifndef NUMINA_DEFINES_H
#define NUMINA_DEFINES_H

#if defined(TT_NUMINA_EXPORT_BUILD)
#if defined(TT_PLATFORM_WIN32)
#define NUMINA_API __declspec(dllexport)
#else
#define NUMINA_API
#endif
#else
#if defined(TT_PLATFORM_WIN32)
#define NUMINA_API __declspec(dllimport)
#else
#define NUMINA_API
#endif
#endif

#endif // NUMINA_DEFINES_H
