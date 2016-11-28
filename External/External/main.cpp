#pragma once
#include "include.h"

int main()
{
	while( !procMem->InitializeProcessData( "Counter-Strike: Global Offensive", offsets->hWindow, offsets->dwProcessId, procMem->hProcess ) )
	{
		std::cout << ".";
		Sleep( 1000 );
	}
	offsets->dwClientDLL = procMem->GetModuleBaseExternal("client.dll", offsets->dwProcessId);

	std::cout << "Found client.dll at 0x" << std::hex << offsets->dwClientDLL << std::endl;

	//TODO:
	//ONLY EXECUTE THIS CODE WHEN INGAME
	localPLayer->ReadInformation();

	std::cout << "Found team: " <<  std::hex << localPLayer->Team << std::endl;
	std::cout << "Found Flags: " <<  std::hex << localPLayer->Flags << std::endl;
	
	while (true)
	{
		g_pMisc->BunnyHop();
		Sleep(1);
	}
	int i;
	std::cin >> i;
	return true;
}