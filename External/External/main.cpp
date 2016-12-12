#pragma once
#include "include.h"

void displayFuncs()
{
	std::cout << "BHOP: " << g_pMisc->GetBhop() << std::endl;
	std::cout << "TRIGGER: " << g_pMisc->GetTrigger() << std::endl;
	std::cout << "GLOW " << g_pMisc->GetGlow() << std::endl;
	std::cout << "ANG " << localPLayer->ViewAngles[0] << std::endl;
	std::cout << "ANG " << localPLayer->ViewAngles[1] << std::endl;
	std::cout << "ANG " << localPLayer->ViewAngles[2] << std::endl;
}

int main()
{
	while( !procMem->InitializeProcessData( "Counter-Strike: Global Offensive", offsets->hWindow, offsets->dwProcessId, procMem->hProcess ) )
	{
		std::cout << ".";
		Sleep( 1000 );
	}


	offsets->dwClientDLL = procMem->GetModuleBaseExternal("client.dll", offsets->dwProcessId);
		offsets->dwEngineDLL = procMem->GetModuleBaseExternal("engine.dll", offsets->dwProcessId);
	std::cout << "Found engine.dll at 0x" << std::hex << offsets->dwEngineDLL << std::endl;
	std::cout << "Found client.dll at 0x" << std::hex << offsets->dwClientDLL << std::endl;

	//TODO:
	//ONLY EXECUTE THIS CODE WHEN INGAME
	localPLayer->ReadInformation();

	std::cout << "Found team: " <<  std::hex << localPLayer->Team << std::endl;
	std::cout << "Found Flags: " <<  std::hex << localPLayer->Flags << std::endl;
	while (true)
	{
		g_pMisc->BunnyHop();
		g_pMisc->Triggerbot();
		g_pMisc->Glow();
		//g_pMisc->AutoPistol();
		//g_pMisc->NoFlash();

		if (GetAsyncKeyState(VK_F1))
		{
			g_pMisc->SetBhop();
			std::cout << "BHOP CHANGED " << g_pMisc->GetBhop() << std::endl;
			Sleep(1000);
			system("cls");
			displayFuncs();
		}

		if (GetAsyncKeyState(VK_F2))
		{
			g_pMisc->SetTrigger();
			std::cout << "TRIGGER CHANGED " << g_pMisc->GetTrigger() << std::endl;
			Sleep(1000);
			system("cls");
			displayFuncs();
		}

		if (GetAsyncKeyState(VK_F3))
		{
			g_pMisc->SetGlow();
			std::cout << "GLOW CHANGED " << g_pMisc->GetGlow() << std::endl;
			Sleep(1000);
			system("cls");
			displayFuncs();
		}
		if (GetAsyncKeyState(VK_RBUTTON))
		{
			g_pMisc->Aimbot();
		}

		Sleep(1);
	}
	int i;
	std::cin >> i;
	return true;
}