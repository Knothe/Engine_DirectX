#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Windows.h"

#pragma once
class Application {
public:
	Application();
	Application(const Application& other);
	~Application();

	bool Initialize(int screenWidth, int screenHeight, HWND hwnd);
	void Shutdown();
	bool Frame();

	inline bool GetFullScreen() { return fullScreen; }

private:
	bool Render();

	bool fullScreen = false;
	//bool vSyncEnabled = true;
	//float screenDepth = 1000.0f;
	//float screenNear = .3f;
};
#endif