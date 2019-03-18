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
	MESHMANAGER->AddMeshAnime("EnemyBullet", L"./Resource/Enemy/enemy_attack/Enemy_Attack%d.obj", 0, ANIMEFRAME);
	MESHMANAGER->AddMeshAnime("stone", L"./Resource/stone/Stone_effect/stone_effect%d.obj", 0, ANIMEFRAME);
	MESHMANAGER->AddMeshAnime("Player_Idle2", L"./Resource/Player/idle_1_upgrade/Player_Idle_1_Upgrade%d.obj", 0, ANIMEFRAME);
	MESHMANAGER->AddMeshAnime("Player_Move2", L"./Resource/Player/move_1_upgrade/Player_moving_upgrade%d.obj", 0, ANIMEFRAME);
	MESHMANAGER->AddMeshAnime("Player_Idle2", L"./Resource/Player/idle_1_upgrade/Player_Idle_1_Upgrade%d.obj", 0, ANIMEFRAME);
	MESHMANAGER->AddMeshAnime("Player_Idle3", L"./Resource/Player/Idle_2_upgrade/Player_Idle_2_Upgrade%d.obj", 0, ANIMEFRAME);
	MESHMANAGER->AddMeshAnime("Player_Move3", L"./Resource/Player/move_2_upgrade/Player_move_2_Upgrade%d.obj", 0, ANIMEFRAME);
	MESHMANAGER->AddMeshAnime("Player_Idle3", L"./Resource/Player/Idle_2_upgrade/Player_Idle_2_Upgrade%d.obj", 0, ANIMEFRAME);

	MESHMANAGER->AddMeshLoader("enemy1", L"./Resource/Enemy/enemy1/enemy.obj");
	MESHMANAGER->AddMeshLoader("enemy2", L"./Resource/Enemy/enemy2_2/enemy2.obj");
	MESHMANAGER->AddMeshLoader("SkyBox", L"./Resource/SkyBox/skybox.obj");
	MESHMANAGER->AddMeshLoader("Background1", L"./Resource/Background/Map.obj");
	MESHMANAGER->AddMeshLoader("Plane", L"./Resource/Effect/dust.obj");

	MESHMANAGER->AddMeshLoader("120MM", L"./Resource/Bullet/EnemyBullet.obj");

	IMAGEMANAGER->AddTexture("IngameUI", "./Resource/UI/ui.png");
	IMAGEMANAGER->AddAnimeTexture("./Resource/UI/ui_upgrade_%d.png", 1, 3);
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
