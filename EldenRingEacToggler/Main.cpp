#include <iostream>
#include <sys/stat.h>
#include <Windows.h>
#include <libloaderapi.h>
#include <vector>
#include <sstream>
#include <fstream>

#include "Logger.h"

Logger logger{ "AntiCheatToggler" };

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
	return tokens.back();
}

void StartGame()
{
	ShellExecute(NULL, "open", "eldenring.exe", NULL, NULL, SW_SHOWDEFAULT);
	logger.Log("Started game");
}

void ToggleAntiCheat()
{
	logger.Log("Toggling...");
	struct stat fileInfo;
	bool exeExists = stat("start_protected_game.exe", &fileInfo) == 0;
	if (exeExists)
	{
		logger.Log(".exe file size: %i", fileInfo.st_size);

		bool isOurExecutable = fileInfo.st_size < 100000;
		bool isActuallyGameExecutable = fileInfo.st_size > 40000000;

		if (isActuallyGameExecutable)
		
		{
			logger.Log("start_protected_game.exe is a copy of the game executable");
			MessageBox(NULL, "Looks like start_protected_game.exe is a copy of the game executable. Please remove it and replace it with the original EasyAntiCheat executable. If you don't have it then you can verify your game files through Steam to get it back.", NULL, MB_OK | MB_ICONERROR);
		}
		else if (isOurExecutable)
		{
			std::ifstream proxyDll("XInput1_4.dll", std::ios::binary);
			if(proxyDll.is_open()) 
			{
				logger.Log("XInput1_4.dll exists");
				proxyDll.close();
				bool proxyDllRenamed = rename("XInput1_4.dll", "_XInput1_4.dll") == 0;
				if (!proxyDllRenamed)
				{
					logger.Log("Failed to rename XInput1_4.dll");
					MessageBox(NULL, "Failed to enable the anti-cheat, please manually rename XInput1_4.dll to _XInput1_4.dll.", NULL, MB_OK | MB_ICONERROR);
					return;
				}
			}

			bool fileRemoved = remove("start_protected_game.exe") == 0;
			if (fileRemoved)
			{
				logger.Log("Removed start_protected_game.exe");
				std::ifstream src("start_protected_game.exe.original", std::ios::binary);
				if (src.is_open())
				{
					std::ofstream dst("start_protected_game.exe", std::ios::binary);
					dst << src.rdbuf();
					src.close();
					dst.close();
					remove("start_protected_game.exe.original");
					logger.Log("Anti-cheat enabled");
					MessageBox(NULL, "Anti-cheat enabled. Remember to turn off external mods such as Flawless Widescreen!", "Enabled", MB_OK | MB_ICONINFORMATION);
				}
				else
				{
					logger.Log("Failed to copy start_protected_game.exe.original");
					src.close();
					MessageBox(NULL, "Failed to enable the anti-cheat, please manually rename start_protected_game.exe.original to start_protected_game.exe or verify your game files through Steam.", NULL, MB_OK | MB_ICONERROR);
				}
			}
			else
			{
				logger.Log("Failed to remove start_protected_game.exe");
				MessageBox(NULL, "Failed to enable the anti-cheat, please delete start_protected_game.exe and manually rename start_protected_game.exe.original to start_protected_game.exe or verify your game files through Steam.", NULL, MB_OK | MB_ICONERROR);
			}
		} 
		else
		{
			std::ifstream proxyDll("_XInput1_4.dll", std::ios::binary);
			if (proxyDll.is_open())
			{
				logger.Log("_XInput1_4.dll exists");
				proxyDll.close();
				bool proxyDllRenamed = rename("_XInput1_4.dll", "XInput1_4.dll") == 0;
				if (!proxyDllRenamed)
				{
					logger.Log("Failed to rename _XInput1_4.dll");
					MessageBox(NULL, "Failed to disable the anti-cheat, could not rename _XInput1_4.dll. Please manually rename _XInput1_4.dll to XInput1_4.dll.", NULL, MB_OK | MB_ICONERROR);
					return;
				}
			}
			else
			{
				proxyDll.close();
				proxyDll.open("XInput1_4.dll", std::ios::binary);
				if (!proxyDll.is_open()) {
					MessageBox(NULL, "Failed to disable the anti-cheat, _XInput1_4.dll does not exist! Either manually rename _XInput1_4.dll to XInput1_4.dll or try to reinstall this tool.", NULL, MB_OK | MB_ICONERROR);
					return;
				}
				proxyDll.close();
			}

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
					logger.Log("Anti-cheat disabled");
					MessageBox(NULL, "Anti-cheat disabled.", "Disabled", MB_OK | MB_ICONINFORMATION);
				}
				else
				{
					logger.Log("Failed to copy toggle_anti_cheat.exe");
					MessageBox(NULL, "Failed to disable the anti-cheat, toggle_anti_cheat.exe not found.", NULL, MB_OK | MB_ICONERROR);
				}
				src.close();
			}
			else
			{
				logger.Log("Failed to rename original start_protected_game.exe");
				MessageBox(NULL, "Failed to disable the anti-cheat, failed to rename start_protected_game.exe. Does start_protected_game.exe.original already exist?", NULL, MB_OK | MB_ICONERROR);
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

	if (name == "start_protected_game.exe")
	{
		StartGame();
	}
	else if (name == "toggle_anti_cheat.exe")
	{
		ToggleAntiCheat();
	}

	return 0;
}