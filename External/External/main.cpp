#pragma once
#include "Offsets.h"
#include "Player.h"
#include "ProcMemory.h"
#include "Misc.h"

int main()
{
	while( !procMem.InitializeProcessData( "Counter-Strike: Global Offensive", hWindow, dwProcessId, hProcess ) )
	{
		std::cout << ".";
		Sleep( 1000 );
	}
	dwClientDLL = procMem.GetModuleBaseExternal("client.dll", dwProcessId);

	std::cout << "Found client.dll at 0x" << std::hex << dwClientDLL << std::endl;
	
	CLocalPlayer localPLayer;
	//TODO:
	//ONLY EXECUTE THIS CODE WHEN INGAME
	localPLayer.ReadInformation();
	std::cout << "Found team: " <<  std::hex << localPLayer.Team << std::endl;
	std::cout << "Found Flags: " <<  std::hex << localPLayer.Flags << std::endl;
	int i;
	std::cin >> i;
	return true;
}