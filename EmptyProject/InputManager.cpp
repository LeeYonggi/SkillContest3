#include "DXUT.h"
#include "InputManager.h"


InputManager::InputManager()
{
	Init();
}


InputManager::~InputManager()
{
}

void InputManager::Init()
{
	memset(nowKey, false, sizeof(nowKey));
	memset(pastKey, false, sizeof(pastKey));

	mouse = { 0, 0 };
}

void InputManager::Update()
{
	memcpy(pastKey, nowKey, sizeof(pastKey));

	for (int i = 0; i < KEY_SIZE; ++i)
		nowKey[i] = GetAsyncKeyState(i) & 0x8000;

	POINT tPoint;
	GetCursorPos(&tPoint);
	ScreenToClient(DXUTGetHWND(), &tPoint);
	mouse.x = tPoint.x;
	mouse.y = tPoint.y;
}
