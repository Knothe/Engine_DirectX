#include "SystemClass.h"

// _In_ explanation: https://learn.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2012/hh916383(v=vs.110)?redirectedfrom=MSDN
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd){
	SystemClass* System;
	System = new SystemClass;
	if (System->Initialize())
		System->Run();
	System->Shutdown();
	delete System;
	System = 0;
	return 0;
}