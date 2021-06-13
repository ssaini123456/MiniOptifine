#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <vector>

#include "tlhelp32.h"

class GameUtil
{
public:
	static uintptr_t findAddressFromPointer(HANDLE proc, uintptr_t provided_ptr, std::vector<DWORD> provided_offsets);
	static DWORD	 getGameProcessId(const wchar_t* proc_name);
	static uintptr_t getGameModule(DWORD processId);

};

