#include "DXUT.h"
#include "PlayerArm.h"

#include "Player.h"
#include "PlayerAttack.h"
#include "Bullet.h"
#include "Particle.h"

PlayerArm::PlayerArm(Player* _player)
{
	player = _player;
	frontRotate = 0;
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
	playerAttack.push_back(new PlayerAttack(2, 3, 0));
	playerAttack.push_back(new PlayerAttack(2, 3, 0));
	isFront = true;
	shootParticle.push_back(OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_EFFECT,
		new Particle("./Resource/Effect/FastSpeed/effect_%d.png", 1, 5, PARTICLE_KIND::STRAIGHT)));
	shootParticle.push_back(OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_EFFECT,
		new Particle("./Resource/Effect/FastSpeed/effect_%d.png", 1, 5, PARTICLE_KIND::STRAIGHT)));
	for(int i = 0; i < 2; i++)
		shootParticle[i]->isActive = false;

	ArmInit();
}

void PlayerArm::Update()
{
	ArmInit();
	StateUpdate();

	for (int i = 0; i < 2; ++i)
	{
		Vector3 tempPos = { 0, 0, 0 };
		tempPos.x = pos.x + GetVec3ToRotate(rotate.y - 40 + i * 80).x * 2.0f;
		tempPos.y = pos.y + GetVec3ToRotate(-rotate.z + 110).z * 2.0f;
		tempPos.z = pos.z + GetVec3ToRotate(rotate.y - 40 + i * 80).z * 2.0f;
		Vector3 tempVec3 = { 0, 0, 0 };
		tempVec3.x = GetVec3ToRotate(rotate.y).x * 0.3f;
		tempVec3.y = GetVec3ToRotate(-rotate.z + 90).z * 0.3f;
		tempVec3.z = GetVec3ToRotate(rotate.y).z * 0.3f;
		if (!isFront)
		{
			tempVec3.x = 0;
			tempVec3.z = 0;
		}
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
	if(isFront)
		frontRotate = Lerp<float>(frontRotate, 0, 0.1f);
	else
		frontRotate = Lerp<float>(frontRotate, 90, 0.1f);
	rotate.z = frontRotate;
}

void PlayerArm::StateUpdate()
{
	Vector3 tempPos = { 0, 0, 0 };
	float tempRY;
	switch (armState)
	{
	case PLAYERARM_IDLE:
		if (INPUTMANAGER->KeyDown('W'))
		{
			for(int i = 0; i < 2; i++)
				playerAttack[i]->Attack();
			armState = PLAYERARM_88MM;
			frame = 0;
		}
		break;
	case PLAYERARM_88MM:
		for (int i = 0; i < 2; i++)
		{
			if (playerAttack[i]->isShootStart == false)
				playerAttack[i]->Attack();
		}
		if (INPUTMANAGER->KeyDown('2'))
		{
			isFront = !isFront;
		}
		for (int i = 0; i < 2; i++)
		{
			tempPos.x = pos.x + GetVec3ToRotate(rotate.y - 40 + i * 80).x * 2.0f;
			tempPos.y = pos.y + GetVec3ToRotate(-rotate.z + 110).z * 2.0f;
			tempPos.z = pos.z + GetVec3ToRotate(rotate.y - 40 + i * 80).z * 2.0f;
			shootParticle[i]->isActive = true;
			tempRY = (int)rotate.y % 360;
			if (tempRY > 90 && tempRY <= 270)
				tempRY -= 180;
			shootParticle[i]->ParticleInit(tempPos, { tempRY - 90, 0, 0 }, 0.05f, { 0, 0, 0 }, 0.6f, 10.0f, 0.5f);
		}
		if (INPUTMANAGER->KeyDown('W'))
		{
			for (int i = 0; i < 2; i++)
			{
				shootParticle[i]->isActive = false;
				shootParticle[i]->isActive = false;
			}
			armState = PLAYERARM_IDLE;
			frame = 0;
		}
		break;
	default:
		break;
	}
}

