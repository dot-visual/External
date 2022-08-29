#include <iostream>
#include <thread>
#include "Utils/ProcMemory.h"
#include "SDK/Offsets.h"
#include "Features/Aimbot.h"
#include "Features/Misc.h"

void Initialize() {
	HWND hWindow{};
	DWORD procId{};

	while (!procMem->InitializeProcessData("Counter-Strike: Global Offensive", hWindow, procId, procMem->hProcess)) {
		std::cout << ".";
		Sleep(1000);
	}

	while (!Offsets::clientDll && !Offsets::engineDll) {
		Offsets::engineDll = procMem->GetModuleBaseExternal("engine.dll", procId);
		Offsets::clientDll = procMem->GetModuleBaseExternal("client_panorama.dll", procId);
	}
	std::cout << "Found engine.dll at 0x" << std::hex << Offsets::clientDll << std::dec << "/n";
	std::cout << "Found client.dll at 0x" << std::hex << Offsets::engineDll << std::dec << "/n";
}

int main() {
	Initialize();

	while (true) {
		//if (isIngame()) {
			aimbot.run();
			bhop.run();
			triggerBot.run();
		//}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	return 1;
}