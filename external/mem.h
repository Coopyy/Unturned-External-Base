#pragma  once
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>

#include "log.h"

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

//WPM wrapper - Lets us call WriteProcessMemory MUCH more easily (with less args)
template <class dataType>
inline void write(dataType valToWrite, DWORD64 addressToWrite)
{
	WriteProcessMemory(hProc, (PVOID)addressToWrite, &valToWrite, sizeof(dataType), 0);
}

//RPM wrapper - Lets us call ReadProcessMemory MUCH more easily (with less args)
template <class dataType>
inline dataType read(DWORD64 addressToRead)
{
	//Stores the value of the address being read

	dataType rpmBuffer;
	//RPM
	ReadProcessMemory(hProc, (PVOID)addressToRead, &rpmBuffer, sizeof(dataType), 0);

	//Return the value that was read
	return rpmBuffer;
}

//Attaches to process and gives ALL_ACCESS so you can rpm/wpm for your hack
extern bool attatchProc(char* procName);

//Gets the base address of a desired module within the process you've attached to, so you can offset from it
extern DWORD64 getModule(char* moduleName);

extern std::uint32_t find(const char* proc);

namespace mem
{
	extern void init();
}

template <class dataType>
class Field
{
	uintptr_t instance;
	uintptr_t offset;
public:
	Field(uintptr_t ins, uintptr_t ofs) : instance{ ins }, offset { ofs }
	{

	}
	dataType Read()
	{
		return read<dataType>(instance + offset);
	}
	void Write(dataType value)
	{
		write<dataType>(value, instance + offset);
	}
};
