#pragma once

#include <string>
#include "Core/OS/OSTypes.h"

namespace ml {

#ifdef WIN32
ProcessHandle findProcess(const std::wstring& processName, DWORD access = PROCESS_ALL_ACCESS);
bool tryTerminateProcess(const std::wstring& processName, int returnCode = -1);
bool terminateProcess(ProcessHandle handle, int returnCode = -1);
#endif


}
