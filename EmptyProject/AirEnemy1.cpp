#include "DXUT.h"
#include "AirEnemy1.h"


AirEnemy1::AirEnemy1(Player *_player)
	:Enemy(_player)
{
}


AirEnemy1::~AirEnemy1()
{
}

void AirEnemy1::Init()
{
	mesh = MESHMANAGER->AddMeshLoader("enemy1", L"./Resource/Enemy/enemy1/enemy.obj");
	speed = 0.5;
	scale = {0.01f, 0.01f, 0.01f};
	pos = {30, 10, 0};

}

void AirEnemy1::Update()
{
	AirEnemyMove();
}

void AirEnemy1::Render()
{
	MESHMANAGER->RenderMesh(mesh, pos, rotate, scale);
}

void AirEnemy1::Release()
{
}
