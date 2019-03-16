#pragma once
#include "Singleton.h"


class CameraManager :
	public Singleton<CameraManager>
{
public:
	CameraManager();
	virtual ~CameraManager();

public:
	Camera *camera;
	
public:
	void Update();
	void View();

	void Init(Camera* _camera) 
	{ 
		SAFE_DELETE(camera);
		camera = _camera;
	}
	Camera* GetCamera() { return camera; }
};

#define CAMERAMANAGER CameraManager::GetInstance()