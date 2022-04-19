# Elden Ring EAC Toggler
Simple convenience tool which lets you easily enable and disable EasyAntiCheat for Elden Ring. **Note:** disabling EAC forces the game into offline mode.

## Why use this tool?
Using this tool has some advantages over other methods:
- It ensures the anti-cheat will not launch no matter how you start the game.
- It is faster than toggling it manually.
- It will not cause issues after a game update (unless start_protected_game.exe is patched in the update).
- It will automatically toggle Elden Mod Loader mods.

## Winhttp.dll
winhttp.dll is simply a dummy proxy .dll whose only function is to stop EasyAntiCheat from loading if a game update replaces our modified "start_protected_game.exe" with the original EasyAntiCheat executable. In which case EAC will refuse to let the game launch because of the untrusted system file "winhttp.dll".

## Download
Download link: [NexusMods](https://www.nexusmods.com/eldenring/mods/90)

![Anti-cheat disabled](https://github.com/techiew/EldenRingEacToggler/blob/master/picture.png)
