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
std::vector<std::string> defaultModsToToggle = {
	"d3d12.dll",
	"dxgi.dll",
	"ws2_32.dll",
	"winmm.dll",
	"crypt32.dll",
	"user32.dll",
	"gdi32.dll",
	"advapi32.dll",
	"shell32.dll",
	"ole32.dll",
	"oleaut32.dll",
	"imm32.dll",
	"setupapi.dll",
	"wldap32.dll",
	"xinput1_4.dll",
	"dinput8.dll"
};

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
	std::string modListFileName = "anti_cheat_toggler_mod_list.txt";
	std::fstream modList(modListFileName, std::ios::in);
	std::vector<std::string> modsToToggle = defaultModsToToggle;

	if (disableAnticheat)
	{
		logger.Log("Enabling mods");
	}
	else
	{
		logger.Log("Disabling mods");
	}

	if (modList.is_open())
	{
		modsToToggle.clear();
		std::string modName = "";
		while (std::getline(modList, modName))
		{
			logger.Log("%s", modName);
			modsToToggle.push_back(modName);
		}
	}
	else
	{
		modList.close();
		modList.open(modListFileName, std::ios::out);
		if (modList.is_open())
		{
			for (auto fileName : defaultModsToToggle)
			{
				modList << fileName << '\n';
			}
		}
		else
		{
			logger.Log("Failed to open %s", modListFileName);
		}
	}

	for (auto modName : modsToToggle) {
		if (disableAnticheat)
		{
			rename(std::string("_" + modName).c_str(), modName.c_str());
		}
		else
		{
			rename(modName.c_str(), std::string("_" + modName).c_str());
		}
	}

	modList.close();
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
			if (winHttpDllRenamed == false)
			{
				logger.Log("Failed to rename _winhttp.dll");
			}
		}
		else
		{
			logger.Log("_winhttp.dll does not exist");
			winHttpDll.close();
			winHttpDll.open("winhttp.dll", std::ios::binary);
			if (winHttpDll.is_open() == false)
			{
				logger.Log("Could not enable safeguard, winhttp.dll has been deleted");
			}
			winHttpDll.close();
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
			if (proxyDllRenamed == false)
			{
				logger.Log("Failed to rename winhttp.dll");
				MessageBox(NULL, "Failed to disable the safeguard, could not rename winhttp.dll. Please manually rename winhttp.dll to _winhttp.dll or delete _winhttp.dll.", NULL, MB_OK | MB_ICONERROR);
				return;
			}
		}
	}

	if (autoToggleMods)
	{
		ToggleOtherProxyDlls(disableAnticheat);
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
		MessageBox(NULL, "Could not find start_protected_game.exe, please move anti_cheat_toggler.exe into the game folder or try to verify your game files through Steam.", NULL, MB_OK | MB_ICONERROR);
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