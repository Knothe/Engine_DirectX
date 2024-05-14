#include "Input.h"

Input* Input::ptr;

Input::Input()
{
}

Input::Input(const Input&)
{
}

Input* Input::GetPtr() {
	if (!ptr)
		ptr = new Input;
	return ptr;
}

Input::~Input()
{
}

void Input::Initialize() {
	int i;

	// Initialize all the keys to being released and not pressed.
	for (i = 0; i < 256; i++)
		m_keys[i] = false;
	return;
}

void Input::KeyDown(unsigned int input){
	// If a key is pressed then save that state in the key array.
	m_keys[input] = true;
	return;
}

void Input::KeyUp(unsigned int input){
	// If a key is released then clear that state in the key array.
	m_keys[input] = false;
	return;
}

bool Input::IsKeyDown(unsigned int key){
	return GetPtr()->m_keys[key];
	return false;
}
