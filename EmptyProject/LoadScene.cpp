#include "DXUT.h"
#include "LoadScene.h"

#include "InGameScene.h"

LoadScene::LoadScene()
{
}


LoadScene::~LoadScene()
{
}

void LoadScene::Init()
{
	MESHMANAGER->AddMeshAnime("Player_Idle", L"./Resource/Player/Idle/Body/Player_Idle%d.obj", 0, ANIMEFRAME);
	MESHMANAGER->AddMeshAnime("Player_Arm_Idle", L"./Resource/Player/Idle/Arm/Player_Idle%d.obj", 0, ANIMEFRAME);
	MESHMANAGER->AddMeshAnime("Player_Arm_88MM", L"./Resource/Player/Attack/Arm/88MM/Player_Attack_Arm%d.obj", 0, ANIMEFRAME);

	MESHMANAGER->AddMeshLoader("SkyBox", L"./Resource/SkyBox/skybox.obj");
	MESHMANAGER->AddMeshLoader("Background1", L"./Resource/Background/Map.obj");
	MESHMANAGER->AddMeshLoader("Plane", L"./Resource/Effect/dust.obj");

	MESHMANAGER->AddMeshLoader("120MM", L"./Resource/Bullet/EnemyBullet.obj");
}

void LoadScene::Update()
{
	SCENEMANAGER->AddScene(new InGameScene());
}

void LoadScene::Render()
{
}

void LoadScene::Release()
{
}