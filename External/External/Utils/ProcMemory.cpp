#include "ProcMemory.h"

ProcMemory* procMem = new ProcMemory();

ProcMemory::~ProcMemory(void) {
	CloseHandle(ProcMemory::hProcess);
}

// Reads Memory on specified Address
bool ProcMemory::ReadMemory(DWORD_PTR dwAddress, LPVOID lpBuffer, DWORD_PTR dwSize)
{
	SIZE_T Out = NULL;

	return (ReadProcessMemory(hProcess, (LPCVOID)dwAddress, lpBuffer, dwSize, &Out) == TRUE);
}

// Writes Memory on specified Address
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
	// Als erstes erstellen wir ein snapshot handle von der gepassten Prozess Id
	// und ueberpruefen, ob das handle invalid ist. Falls ja, verlassen wir die Funktion.
	auto hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
	if (hSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	DWORD_PTR dwModuleBase = 0;
	MODULEENTRY32 ModuleEntry = { sizeof(MODULEENTRY32) };
	// Wenn die folgende Funktion nicht 0 zurueck gibt, fangen wir an durch alle
	// Module von dem erstellten snapshot zu loopen.
	if (Module32First(hSnapshot, &ModuleEntry))
	{
#ifdef _UNICODE
		// Falls der Zeichensatz auf UNICODE stehen sollte, benoetigen wir fuer unseren
		// String Vergleich einen UNICODE( Original: wchar_t ) String.
		std::wstring wstrModuleName(strModuleName.begin(), strModuleName.end());
#endif
		auto bComparedStrings = false;
		do
		{
			// Nun vergleichen wir unseren angeforderten Namen des Modules mit dem aktuellen.
#ifdef _UNICODE
			bComparedStrings = (!wstrModuleName.compare(ModuleEntry.szModule));
#else
			bComparedStrings = (!strModuleName.compare(ModuleEntry.szModule));
#endif

			// Falls die beiden Strings miteinander uebereinstimmen, verlassen wir die Schleife.
			if (bComparedStrings)
			{
				dwModuleBase = (DWORD_PTR)ModuleEntry.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnapshot, &ModuleEntry));
	}

	// Bevor wir die Funktion verlassen, sollten wir das erstellte snapshot handle schliessen.
	CloseHandle(hSnapshot);

	return dwModuleBase;
}