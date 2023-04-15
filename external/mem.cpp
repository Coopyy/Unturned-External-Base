#include "mono.h"

//nulls memory

//Vars to use
DWORD64 baseAddress = NULL;

//Vars for process snapshot
HANDLE hProcSnap = NULL;
PROCESSENTRY32 procEntry32;

//Vars for module snapshot
HANDLE hModuleSnap = NULL;
MODULEENTRY32 modEntry32;

//Process ID of attached proc
DWORD pID = NULL;

//Handle to process
HANDLE hProc = NULL;

bool attatchProc(const char* procName)
{
	procEntry32.dwSize = sizeof(PROCESSENTRY32);

	hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcSnap == INVALID_HANDLE_VALUE)
	{
		Log("Failed to get process snapshot handle");
		return false;
	}

	while (Process32Next(hProcSnap, &procEntry32))
	{
		if (!strcmp(procName, procEntry32.szExeFile))
		{
			Log("%s found (%u)", procEntry32.szExeFile, procEntry32.th32ProcessID);
			hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procEntry32.th32ProcessID);
			pID = procEntry32.th32ProcessID;

			if (hProc == NULL)
				Log("Failed to get process handle");
			CloseHandle(hProcSnap);
			return true;
		}
	}

	Log("%s was not found", procName);
	CloseHandle(hProcSnap);
	return false;
}

DWORD64 getModule(const char* moduleName)
{
	hModuleSnap = INVALID_HANDLE_VALUE;
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);

	if (hModuleSnap == INVALID_HANDLE_VALUE)
	{
		Log("Failed to get modules");
		CloseHandle(hModuleSnap);
		return 0;
	}

	modEntry32.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hModuleSnap, &modEntry32))
	{
		if (!strcmp(moduleName, modEntry32.szModule))
		{
			Log("%s -> 0x%p", modEntry32.szModule, (DWORD64)modEntry32.modBaseAddr);

			CloseHandle(hModuleSnap);
			return (DWORD64)modEntry32.modBaseAddr;
		}
	}

	while (Module32Next(hModuleSnap, &modEntry32))
	{
		if (!strcmp(moduleName, modEntry32.szModule))
		{
			Log("%s -> 0x%p", modEntry32.szModule, (DWORD64)modEntry32.modBaseAddr);

			CloseHandle(hModuleSnap);
			return (DWORD64)modEntry32.modBaseAddr;
		}
	}
	Log("%s not found", moduleName);
	CloseHandle(hModuleSnap);
	return false;
}

std::uint32_t find(const char* proc)
{
	auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(pe);

	if (Process32First(snapshot, &pe))
	{
		while (Process32Next(snapshot, &pe))
		{
			if (!strcmp(proc, pe.szExeFile))
			{
				CloseHandle(snapshot);
				return pe.th32ProcessID;
			}
		}
	}
	CloseHandle(snapshot);
	return 0;
}

namespace mem
{
	void init()
	{
		if (attatchProc("Unturned.exe"))
		{
			baseAddress = getModule("mono-2.0-bdwgc.dll");
		}
	}
}