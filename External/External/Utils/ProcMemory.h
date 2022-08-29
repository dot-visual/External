#ifndef PROCMEMORY_HEADER
#define PROCMEMORY_HEADER

#include <Windows.h>
#include <TlHelp32.h>
#include <string>

// Don't know anymore whom I copied this from 6 years ago, sorry
class ProcMemory
{
public:
	ProcMemory() = default;
	~ProcMemory(void);
	HANDLE hProcess{};

	bool ReadMemory(DWORD_PTR dwAddress, LPVOID lpBuffer, DWORD_PTR dwSize);
	bool WriteMemory(DWORD_PTR dwAddress, LPCVOID lpBuffer, DWORD_PTR dwSize);

	template<typename T>
	T ReadMemory(DWORD_PTR dwAddress, const T& tDefault = T())
	{
		T tRet;

		if (!ReadMemory(dwAddress, &tRet, sizeof(T)))
		{
			return tDefault;
		}

		return tRet;
	}

	template<typename T>
	bool WriteMemory(DWORD_PTR dwAddress, const T& tValue)
	{
		return WriteMemory(dwAddress, &tValue, sizeof(T));
	}

	bool InitializeProcessData(const std::string& strWindowTitle, HWND& hWindow, DWORD& dwProcessId, HANDLE& hProcess);
	DWORD_PTR GetModuleBaseExternal(const std::string& strModuleName, const DWORD& dwProcessId);

private:
};

extern ProcMemory* procMem;
#endif