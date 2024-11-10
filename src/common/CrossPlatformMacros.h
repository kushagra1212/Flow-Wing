// CrossPlatformMacros.h

#pragma once

#ifdef _WIN32
#include <Windows.h>
#include <minwindef.h> 

// Undefine conflicting macros
#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif
#else 
#include <unistd.h>
#endif

