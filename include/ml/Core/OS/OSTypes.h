#pragma once

#ifdef WIN32
#include <Windows.h>
#endif

namespace ml {

#ifdef WIN32
using ProcessHandle = HANDLE;
using ProcessId = DWORD;
#endif

}
