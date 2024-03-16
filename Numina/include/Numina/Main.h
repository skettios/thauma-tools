#ifndef NUMINA_MAIN_H
#define NUMINA_MAIN_H

#if !defined(TT_NUMINA_EXPORT_BUILD)

#define main Numina_Main

#else

extern int Numina_Main(int, char **);

namespace tt
{
int NUMINA_API Numina_Initialize();
void NUMINA_API Numina_Run(class App *);
void NUMINA_API Numina_Quit(class App *);

App NUMINA_API *Numina_GetApplication();
} // namespace tt

#endif

#endif // NUMINA_MAIN_H
