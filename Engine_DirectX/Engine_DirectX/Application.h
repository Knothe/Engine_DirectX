#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Windows.h"

#pragma once
class Application {
public:
	static Application* GetPtr();
	~Application();

	bool Initialize(int screenWidth, int screenHeight, HWND hwnd);
	void Shutdown();
	bool Frame();

	static inline bool GetFullScreen() { return GetPtr()->fullScreen; }

private:
	Application();

	bool Render();

	static Application* ptr;
	bool fullScreen = false;
	//bool vSyncEnabled = true;
	//float screenDepth = 1000.0f;
	//float screenNear = .3f;
};
#endif