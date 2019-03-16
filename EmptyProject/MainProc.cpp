#include "DXUT.h"
#include "MainProc.h"

#include "InGameScene.h"
#include "LoadScene.h"

MainProc::MainProc()
{
}

MainProc::~MainProc()
{
}

void MainProc::Init()
{
	SCENEMANAGER->AddScene(new LoadScene());
}

void MainProc::Update()
{
	SCENEMANAGER->Update();
	OBJECTMANAGER->Update();
	INPUTMANAGER->Update();
}

void MainProc::Render()
{
	SCENEMANAGER->Render();
	OBJECTMANAGER->Render();
}

void MainProc::Release()
{
	ImageManager::ReleaseInstance();
	ObjectManager::ReleaseInstance();
	SceneManager::ReleaseInstance();
	InputManager::ReleaseInstance();
	MeshManager::ReleaseInstance();
	CameraManager::ReleaseInstance();
}
