#include <iostream>
#include "Windows.h"
#include <TlHelp32.h>
#include <stdint.h>

DWORD LocalPlayer = 0x00A8F53C;
DWORD oFlags = 0x00000100;
DWORD Jump = 0x04F47AD4;
DWORD dwProcessId = 0;
HANDLE hProcess = NULL;
HWND hWindow = NULL;
int vFlags;
DWORD dwClientDLL;

DWORD aEntityList = 0x04AB0F94;
DWORD oCrosshair = 0x0000AA64;
DWORD oTeamNum = 0x000000F0;
DWORD oEntityLoopDist = 0x10;
DWORD oHealth = 0x000000FC;
DWORD aForceAttack = 0x02EF0F98;
DWORD m_vecOrigin = 0x00000134;

int crosshairID;
int teamNum; //2 T, 3 CT
bool InitializeProcessData( const std::string &strWindowTitle, HWND &hWindow, DWORD &dwProcessId, HANDLE &hProcess )
{
	// Als erstes fragen wir ab, ob das Window Handle von FindWindow, welches wir in
	// hWindow passen nicht 0 ist. Falls doch, verlassen wir die funktion mit einem false.
	if( !( hWindow = FindWindowA( NULL, strWindowTitle.c_str( ) ) ) )
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

void bhop()
{
	ReadProcessMemory(hProcess, (PBYTE*) (LocalPlayer + oFlags), &vFlags,sizeof(int),0);
	//std::cout << "Flags value: " << vFlags << std::endl;
}

struct MyPlayer
{
	DWORD myLocalPlayer;
	int Team;
	float Position[3];
	int myFlags;

	void ReadInformation()
	{
			ReadProcessMemory(hProcess, (PBYTE*) (dwClientDLL + LocalPlayer), &myLocalPlayer, sizeof(DWORD), 0);
			ReadProcessMemory(hProcess, (PBYTE*) (myLocalPlayer + oTeamNum), &Team, sizeof(int), 0);
			ReadProcessMemory(hProcess, (PBYTE*) (myLocalPlayer + oFlags), &myFlags,sizeof(int),0);
	}
};

void trigger()
{
	DWORD enemyInCH;
	int enemyHealth;
	int enemyTeam;
	float velo[3];

	ReadProcessMemory(hProcess, (PBYTE*) (LocalPlayer + oCrosshair), &crosshairID, sizeof(int), 0);
	ReadProcessMemory(hProcess, (PBYTE*) (LocalPlayer + oTeamNum), &teamNum, sizeof(int), 0);
	ReadProcessMemory(hProcess, (PBYTE*) (dwClientDLL + aEntityList + ((crosshairID - 1) * oEntityLoopDist)), &enemyInCH,sizeof(DWORD), 0);
	ReadProcessMemory(hProcess, (PBYTE*) (enemyInCH + oTeamNum),&enemyTeam,sizeof(int),0);
	ReadProcessMemory(hProcess, (PBYTE*) (enemyInCH + oHealth), &enemyHealth, sizeof(int), 0);
	ReadProcessMemory(hProcess, (PBYTE*) (enemyInCH + m_vecOrigin), &velo,sizeof(float),0);
	//std::cout << "enemyTeam: " << enemyTeam << std::endl;
	if(teamNum != enemyTeam && enemyHealth > 0)
	{
		mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
		mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
		Sleep(1);
		std::cout << "loc1: " << velo[1] << std::endl;;
	}

	
}

int main( )
{
	std::cout << "Waiting for Counter-Strike: Global Offensive...";

	while( !InitializeProcessData( "Counter-Strike: Global Offensive", hWindow, dwProcessId, hProcess ) )
	{
		std::cout << ".";
		Sleep( 1000 );
	}

	std::cout << "ok!" << std::endl;

	dwClientDLL = GetModuleBaseExternal( "client.dll", dwProcessId );
	MODULEENTRY32 entry;
	std::cout << "found client.dll at 0x" << std::hex << dwClientDLL << std::endl;
	//ReadProcessMemory(hProcess, (PBYTE*) (dwClientDLL + LocalPlayer), &LocalPlayer, sizeof(DWORD), 0);
	MyPlayer ich;
	ich.ReadInformation();
	std::cout<< "Team: " << std::hex << ich.Team << std::endl;
	std::cout<< "Flags: " << std::hex << ich.myFlags << std::endl;

	std::cout<< "LocalPlayer: 0x" << std::hex << LocalPlayer << std::endl;

	while (true)
	{
		trigger();
		bhop();
		//std::cout << "Flags value: " << vFlags << std::endl;
		if(vFlags == 257 && GetAsyncKeyState(0x20))
		{
			keybd_event(MapVirtualKey(0x20,0),0x39, KEYEVENTF_EXTENDEDKEY,0);
			keybd_event(MapVirtualKey(0x20,0),0x39,KEYEVENTF_KEYUP,0);
			Sleep(1);
		}
	}

	/*
	while (true)
	{
	bhop();
	//std::cout << "Flags value: " << vFlags << std::endl;
	if(vFlags == 257 && GetAsyncKeyState(0x20))
	{
	keybd_event(MapVirtualKey(0x20,0),0x39, KEYEVENTF_EXTENDEDKEY,0);
	keybd_event(MapVirtualKey(0x20,0),0x39,KEYEVENTF_KEYUP,0);
	Sleep(1);
	}
	}
	*/

	CloseHandle( hProcess );

	system( "pause" );

	return 1;
}