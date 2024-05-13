#pragma once
#include <windows.h>
#include <iostream>


class Debug {
public:
	enum Color {
		BLACK, BLUE, GREEN, CYAN, 
		RED, MAGENTA, BROWN, LIGHTGRAY, 
		DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN,
		LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
	};

	static Debug* GetPtr();
	static void Log(std::string s);
	static void LogError(std::string s);
	static void LogWarning(std::string s);

private:
	Debug();
	void RedirectStd();
	static Debug* ptr;
	HANDLE hConsole;
};

