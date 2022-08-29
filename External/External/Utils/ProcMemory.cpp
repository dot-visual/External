#include "ProcMemory.h"

ProcMemory* procMem;

ProcMemory::~ProcMemory(void) {
	CloseHandle(ProcMemory::hProcess);
}

bool ProcMemory::ReadMemory(DWORD_PTR dwAddress, LPVOID lpBuffer, DWORD_PTR dwSize)
{
	SIZE_T Out = NULL;
	return (ReadProcessMemory(hProcess, (LPCVOID)dwAddress, lpBuffer, dwSize, &Out) == TRUE);
}

bool ProcMemory::WriteMemory(DWORD_PTR dwAddress, LPCVOID lpBuffer, DWORD_PTR dwSize)
{
	SIZE_T Out = NULL;

	return (WriteProcessMemory(hProcess, (LPVOID)dwAddress, lpBuffer, dwSize, &Out) == TRUE);
}

bool ProcMemory::InitializeProcessData(const std::string& strWindowTitle, HWND& hWindow, DWORD& dwProcessId, HANDLE& hProcess)
{
	hWindow = FindWindowA(NULL, strWindowTitle.c_str());
	if (!hWindow)
		return false;

	GetWindowThreadProcessId(hWindow, &dwProcessId);

	if (!dwProcessId)
		return false;

	return((ProcMemory::hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId)) != INVALID_HANDLE_VALUE);
}

DWORD_PTR ProcMemory::GetModuleBaseExternal(const std::string& strModuleName, const DWORD& dwProcessId)
{
	auto hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
	if (hSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	DWORD_PTR dwModuleBase = 0;
	MODULEENTRY32 ModuleEntry = { sizeof(MODULEENTRY32) };
	if (Module32First(hSnapshot, &ModuleEntry))
	{
#ifdef _UNICODE
		std::wstring wstrModuleName(strModuleName.begin(), strModuleName.end());
#endif
		auto bComparedStrings = false;
		do
		{
#ifdef _UNICODE
			bComparedStrings = (!wstrModuleName.compare(ModuleEntry.szModule));
#else
			bComparedStrings = (!strModuleName.compare(ModuleEntry.szModule));
#endif
			if (bComparedStrings)
			{
				dwModuleBase = (DWORD_PTR)ModuleEntry.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnapshot, &ModuleEntry));
	}
	CloseHandle(hSnapshot);
	return dwModuleBase;
}