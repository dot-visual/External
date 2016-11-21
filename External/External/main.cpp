#include <iostream>
#include "Windows.h"
#include <TlHelp32.h>
#include <stdint.h>
#include <fstream>
#include <string>

DWORD dwLocalPlayer = 0xA9053C;
DWORD oFlags = 0x00000100;
DWORD dwForceJump = 0x4F48A94;
DWORD dwProcessId = 0;
HANDLE hProcess = NULL;
HWND hWindow = NULL;
int vFlags;
DWORD dwClientDLL;
DWORD dwEngine;
DWORD dwAngl = 0x4D0C;
DWORD myAngl;
DWORD aEntityList = 0x4AB1F54;
DWORD oCrosshair = 0x0000AA64;
DWORD oTeamNum = 0x000000F0;
DWORD oEntityLoopDist = 0x10;
DWORD oHealth = 0x000000FC;
DWORD dwForceAttack = 0x2EF1F40;
DWORD m_vecOrigin = 0x00000134;
DWORD m_vecVelocity  = 0x110;

boolean trig = false;
boolean bhop = false;
bool shot = false;

int TRIGGER_BUTTON = 0x47;

bool InitializeProcessData( const std::string &strWindowTitle, HWND &hWindow, DWORD &dwProcessId, HANDLE &hProcess )
{
	// Als erstes fragen wir ab, ob das Window Handle von FindWindow, welches wir in
	// hWindow passen nicht 0 ist. Falls doch, verlassen wir die funktion mit einem false.
	hWindow = FindWindowA(NULL, strWindowTitle.c_str());
	if(!hWindow)
		return false;

	// Als naechstes werden wir anhand des Window Handles die Prozess Id ergattern.
	GetWindowThreadProcessId( hWindow, &dwProcessId );

	// Falls diese 0 sein sollte, verlassen wir die Funktion mit einem false.
	if( !dwProcessId )
		return false;

	// Als letztes fragen wir, ob das Handle zum Prozess, welches wir von OpenProcess bekommen
	// nicht invalid ist und geben diesen Wert zurueck

	return( ( hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, dwProcessId ) ) != INVALID_HANDLE_VALUE );
}

DWORD_PTR GetModuleBaseExternal( const std::string &strModuleName, const DWORD &dwProcessId )
{
	// Als erstes erstellen wir ein snapshot handle von der gepassten Prozess Id
	// und ueberpruefen, ob das handle invalid ist. Falls ja, verlassen wir die Funktion.
	auto hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, dwProcessId );
	if( hSnapshot == INVALID_HANDLE_VALUE )
		return 0;

	DWORD_PTR dwModuleBase = 0;
	MODULEENTRY32 ModuleEntry = { sizeof( MODULEENTRY32 ) };
	// Wenn die folgende Funktion nicht 0 zurueck gibt, fangen wir an durch alle
	// Module von dem erstellten snapshot zu loopen.
	if( Module32First( hSnapshot, &ModuleEntry ) )
	{
#ifdef _UNICODE
		// Falls der Zeichensatz auf UNICODE stehen sollte, benoetigen wir fuer unseren
		// String Vergleich einen UNICODE( Original: wchar_t ) String.
		std::wstring wstrModuleName( strModuleName.begin( ), strModuleName.end( ) );
#endif
		auto bComparedStrings = false;
		do
		{
			// Nun vergleichen wir unseren angeforderten Namen des Modules mit dem aktuellen.
#ifdef _UNICODE
			bComparedStrings = ( !wstrModuleName.compare( ModuleEntry.szModule ) );
#else
			bComparedStrings = ( !strModuleName.compare( ModuleEntry.szModule ) );
#endif

			// Falls die beiden Strings miteinander uebereinstimmen, verlassen wir die Schleife.
			if( bComparedStrings )
			{
				dwModuleBase = ( DWORD_PTR )ModuleEntry.modBaseAddr;
				break;
			}
		} while( Module32Next( hSnapshot, &ModuleEntry ) );
	}

	// Bevor wir die Funktion verlassen, sollten wir das erstellte snapshot handle schliessen.
	CloseHandle( hSnapshot );

	return dwModuleBase;
}


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

struct MyPlayer
{
	DWORD LocalPlayer;
	int Team; //2 T, 3 CT
	float Position[3];
	int Flags;
	int CrosshairID;

	void ReadInformation()
	{
		LocalPlayer = ReadMemory<DWORD>(dwClientDLL + dwLocalPlayer);
		Team = ReadMemory<int>(LocalPlayer + oTeamNum);
		Flags = ReadMemory<int>(LocalPlayer+ oFlags);
		CrosshairID = ReadMemory<int>(LocalPlayer+ oCrosshair);

	}
	void bhop()
	{
		ReadInformation();
		int vJump = 5;
		if (GetAsyncKeyState(0x20))
		{
			if(Flags == 257)
			{
				vJump = 5;
			}
			if(Flags == 256)
			{
				vJump = 4;
			}
			WriteMemory<int>(dwClientDLL + dwForceJump, vJump);
		}
	}

	void trigger()
	{
		DWORD enemyInCH;
		int enemyHealth;
		int enemyTeam;
		int myval = 5;
		float pos[3];

		ReadInformation();
		enemyInCH = ReadMemory<DWORD>(dwClientDLL + aEntityList + ((CrosshairID - 1) * oEntityLoopDist));
		enemyHealth = ReadMemory<DWORD>(enemyInCH + oHealth);
		enemyTeam = ReadMemory<DWORD>(enemyInCH + oTeamNum);
		pos[0] = ReadMemory<float>(enemyInCH + m_vecOrigin); // X
		pos[1] = ReadMemory<float>(enemyInCH + m_vecOrigin + 0x4); // Y
		pos[2] = ReadMemory<float>(enemyInCH + m_vecOrigin + 0x8); // Z

		if(GetAsyncKeyState(TRIGGER_BUTTON) && Team != enemyTeam && enemyHealth > 0)
		{
			WriteMemory(dwClientDLL + dwForceAttack, myval);
			myval = 4;
			Sleep(1);
			WriteMemory(dwClientDLL + dwForceAttack, myval);
			myval = 5;
			//Sleep(1000);
		}
	}
};

int main( )
{
	std::ifstream ifs("config.txt");
	std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
	std::cout << "CONFIG LOADED" << std::endl;
	TRIGGER_BUTTON = std::stoi(content);

	std::cout << "Waiting for Counter-Strike: Global Offensive...";

	while( !InitializeProcessData( "Counter-Strike: Global Offensive", hWindow, dwProcessId, hProcess ) )
	{
		std::cout << ".";
		Sleep( 1000 );
	}

	std::cout << "ok!" << std::endl;

	dwClientDLL = GetModuleBaseExternal( "client.dll", dwProcessId );
	dwEngine = GetModuleBaseExternal("engine.dll", dwProcessId);
	//MODULEENTRY32 entry;
	std::cout << "found client.dll at 0x" << std::hex << dwClientDLL << std::endl;
	std::cout << "found engine.dll at 0x" << std::hex << dwEngine << std::endl;
	MyPlayer me;
	me.ReadInformation();

	std::cout<< "Team: " << std::hex << me.Team << std::endl;
	std::cout<< "Flags: " << std::hex << me.Flags << std::endl;

	std::cout<< "LocalPlayer: 0x" << std::hex << dwLocalPlayer << std::endl;

	while (true)
	{
		if(bhop)
		{
			me.bhop();
		}
		if(trig)
		{
			me.trigger();
		}

		if (GetAsyncKeyState(0x70))
		{
			bhop = !bhop;
			std::cout << "bhop: " << bhop << std::endl;
			Sleep(1000);
		}
		if (GetAsyncKeyState(0x71))
		{
			trig = !trig;
			std::cout << "trigger: " << trig << std::endl;
			Sleep(1000);
		}
		if (GetAsyncKeyState(0x72))
		{
			break;
		}
	}

	CloseHandle( hProcess );

	system( "cls" );
	main();
	return 1;
}