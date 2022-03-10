#include <windows.h>

HINSTANCE hLThis = 0;
FARPROC p[69];
HINSTANCE hL = 0;

BOOL WINAPI DllMain(HINSTANCE hInst,DWORD reason,LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		hLThis = hInst;
		hL = LoadLibrary("C:\\Windows\\System32\\winhttp.dll");
		if(!hL) return false;
	}

	p[0] = GetProcAddress(hL, "DllCanUnloadNow");
	p[1] = GetProcAddress(hL, "DllGetClassObject");
	p[2] = GetProcAddress(hL, "Private1");
	p[3] = GetProcAddress(hL, "SvchostPushServiceGlobals");
	p[4] = GetProcAddress(hL, "WinHttpAddRequestHeaders");
	p[5] = GetProcAddress(hL, "WinHttpAddRequestHeadersEx");
	p[6] = GetProcAddress(hL, "WinHttpAutoProxySvcMain");
	p[7] = GetProcAddress(hL, "WinHttpCheckPlatform");
	p[8] = GetProcAddress(hL, "WinHttpCloseHandle");
	p[9] = GetProcAddress(hL, "WinHttpConnect");
	p[10] = GetProcAddress(hL, "WinHttpConnectionDeletePolicyEntries");
	p[11] = GetProcAddress(hL, "WinHttpConnectionDeleteProxyInfo");
	p[12] = GetProcAddress(hL, "WinHttpConnectionFreeNameList");
	p[13] = GetProcAddress(hL, "WinHttpConnectionFreeProxyInfo");
	p[14] = GetProcAddress(hL, "WinHttpConnectionFreeProxyList");
	p[15] = GetProcAddress(hL, "WinHttpConnectionGetNameList");
	p[16] = GetProcAddress(hL, "WinHttpConnectionGetProxyInfo");
	p[17] = GetProcAddress(hL, "WinHttpConnectionGetProxyList");
	p[18] = GetProcAddress(hL, "WinHttpConnectionSetPolicyEntries");
	p[19] = GetProcAddress(hL, "WinHttpConnectionSetProxyInfo");
	p[20] = GetProcAddress(hL, "WinHttpConnectionUpdateIfIndexTable");
	p[21] = GetProcAddress(hL, "WinHttpCrackUrl");
	p[22] = GetProcAddress(hL, "WinHttpCreateProxyResolver");
	p[23] = GetProcAddress(hL, "WinHttpCreateUrl");
	p[24] = GetProcAddress(hL, "WinHttpDetectAutoProxyConfigUrl");
	p[25] = GetProcAddress(hL, "WinHttpFreeProxyResult");
	p[26] = GetProcAddress(hL, "WinHttpFreeProxyResultEx");
	p[27] = GetProcAddress(hL, "WinHttpFreeProxySettings");
	p[28] = GetProcAddress(hL, "WinHttpGetDefaultProxyConfiguration");
	p[29] = GetProcAddress(hL, "WinHttpGetIEProxyConfigForCurrentUser");
	p[30] = GetProcAddress(hL, "WinHttpGetProxyForUrl");
	p[31] = GetProcAddress(hL, "WinHttpGetProxyForUrlEx");
	p[32] = GetProcAddress(hL, "WinHttpGetProxyForUrlEx2");
	p[33] = GetProcAddress(hL, "WinHttpGetProxyForUrlHvsi");
	p[34] = GetProcAddress(hL, "WinHttpGetProxyResult");
	p[35] = GetProcAddress(hL, "WinHttpGetProxyResultEx");
	p[36] = GetProcAddress(hL, "WinHttpGetProxySettingsVersion");
	p[37] = GetProcAddress(hL, "WinHttpGetTunnelSocket");
	p[38] = GetProcAddress(hL, "WinHttpOpen");
	p[39] = GetProcAddress(hL, "WinHttpOpenRequest");
	p[40] = GetProcAddress(hL, "WinHttpPacJsWorkerMain");
	p[41] = GetProcAddress(hL, "WinHttpProbeConnectivity");
	p[42] = GetProcAddress(hL, "WinHttpQueryAuthSchemes");
	p[43] = GetProcAddress(hL, "WinHttpQueryDataAvailable");
	p[44] = GetProcAddress(hL, "WinHttpQueryHeaders");
	p[45] = GetProcAddress(hL, "WinHttpQueryOption");
	p[46] = GetProcAddress(hL, "WinHttpReadData");
	p[47] = GetProcAddress(hL, "WinHttpReadProxySettings");
	p[48] = GetProcAddress(hL, "WinHttpReadProxySettingsHvsi");
	p[49] = GetProcAddress(hL, "WinHttpReceiveResponse");
	p[50] = GetProcAddress(hL, "WinHttpResetAutoProxy");
	p[51] = GetProcAddress(hL, "WinHttpSaveProxyCredentials");
	p[52] = GetProcAddress(hL, "WinHttpSendRequest");
	p[53] = GetProcAddress(hL, "WinHttpSetCredentials");
	p[54] = GetProcAddress(hL, "WinHttpSetDefaultProxyConfiguration");
	p[55] = GetProcAddress(hL, "WinHttpSetOption");
	p[56] = GetProcAddress(hL, "WinHttpSetProxySettingsPerUser");
	p[57] = GetProcAddress(hL, "WinHttpSetStatusCallback");
	p[58] = GetProcAddress(hL, "WinHttpSetTimeouts");
	p[59] = GetProcAddress(hL, "WinHttpTimeFromSystemTime");
	p[60] = GetProcAddress(hL, "WinHttpTimeToSystemTime");
	p[61] = GetProcAddress(hL, "WinHttpWebSocketClose");
	p[62] = GetProcAddress(hL, "WinHttpWebSocketCompleteUpgrade");
	p[63] = GetProcAddress(hL, "WinHttpWebSocketQueryCloseStatus");
	p[64] = GetProcAddress(hL, "WinHttpWebSocketReceive");
	p[65] = GetProcAddress(hL, "WinHttpWebSocketSend");
	p[66] = GetProcAddress(hL, "WinHttpWebSocketShutdown");
	p[67] = GetProcAddress(hL, "WinHttpWriteData");
	p[68] = GetProcAddress(hL, "WinHttpWriteProxySettings");
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

	void PROXY_DllCanUnloadNow() {
		PA = p[0];
		RunASM();
	}
	void PROXY_DllGetClassObject() {
		PA = p[1];
		RunASM();
	}
	void PROXY_Private1() {
		PA = p[2];
		RunASM();
	}
	void PROXY_SvchostPushServiceGlobals() {
		PA = p[3];
		RunASM();
	}
	void PROXY_WinHttpAddRequestHeaders() {
		PA = p[4];
		RunASM();
	}
	void PROXY_WinHttpAddRequestHeadersEx() {
		PA = p[5];
		RunASM();
	}
	void PROXY_WinHttpAutoProxySvcMain() {
		PA = p[6];
		RunASM();
	}
	void PROXY_WinHttpCheckPlatform() {
		PA = p[7];
		RunASM();
	}
	void PROXY_WinHttpCloseHandle() {
		PA = p[8];
		RunASM();
	}
	void PROXY_WinHttpConnect() {
		PA = p[9];
		RunASM();
	}
	void PROXY_WinHttpConnectionDeletePolicyEntries() {
		PA = p[10];
		RunASM();
	}
	void PROXY_WinHttpConnectionDeleteProxyInfo() {
		PA = p[11];
		RunASM();
	}
	void PROXY_WinHttpConnectionFreeNameList() {
		PA = p[12];
		RunASM();
	}
	void PROXY_WinHttpConnectionFreeProxyInfo() {
		PA = p[13];
		RunASM();
	}
	void PROXY_WinHttpConnectionFreeProxyList() {
		PA = p[14];
		RunASM();
	}
	void PROXY_WinHttpConnectionGetNameList() {
		PA = p[15];
		RunASM();
	}
	void PROXY_WinHttpConnectionGetProxyInfo() {
		PA = p[16];
		RunASM();
	}
	void PROXY_WinHttpConnectionGetProxyList() {
		PA = p[17];
		RunASM();
	}
	void PROXY_WinHttpConnectionSetPolicyEntries() {
		PA = p[18];
		RunASM();
	}
	void PROXY_WinHttpConnectionSetProxyInfo() {
		PA = p[19];
		RunASM();
	}
	void PROXY_WinHttpConnectionUpdateIfIndexTable() {
		PA = p[20];
		RunASM();
	}
	void PROXY_WinHttpCrackUrl() {
		PA = p[21];
		RunASM();
	}
	void PROXY_WinHttpCreateProxyResolver() {
		PA = p[22];
		RunASM();
	}
	void PROXY_WinHttpCreateUrl() {
		PA = p[23];
		RunASM();
	}
	void PROXY_WinHttpDetectAutoProxyConfigUrl() {
		PA = p[24];
		RunASM();
	}
	void PROXY_WinHttpFreeProxyResult() {
		PA = p[25];
		RunASM();
	}
	void PROXY_WinHttpFreeProxyResultEx() {
		PA = p[26];
		RunASM();
	}
	void PROXY_WinHttpFreeProxySettings() {
		PA = p[27];
		RunASM();
	}
	void PROXY_WinHttpGetDefaultProxyConfiguration() {
		PA = p[28];
		RunASM();
	}
	void PROXY_WinHttpGetIEProxyConfigForCurrentUser() {
		PA = p[29];
		RunASM();
	}
	void PROXY_WinHttpGetProxyForUrl() {
		PA = p[30];
		RunASM();
	}
	void PROXY_WinHttpGetProxyForUrlEx() {
		PA = p[31];
		RunASM();
	}
	void PROXY_WinHttpGetProxyForUrlEx2() {
		PA = p[32];
		RunASM();
	}
	void PROXY_WinHttpGetProxyForUrlHvsi() {
		PA = p[33];
		RunASM();
	}
	void PROXY_WinHttpGetProxyResult() {
		PA = p[34];
		RunASM();
	}
	void PROXY_WinHttpGetProxyResultEx() {
		PA = p[35];
		RunASM();
	}
	void PROXY_WinHttpGetProxySettingsVersion() {
		PA = p[36];
		RunASM();
	}
	void PROXY_WinHttpGetTunnelSocket() {
		PA = p[37];
		RunASM();
	}
	void PROXY_WinHttpOpen() {
		PA = p[38];
		RunASM();
	}
	void PROXY_WinHttpOpenRequest() {
		PA = p[39];
		RunASM();
	}
	void PROXY_WinHttpPacJsWorkerMain() {
		PA = p[40];
		RunASM();
	}
	void PROXY_WinHttpProbeConnectivity() {
		PA = p[41];
		RunASM();
	}
	void PROXY_WinHttpQueryAuthSchemes() {
		PA = p[42];
		RunASM();
	}
	void PROXY_WinHttpQueryDataAvailable() {
		PA = p[43];
		RunASM();
	}
	void PROXY_WinHttpQueryHeaders() {
		PA = p[44];
		RunASM();
	}
	void PROXY_WinHttpQueryOption() {
		PA = p[45];
		RunASM();
	}
	void PROXY_WinHttpReadData() {
		PA = p[46];
		RunASM();
	}
	void PROXY_WinHttpReadProxySettings() {
		PA = p[47];
		RunASM();
	}
	void PROXY_WinHttpReadProxySettingsHvsi() {
		PA = p[48];
		RunASM();
	}
	void PROXY_WinHttpReceiveResponse() {
		PA = p[49];
		RunASM();
	}
	void PROXY_WinHttpResetAutoProxy() {
		PA = p[50];
		RunASM();
	}
	void PROXY_WinHttpSaveProxyCredentials() {
		PA = p[51];
		RunASM();
	}
	void PROXY_WinHttpSendRequest() {
		PA = p[52];
		RunASM();
	}
	void PROXY_WinHttpSetCredentials() {
		PA = p[53];
		RunASM();
	}
	void PROXY_WinHttpSetDefaultProxyConfiguration() {
		PA = p[54];
		RunASM();
	}
	void PROXY_WinHttpSetOption() {
		PA = p[55];
		RunASM();
	}
	void PROXY_WinHttpSetProxySettingsPerUser() {
		PA = p[56];
		RunASM();
	}
	void PROXY_WinHttpSetStatusCallback() {
		PA = p[57];
		RunASM();
	}
	void PROXY_WinHttpSetTimeouts() {
		PA = p[58];
		RunASM();
	}
	void PROXY_WinHttpTimeFromSystemTime() {
		PA = p[59];
		RunASM();
	}
	void PROXY_WinHttpTimeToSystemTime() {
		PA = p[60];
		RunASM();
	}
	void PROXY_WinHttpWebSocketClose() {
		PA = p[61];
		RunASM();
	}
	void PROXY_WinHttpWebSocketCompleteUpgrade() {
		PA = p[62];
		RunASM();
	}
	void PROXY_WinHttpWebSocketQueryCloseStatus() {
		PA = p[63];
		RunASM();
	}
	void PROXY_WinHttpWebSocketReceive() {
		PA = p[64];
		RunASM();
	}
	void PROXY_WinHttpWebSocketSend() {
		PA = p[65];
		RunASM();
	}
	void PROXY_WinHttpWebSocketShutdown() {
		PA = p[66];
		RunASM();
	}
	void PROXY_WinHttpWriteData() {
		PA = p[67];
		RunASM();
	}
	void PROXY_WinHttpWriteProxySettings() {
		PA = p[68];
		RunASM();
	}
}
