#pragma once

#ifdef WIN32
#include <Windows.h>
#endif

// TODO: Get rid of this shit

namespace ml {

#ifdef WIN32
using ProcessHandle = HANDLE;
using ProcessId = DWORD;
#endif

}
