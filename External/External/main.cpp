#include <iostream>
#include <thread>
#include "Utils/ProcMemory.h"
#include "SDK/Helper.h"
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
	std::cout << "Found engine.dll at 0x" << std::hex << Offsets::clientDll << std::dec << "\n";
	std::cout << "Found client.dll at 0x" << std::hex << Offsets::engineDll << std::dec << "\n";
}

void toggleFeature(Feature& feature) {
	feature.toggle();
	std::cout << feature.getName() << " Changed. Current State: " << feature.isEnabled() << "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

int main() {
	Initialize();

	while (true) {
		if (Helper::IsIngame()) {
			aimbot.run();
			bhop.run();
			triggerBot.run();

			if (GetAsyncKeyState(VK_F1) & 0x01)
				toggleFeature(aimbot);
			else if (GetAsyncKeyState(VK_F2) & 0x01)
				toggleFeature(bhop);
			else if (GetAsyncKeyState(VK_F3) & 0x01)
				toggleFeature(triggerBot);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	return 1;
}