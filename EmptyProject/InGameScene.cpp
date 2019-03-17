#include "DXUT.h"
#include "InGameScene.h"

#include "Player.h"
#include "PlayerArm.h"
#include "Background.h"
#include "AirEnemy1.h"

#include "SvCamera.h"
#include "SkyBox.h"

InGameScene::InGameScene()
{
}


InGameScene::~InGameScene()
{
}

void InGameScene::Init()
{
	Background* background = OBJECTMANAGER->AddObject(OBJ_BACKGROUND, new Background());
	Player* player = OBJECTMANAGER->AddObject(OBJ_PLAYER, new Player(background));
	OBJECTMANAGER->AddObject(OBJ_PLAYER, new PlayerArm(player));
	OBJECTMANAGER->AddObject(OBJ_ENEMY, new AirEnemy1(player));

	SvCamera *camera = new SvCamera(player);
	CAMERAMANAGER->Init(camera);
}

void InGameScene::Update()
{
	CAMERAMANAGER->Update();
}

void InGameScene::Render()
{
	CAMERAMANAGER->View();
}

void InGameScene::Release()
{
}
