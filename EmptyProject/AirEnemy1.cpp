#include "DXUT.h"
#include "AirEnemy1.h"


AirEnemy1::AirEnemy1(Player *_player, Vector3 _pos)
	:Enemy(_player, 10.0f, _pos)
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
	pos = initVector;
	hp = 10;
	speed = 1.0f;

}

void AirEnemy1::Update()
{
	if (!IsCameraZone())
		return;
	AirEnemyMove();
	AirEnemyAttack();
	EnemyAttacked(5.0f, 6.0f);
}

void AirEnemy1::Render()
{
	MESHMANAGER->RenderMesh(mesh, pos, rotate, scale);
}

void AirEnemy1::Release()
{
}
