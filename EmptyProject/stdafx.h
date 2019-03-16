#pragma once


//define
extern float timeScale;
typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;

#define SCREEN_X 1280
#define SCREEN_Y 720
#define DEVICE DXUTGetD3D9Device()
#define ELTIME DXUTGetElapsedTime() * timeScale

#include "Utility.h"
#include "Singleton.h"
#include "ImageManager.h"

#include "MeshLoader.h"
#include "MeshManager.h"

#include "Camera.h"
#include "CameraManager.h"

#include "Object.h"
#include "ObjectManager.h"

#include "InputManager.h"

#include "BaseScene.h"
#include "SceneManager.h"

#include "LoadScene.h"

#include "MainProc.h"
