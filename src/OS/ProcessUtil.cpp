#include "Core/OS/ProcessUtil.h"

#include <TlHelp32.h>

namespace ml {

ProcessHandle findProcess(const std::wstring& processName, DWORD access) {
    HANDLE snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapShot == INVALID_HANDLE_VALUE) {
        return nullptr;
    }

    DWORD pid = -1;
    PROCESSENTRY32W entry{ sizeof(entry) };

    if (Process32FirstW(snapShot, &entry)) {
        do {
            if (processName == entry.szExeFile) {
                pid = entry.th32ProcessID;
                break;
            }
        } while (Process32NextW(snapShot, &entry));
    }

    CloseHandle(snapShot);

    if (pid == -1) {
        return nullptr;
    }

    return OpenProcess(access, FALSE, pid);
}

bool tryTerminateProcess(const std::wstring& processName, int returnCode) {
    ProcessHandle handle = findProcess(processName);

    if (handle == nullptr) {
        return false; // process already closed
    }

    return TerminateProcess(handle, returnCode);
}

bool terminateProcess(ProcessHandle handle, int returnCode) {
    return TerminateProcess(handle, returnCode);
}

}
