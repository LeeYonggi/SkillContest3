#pragma once
#include "Singleton.h"


class SceneManager :
	public Singleton<SceneManager>
{
public:
	SceneManager();
	virtual ~SceneManager();

private:
	BaseScene *nowScene;
	BaseScene *nextScene;
	bool isSceneChange;

public:
	void AddScene(BaseScene *scene);
	void Update();
	void Render();
	void Release();

};

#define SCENEMANAGER SceneManager::GetInstance()