#include <iostream>
#include <sys/stat.h>
#include <Windows.h>
#include <libloaderapi.h>
#include <vector>
#include <sstream>
#include <fstream>

#include "Logger.h"
#include "ini.h"

using namespace mINI;

Logger logger{ "AntiCheatToggler" };
static bool autoToggleMods = true;

std::string GetNameOfSelf(std::string exePath)
{
	std::stringstream stringStream(exePath);
	std::string token = "";
	std::vector<std::string> tokens;
	char delimiter = '\\';
	while (std::getline(stringStream, token, delimiter))
	{
		tokens.push_back(token);
		logger.Log("Token: %s", token.c_str());
	}

	if (tokens[tokens.size() - 2] != "Game")
	{
		logger.Log("Doesn't seem like the tool is located inside the Elden Ring 'Game' folder, did you install it correctly?");
	}

	return tokens.back();
}

void ReadConfig()
{
	INIFile config("anti_cheat_toggler_config.ini");
	INIStructure ini;

	if (config.read(ini))
	{
		autoToggleMods = std::stoi(ini["anti_cheat_toggler"].get("auto_toggle_mods")) > 0;
	}
	else
	{
		ini["anti_cheat_toggler"]["auto_toggle_mods"] = "1";
		config.write(ini, true);
	}

	logger.Log("Auto toggle mods: %i", autoToggleMods);
}

void StartGame()
{
	SetEnvironmentVariableA("SteamAppId", "1245620");
	ShellExecute(NULL, "open", "eldenring.exe", NULL, NULL, SW_SHOWDEFAULT);
	logger.Log("Started game");
}

void ToggleOtherProxyDlls(bool disableAnticheat)
{
	if (disableAnticheat)
	{
		rename("_d3d12.dll", "d3d12.dll");
		rename("_dxgi.dll", "dxgi.dll");
		rename("_ws2_32.dll", "ws2_32.dll");
		rename("_winmm.dll", "winmm.dll");
		rename("_crypt32.dll", "crypt32.dll");
		rename("_user32.dll", "user32.dll");
		rename("_gdi32.dll", "gdi32.dll");
		rename("_advapi32.dll", "advapi32.dll");
		rename("_shell32.dll", "shell32.dll");
		rename("_ole32.dll", "ole32.dll");
		rename("_oleaut32.dll", "oleaut32.dll");
		rename("_imm32.dll", "imm32.dll");
		rename("_setupapi.dll", "setupapi.dll");
		rename("_wldap32.dll", "wldap32.dll");
		rename("_xinput1_4.dll", "xinput1_4.dll");
		rename("_dinput8.dll", "dinput8.dll");
		logger.Log("Mods enabled");
	}
	else
	{
		rename("d3d12.dll", "_d3d12.dll");
		rename("dxgi.dll", "_dxgi.dll");
		rename("ws2_32.dll", "_ws2_32.dll");
		rename("winmm.dll", "_winmm.dll");
		rename("crypt32.dll", "_crypt32.dll");
		rename("user32.dll", "_user32.dll");
		rename("gdi32.dll", "_gdi32.dll");
		rename("advapi32.dll", "_advapi32.dll");
		rename("shell32.dll", "_shell32.dll");
		rename("ole32.dll", "_ole32.dll");
		rename("oleaut32.dll", "_oleaut32.dll");
		rename("imm32.dll", "_imm32.dll");
		rename("setupapi.dll", "_setupapi.dll");
		rename("wldap32.dll", "_wldap32.dll");
		rename("xinput1_4.dll", "_xinput1_4.dll");
		rename("dinput8.dll", "_dinput8.dll");
		logger.Log("Mods disabled");
	}
}

void ToggleWinHttpProxyDll(bool disableAnticheat)
{
	if (disableAnticheat)
	{
		std::ifstream winHttpDll("_winhttp.dll", std::ios::binary);
		if (winHttpDll.is_open())
		{
			logger.Log("_winhttp.dll exists");
			winHttpDll.close();
			remove("winhttp.dll");
			bool winHttpDllRenamed = rename("_winhttp.dll", "winhttp.dll") == 0;
			if (!winHttpDllRenamed)
			{
				logger.Log("Failed to rename _winhttp.dll");
				MessageBox(NULL, "Failed to enable the safeguard, could not rename _winhttp.dll. Does winhttp.dll already exist? Please manually rename _winhttp.dll to winhttp.dll or delete winhttp.dll.", NULL, MB_OK | MB_ICONERROR);
				return;
			}
		}
		else
		{
			logger.Log("_winhttp.dll does not exist");
			winHttpDll.close();
			winHttpDll.open("winhttp.dll", std::ios::binary);
			if (!winHttpDll.is_open())
			{
				MessageBox(NULL, "Failed to enable the safeguard, _winhttp.dll does not exist! Either manually rename _winhttp.dll to winhttp.dll or try to reinstall this tool.", NULL, MB_OK | MB_ICONERROR);
				return;
			}
			winHttpDll.close();
		}

		if (autoToggleMods)
		{
			ToggleOtherProxyDlls(disableAnticheat);
		}
	}
	else
	{
		std::ifstream winHttpDll("winhttp.dll", std::ios::binary);
		if (winHttpDll.is_open())
		{
			logger.Log("winhttp.dll exists");
			winHttpDll.close();
			remove("_winhttp.dll");
			bool proxyDllRenamed = rename("winhttp.dll", "_winhttp.dll") == 0;
			if (!proxyDllRenamed)
			{
				logger.Log("Failed to rename winhttp.dll");
				MessageBox(NULL, "Failed to disable the safeguard, could not rename winhttp.dll. Please manually rename winhttp.dll to _winhttp.dll or delete _winhttp.dll.", NULL, MB_OK | MB_ICONERROR);
				return;
			}
		}

		if (autoToggleMods)
		{
			ToggleOtherProxyDlls(disableAnticheat);
		}
	}
}

bool ToggleStartProtectedGame(bool disableAnticheat)
{
	if (disableAnticheat)
	{
		remove("start_protected_game.exe.original");
		bool originalFileRenamed = rename("start_protected_game.exe", "start_protected_game.exe.original") == 0;
		if (originalFileRenamed)
		{
			logger.Log("Renamed original start_protected_game.exe");

			std::ifstream src("toggle_anti_cheat.exe", std::ios::binary);
			if (src.is_open())
			{
				std::ofstream dst("start_protected_game.exe", std::ios::binary);
				dst << src.rdbuf();
				dst.close();
				rename("_steam_appid.txt", "steam_appid.txt");
				remove("_steam_appid.txt");
				logger.Log("Anti-cheat disabled");
				MessageBox(NULL, "Anti-cheat disabled.", "Disabled", MB_OK | MB_ICONINFORMATION);
				return true;
			}
			else
			{
				logger.Log("Failed to copy toggle_anti_cheat.exe");
				MessageBox(NULL, "Failed to disable the anti-cheat, toggle_anti_cheat.exe not found.", NULL, MB_OK | MB_ICONERROR);
				return false;
			}
			src.close();
		}
		else
		{
			logger.Log("Failed to rename original start_protected_game.exe");
			MessageBox(NULL, "Failed to disable the anti-cheat, failed to rename start_protected_game.exe. Delete start_protected_game.exe.original if it already exists.", NULL, MB_OK | MB_ICONERROR);
			return false;
		}
	}
	else
	{
		bool fileRemoved = remove("start_protected_game.exe") == 0;
		if (fileRemoved)
		{
			logger.Log("Removed start_protected_game.exe");
			bool exeRenamed = rename("start_protected_game.exe.original", "start_protected_game.exe") == 0;
			if (exeRenamed)
			{
				rename("steam_appid.txt", "_steam_appid.txt");
				remove("steam_appid.txt");
				logger.Log("Anti-cheat enabled");
				MessageBox(NULL, "Anti-cheat enabled. Remember to turn off external mods such as Flawless Widescreen!", "Enabled", MB_OK | MB_ICONINFORMATION);
				return true;
			}
			else
			{
				logger.Log("Failed to rename start_protected_game.exe.original");
				MessageBox(NULL, "Failed to enable the anti-cheat, please manually rename start_protected_game.exe.original to start_protected_game.exe or verify your game files through Steam.", NULL, MB_OK | MB_ICONERROR);
				return false;
			}
		}
		else
		{
			logger.Log("Failed to remove start_protected_game.exe");
			MessageBox(NULL, "Failed to enable the anti-cheat, please delete start_protected_game.exe and manually rename start_protected_game.exe.original to start_protected_game.exe or verify your game files through Steam.", NULL, MB_OK | MB_ICONERROR);
			return false;
		}
	}

	return false;
}

void ToggleAntiCheat()
{
	logger.Log("Toggling...");
	struct stat fileInfo;
	bool exeExists = stat("start_protected_game.exe", &fileInfo) == 0;
	if (exeExists)
	{
		logger.Log(".exe file size: %i", fileInfo.st_size);

		bool isOurExecutable = fileInfo.st_size < 1000000;
		bool isActuallyGameExecutable = fileInfo.st_size > 40000000;

		if (isActuallyGameExecutable)
		{
			logger.Log("start_protected_game.exe is a copy of the game executable");
			MessageBox(NULL, "Looks like start_protected_game.exe is a copy of the game executable. Please remove it and replace it with the original EasyAntiCheat executable. If you don't have it then you can verify your game files through Steam to get it back.", NULL, MB_OK | MB_ICONERROR);
		}
		else if (isOurExecutable)
		{
			if (ToggleStartProtectedGame(false))
			{
				ToggleWinHttpProxyDll(false);
			}
		} 
		else
		{
			if (ToggleStartProtectedGame(true))
			{
				ToggleWinHttpProxyDll(true);
			}
		}
	}
	else 
	{
		logger.Log("start_protected_game.exe does not exist");
		MessageBox(NULL, "start_protected_game.exe does not exist, please verify your game files through Steam.", NULL, MB_OK | MB_ICONERROR);
	}
}

int main(int argc, char* argv[])
{
	std::string name = GetNameOfSelf(argv[0]);
	logger.Log("Name: %s", name.c_str());

	ReadConfig();

	if (name == "start_protected_game.exe")
	{
		StartGame();
	}
	else if (name == "toggle_anti_cheat.exe")
	{
		ToggleAntiCheat();
	}

	logger.CloseFile();
	return 0;
}