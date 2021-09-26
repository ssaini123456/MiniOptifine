#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <vector>

#include "tlhelp32.h"

class GameUtil
{
public:
	static uintptr_t findAddressFromPointer(HANDLE proc, uintptr_t provided_ptr, std::vector<uint32_t> provided_offsets);
	static uint32_t	 getGameProcessId();
	static uintptr_t getGameModule(uint32_t processId);
};
