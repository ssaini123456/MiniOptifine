#include "GameUtil.h"

uintptr_t GameUtil::findAddressFromPointer(HANDLE proc, uintptr_t provided_ptr, std::vector<DWORD> provided_offsets)
{
    uintptr_t address = provided_ptr;

    for (DWORD i = 0; i < provided_offsets.size(); ++i) {
        ReadProcessMemory(proc, (BYTE*)address, &address, sizeof(address), 0);
        address += provided_offsets[i];
    }


    return address;
}

DWORD GameUtil::getGameProcessId(const wchar_t* proc_name)
{
    DWORD processID = 0;
    HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshotHandle != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 processEntry;
        processEntry.dwSize = sizeof(processEntry);
        if (Process32First(snapshotHandle, &processEntry)) {
            do {
                if (!_wcsicmp(processEntry.szExeFile, proc_name)) {
                    processID = processEntry.th32ProcessID;

                    break;
                }
            } while (Process32Next(snapshotHandle, &processEntry));

        }
    }

    CloseHandle(snapshotHandle);
    return processID;
}

uintptr_t GameUtil::getGameModule(DWORD processID)
{
    uintptr_t gameModuleAddress = 0;
    const wchar_t* gameName = L"Minecraft.Windows.exe";
    HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);

    if (snapshotHandle != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);


        if (Module32First(snapshotHandle, &modEntry)) {

            do {

                if (!_wcsicmp(modEntry.szModule, gameName)) {
                    gameModuleAddress = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(snapshotHandle, &modEntry));

        }
    }
    CloseHandle(snapshotHandle);
    return gameModuleAddress;
}
