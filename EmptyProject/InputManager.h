#pragma once
#include "Singleton.h"

#define KEY_SIZE 256
class InputManager :
	public Singleton<InputManager>
{
public:
	InputManager();
	virtual ~InputManager();

private:
	bool nowKey[KEY_SIZE];
	bool pastKey[KEY_SIZE];
	Vector2 mouse;

public:
	void Init();
	void Update();

public:
	bool KeyDown(int key)	{ return (pastKey[key] == false && nowKey[key] == true) ? true : false; }
	bool KeyPress(int key)	{ return (pastKey[key] == true && nowKey[key] == true) ? true : false; }
	bool KeyUp(int key)		{ return (pastKey[key] == true && nowKey[key] == false) ? true : false; }

	Vector2 GetMousePos() { return mouse; }
};

#define INPUTMANAGER InputManager::GetInstance()