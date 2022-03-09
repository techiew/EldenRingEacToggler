#include <windows.h>

HINSTANCE hLThis = 0;
FARPROC p[8];
HINSTANCE hL = 0;

BOOL WINAPI DllMain(HINSTANCE hInst,DWORD reason,LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		hLThis = hInst;
		hL = LoadLibrary("C:\\Windows\\System32\\XInput1_4.dll");
		if(!hL) return false;
	}

	p[0] = GetProcAddress(hL, "DllMain");
	p[1] = GetProcAddress(hL, "XInputEnable");
	p[2] = GetProcAddress(hL, "XInputGetAudioDeviceIds");
	p[3] = GetProcAddress(hL, "XInputGetBatteryInformation");
	p[4] = GetProcAddress(hL, "XInputGetCapabilities");
	p[5] = GetProcAddress(hL, "XInputGetKeystroke");
	p[6] = GetProcAddress(hL, "XInputGetState");
	p[7] = GetProcAddress(hL, "XInputSetState");
	if (reason == DLL_PROCESS_DETACH)
	{
		FreeLibrary(hL);
		return 1;
	}

	return 1;
}

extern "C"
{
	FARPROC PA = NULL;
	int RunASM();

	void PROXY_DllMain() {
		PA = p[0];
		RunASM();
	}
	void PROXY_XInputEnable() {
		PA = p[1];
		RunASM();
	}
	void PROXY_XInputGetAudioDeviceIds() {
		PA = p[2];
		RunASM();
	}
	void PROXY_XInputGetBatteryInformation() {
		PA = p[3];
		RunASM();
	}
	void PROXY_XInputGetCapabilities() {
		PA = p[4];
		RunASM();
	}
	void PROXY_XInputGetKeystroke() {
		PA = p[5];
		RunASM();
	}
	void PROXY_XInputGetState() {
		PA = p[6];
		RunASM();
	}
	void PROXY_XInputSetState() {
		PA = p[7];
		RunASM();
	}
}
