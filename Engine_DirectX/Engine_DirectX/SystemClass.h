#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "Application.h"
#include "Input.h"

#pragma once
class SystemClass {
public:
	static SystemClass* GetPtr();
	~SystemClass();
	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

private:
	static SystemClass* ptr;

	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	Application* m_Application;
	Input* m_Input;

	SystemClass();
	SystemClass(const SystemClass& other);

	void InitializeWindows(int& screenWidth, int& screenHeight);
	void ShutdownWindows();
	bool Frame();
};

static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
static SystemClass* ApplicationHandle = 0;
#endif
