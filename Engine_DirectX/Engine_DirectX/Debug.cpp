#include "Debug.h"

Debug* Debug::ptr;


Debug* Debug::GetPtr(){
	if (!ptr) 
		ptr = new Debug;
	return ptr;
}

Debug::Debug() {
	RedirectStd();
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Debug::RedirectStd() {
	// https://smacdo.com/programming/redirecting-standard-output-to-console-in-windows/
	if (AllocConsole() == 0) 
		throw "No console allocated";
	FILE* pNewStdout = nullptr;
	FILE* pNewStderr = nullptr;
	FILE* pNewStdin = nullptr;
	freopen_s(&pNewStdout, "CONOUT$", "w", stdout);
	freopen_s(&pNewStderr, "CONOUT$", "w", stderr);
	freopen_s(&pNewStdin, "CONIN$", "r", stdin);
	std::cout.clear();
	std::cerr.clear();
	std::cin.clear();
	std::wcout.clear();
	std::wcerr.clear();
	std::wcin.clear();
}

void Debug::Log(std::string s){
	SetConsoleTextAttribute(GetPtr()->hConsole, Color::WHITE);
	std::cout << s << std::endl;
}

void Debug::LogError(std::string s) {
	SetConsoleTextAttribute(GetPtr()->hConsole, Color::LIGHTRED);
	std::cout << s << std::endl;
}

void Debug::LogWarning(std::string s) {
	SetConsoleTextAttribute(GetPtr()->hConsole, Color::YELLOW);
	std::cout << s << std::endl;
}
