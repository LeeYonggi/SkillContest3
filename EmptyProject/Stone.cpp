#include "DXUT.h"
#include "Stone.h"

#include "Item.h"

Stone::Stone(Player *_player, Vector3 _pos)
	:Enemy(_player, 0, _pos)
{
}


Stone::~Stone()
{
}

void Stone::Init()
{
	animeMesh.push_back(MESHMANAGER->AddMeshAnime("stone", L"./Resource/stone/Stone_effect/stone_effect%d.obj", 0, 20));
	hp = 30;
	scale = { 0.1f, 0.1f, 0.1f };
	frame = 0;
	pos = initVector;
	radius = 3;
}

void Stone::Update()
{
	EnemyAttacked(25.0f, 20.0f);
	if (isDestroy == true)
		OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_ITEM, new Item(ITEM_KINDS::SPEED_UP, { pos.x, pos.y + 1.5f, pos.z }));
}

void Stone::Render()
{
	MESHMANAGER->RenderMesh(animeMesh[0][(int)frame % animeMesh[0].size()], pos, rotate, scale);
}

void Stone::Release()
{
}
