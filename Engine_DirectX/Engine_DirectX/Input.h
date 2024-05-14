#pragma once
class Input {
public:
	static Input* GetPtr();
	~Input();

	void Initialize();

	void KeyDown(unsigned int input);
	void KeyUp(unsigned int input);

	static bool IsKeyDown(unsigned int key);

private:
	static Input* ptr;
	bool m_keys[256];

	Input();
	Input(const Input&);
};

