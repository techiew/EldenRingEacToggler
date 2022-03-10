#include <Windows.h>

int main()
{
	SetEnvironmentVariableA("SteamAppId", "1245620");
	ShellExecute(NULL, "open", "eldenring.exe", NULL, NULL, SW_SHOWDEFAULT);
}