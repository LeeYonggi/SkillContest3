#include "DXUT.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{
	isSceneChange = false;
	nowScene = nullptr;
	nextScene = nullptr;
}


SceneManager::~SceneManager()
{
	Release();
}

void SceneManager::AddScene(BaseScene* scene)
{
	isSceneChange = true;
	nextScene = scene;
}

void SceneManager::Update()
{
	if (isSceneChange)
	{
		if (nowScene)
		{
			nowScene->Release();
			delete nowScene;
			nowScene = nullptr;
			OBJECTMANAGER->Release();
			OBJECTMANAGER->Init();
		}
		nowScene = nextScene;
		nowScene->Init();
		nextScene = nullptr;
		isSceneChange = false;
	}
	nowScene->Update();
}

void SceneManager::Render()
{
	if (nowScene)
		nowScene->Render();
}

void SceneManager::Release()
{
	SAFE_RELEASE(nowScene);
	SAFE_DELETE(nowScene);
	SAFE_RELEASE(nextScene);
	SAFE_DELETE(nextScene);
}
