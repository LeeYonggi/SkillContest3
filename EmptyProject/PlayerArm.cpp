#include "DXUT.h"
#include "PlayerArm.h"

#include "Player.h"
#include "PlayerAttack.h"
#include "Bullet.h"

PlayerArm::PlayerArm(Player* _player)
{
	player = _player;
}

PlayerArm::~PlayerArm()
{
	for (auto iter : playerAttack)
	{
		SAFE_DELETE(iter);
	}
	playerAttack.clear();
}

void PlayerArm::Init()
{
	animeMesh.push_back(MESHMANAGER->AddMeshAnime("Player_Arm_Idle", L"./Resource/Player/Idle/Arm/Player_Idle%d.obj", 0, ANIMEFRAME));
	animeMesh.push_back(MESHMANAGER->AddMeshAnime("Player_Arm_88MM", L"./Resource/Player/Attack/Arm/88MM/Player_Attack_Arm%d.obj", 0, 20));

	armState = PLAYERARM_STATE::PLAYERARM_IDLE;
	playerAttack.push_back(new PlayerAttack(2, 3));
	isFront = true;

	ArmInit();
}

void PlayerArm::Update()
{
	ArmInit();
	StateUpdate();

	for (int i = 0; i < playerAttack.size(); ++i)
	{
		Vector3 tempPos = { 0, 0, 0 };
		tempPos.x = pos.x + GetVec3ToRotate(rotate.z + 110).x * 1.5f;
		tempPos.y = pos.y + GetVec3ToRotate(rotate.z + 110).z * 1.5f;
		tempPos.z = pos.z;
		Vector3 tempVec3 = { 0, 0, 0 };
		tempVec3.x = GetVec3ToRotate(rotate.y).x * 0.2f;
		tempVec3.z = GetVec3ToRotate(rotate.y).z * 0.2f;
		playerAttack[i]->AttackUpdate(tempPos, tempVec3, BULLET_STATE::BULLET_88MM);
	}
	frame += ELTIME * 15;
	if (frame >= animeMesh[armState].size())
		frame = 0;
}

void PlayerArm::Render()
{
	if(isFront)
		MESHMANAGER->RenderMesh(animeMesh[armState][(int)frame], pos, { rotate.x, rotate.y - 90, rotate.z }, scale);
	else
		MESHMANAGER->RenderMesh(animeMesh[armState][(int)frame], pos, { rotate.y - 90, rotate.x, rotate.z }, scale);
}

void PlayerArm::Release()
{
}

void PlayerArm::ArmInit()
{
	pos = player->pos;
	rotate = player->rotate;
	scale = player->scale;
	color = player->color;

}

void PlayerArm::StateUpdate()
{
	switch (armState)
	{
	case PLAYERARM_IDLE:
		if (INPUTMANAGER->KeyDown('W'))
		{
			playerAttack[0]->Attack();
			armState = PLAYERARM_88MM;
			frame = 0;
		}
		break;
	case PLAYERARM_88MM:
		if (playerAttack[0]->isShootStart == false)
			playerAttack[0]->Attack();
		if (INPUTMANAGER->KeyDown('W'))
			armState = PLAYERARM_IDLE;
		break;
	default:
		break;
	}
}

