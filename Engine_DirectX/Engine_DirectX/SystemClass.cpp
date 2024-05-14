﻿#include "SystemClass.h"

SystemClass* SystemClass::ptr;

SystemClass::SystemClass() {
	m_Application = 0;
}

SystemClass::SystemClass(const SystemClass& other) {
	m_Application = 0;
}

SystemClass* SystemClass::GetPtr() {
	if (!ptr)
		ptr = new SystemClass;
	return ptr;
}

SystemClass::~SystemClass() {
}

bool SystemClass::Initialize() {
	int screenWidth, screenHeight;
	screenWidth = 0;
	screenHeight = 0;
	m_Application = Application::GetPtr();
	m_Input = Input::GetPtr();
	m_Input->Initialize();
	InitializeWindows(screenWidth, screenHeight);
	bool result = m_Application->Initialize(screenWidth, screenHeight, m_hwnd);
	return result;
}

void SystemClass::Shutdown() {
	ShutdownWindows();
	return;
}

void SystemClass::Run() {
	MSG msg;
	bool done, result;

	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));

	done = false;
	while (!done) {
		// Handle the windows messages.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT) {
			done = true;
		}
		else {
			result = Frame();
			if (!result)
				done = true;
		}
	}
	return;
}

LRESULT SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	switch (umsg) {
		case WM_KEYDOWN: {
			m_Input->KeyDown((unsigned int)wparam);
			return 0;
		}
		case WM_KEYUP: {
			m_Input->KeyUp((unsigned int)wparam);
			return 0;
		}
		default:
			return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight) {
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;
	
	ApplicationHandle = this;
	m_hinstance = GetModuleHandle(NULL);
	m_applicationName = L"Engine-エンジン";

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	if (m_Application->GetFullScreen()) { // If full screen set the screen to maximum size of the users desktop and 32bit.
		// Determine the resolution of the clients desktop screen.
		screenWidth = GetSystemMetrics(SM_CXSCREEN);
		screenHeight = GetSystemMetrics(SM_CYSCREEN);

		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else {
		// If windowed then set it to 800x600 resolution.
		screenWidth = 800;
		screenHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	ShowCursor(false);
	return;
}

void SystemClass::ShutdownWindows() {
	ShowCursor(true);
	if (m_Application->GetFullScreen()) { // Fix the display settings if leaving full screen mode.
		ChangeDisplaySettings(NULL, 0);
	}
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;
	ApplicationHandle = NULL;
	return;
}

bool SystemClass::Frame() {
	bool result;
	// Check if the user pressed escape and wants to exit the application.
	if (Input::IsKeyDown(VK_ESCAPE)) {
		return false;
	}

	// Do the frame processing for the application class object.
	result = m_Application->Frame();
	if (!result) {
		return false;
	}
	return true;
}

LRESULT WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {
	switch (umessage) {
		case WM_DESTROY: { // Window is being destroyed
			PostQuitMessage(0);
			return 0;
		}
		case WM_CLOSE: { // Window is being closed
			PostQuitMessage(0);
			return 0;
		}
		default: {
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}

