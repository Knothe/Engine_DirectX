#include "Application.h"

Application* Application::ptr;

Application::Application() {
}

Application* Application::GetPtr() {
    if (!ptr)
        ptr = new Application;
    return ptr;
}

Application::~Application() {
}

bool Application::Initialize(int screenWidth, int screenHeight, HWND hwnd) {
    return true;
}

void Application::Shutdown() {
    return;
}

bool Application::Frame() {
    return true;
}

bool Application::Render() {
    return true;
}
