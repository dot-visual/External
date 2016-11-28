#pragma once

#pragma warning( disable : 4244 )
#pragma warning( disable : 4309 )
#pragma warning( disable : 4838 )
#pragma warning( disable : 4800 )
#pragma warning( disable : 4334 )
#pragma warning( disable : 4305 )
#pragma warning( disable : 4805 )
#pragma warning( disable : 4018 )
#pragma warning( disable : 4172 )
#pragma warning( disable : 4042 )

#pragma comment(lib,"wininet.lib")

#include <Windows.h>
#include <iostream>
#include <string>
#include <TlHelp32.h>
#include <thread>

#include "Misc.h"
#include "Offsets.h"
#include "Player.h"
#include "ProcMemory.h"
