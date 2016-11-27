#pragma once
#ifndef PROCMEM_H //If Not Defined
#define PROCMEM_H //Define Now
#include <Windows.h>
#include <string>

class ProcMemory
{
protected:
	HANDLE hProcess;
public:
	ProcMemory();
	~ProcMemory();

	template<typename T>
	T ReadMemory(DWORD Address)
	{
		T read;
		ReadProcessMemory(hProcess, (PBYTE*) Address, &read, sizeof(T),0);
		return read;
	}

	template<typename T>
	void WriteMemory(DWORD Address, T Value)
	{
		WriteProcessMemory(hProcess, (PBYTE*) Address, &Value, sizeof(T), 0);
	}

	virtual bool InitializeProcessData(const std::string &strWindowTitle, HWND &hWindow, DWORD &dwProcessId, HANDLE &hProcess); 
	virtual DWORD_PTR GetModuleBaseExternal(const std::string &strModuleName, const DWORD &dwProcessId);

private:
};
extern ProcMemory procMem;
#endif
