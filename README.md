## Elden Ring EAC Toggler
Simple tool which lets you easily enable and disable EasyAntiCheat for Elden Ring.

Using this tool should be the preferred method of disabling EasyAntiCheat as the old method where you replace "start_protected_game.exe" with a copy of "eldenring.exe" will cause issues after a game update. Using the old method, if you launch the game through Steam after the game has been updated, it will launch the game using the old copy of the executable (That is, start_protected_game.exe), effectively making you play an older game version. Other methods also have downsides.

winhttp.dll is simply a dummy proxy .dll whose only function is to stop EasyAntiCheat from loading if a game update replaces our modified "start_protected_game.exe" with the original EasyAntiCheat executable (which I'm pretty sure it doesn't do every time). In that case, EAC will stop the game on startup because of the untrusted system file "winhttp.dll".

Download link: [NexusMods](https://www.nexusmods.com/eldenring/mods/90)

![Anti-cheat disabled](https://github.com/techiew/EldenRingEacToggler/blob/master/picture.png)
