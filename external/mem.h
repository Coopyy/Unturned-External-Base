#pragma  once
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>

#include "log.h"

// change me to use your driver and stuff

//Vars to use
extern DWORD64 baseAddress;

//Vars for process snapshot
extern HANDLE hProcSnap;
extern PROCESSENTRY32 procEntry32;

//Vars for module snapshot
extern HANDLE hModuleSnap;
extern MODULEENTRY32 modEntry32;

//Process ID of attached proc
extern DWORD pID;

//Handle to process
extern HANDLE hProc;

// change to driver write mem
template <class dataType>
inline void write(dataType valToWrite, DWORD64 addressToWrite)
{
	WriteProcessMemory(hProc, (PVOID)addressToWrite, &valToWrite, sizeof(dataType), 0);
}

// change to driver read mem
template <class dataType>
inline dataType read(DWORD64 addressToRead)
{
	dataType rpmBuffer;
	ReadProcessMemory(hProc, (PVOID)addressToRead, &rpmBuffer, sizeof(dataType), 0);
	return rpmBuffer;
}

// change to driver read mem
inline void read_buffer(DWORD64 addressToRead, void* buffer, size_t size)
{
	ReadProcessMemory(hProc, (PVOID)addressToRead, buffer, size, 0);
}

//Attaches to process and gives ALL_ACCESS so you can rpm/wpm for your hack
extern bool attatchProc(char* procName);

extern DWORD64 getModule(char* moduleName);
extern std::uint32_t getProcessId(const char* proc);

namespace Memory
{
	extern void init();
}


// idk what substances i was on thinking this was smart
//template <class dataType>
//class Field
//{
//	uintptr_t instance;
//	uintptr_t offset;
//public:
//	Field(uintptr_t ins, uintptr_t ofs) : instance{ ins }, offset { ofs }
//	{
//
//	}
//	dataType Read()
//	{
//		return read<dataType>(instance + offset);
//	}
//	void Write(dataType value)
//	{
//		write<dataType>(value, instance + offset);
//	}
//};
