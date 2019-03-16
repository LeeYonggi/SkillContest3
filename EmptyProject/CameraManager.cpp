#include "DXUT.h"
#include "CameraManager.h"



CameraManager::CameraManager()
{
	camera = nullptr;
}

CameraManager::~CameraManager()
{
}

void CameraManager::Update()
{
	camera->Update();
}

void CameraManager::View()
{
	camera->View();
}
