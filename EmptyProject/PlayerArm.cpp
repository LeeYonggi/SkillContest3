#include "DXUT.h"
#include "PlayerArm.h"

#include "Player.h"
#include "PlayerAttack.h"
#include "Bullet.h"
#include "Particle.h"

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
	shootParticle = OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_EFFECT, 
		new Particle("./Resource/Effect/FastSpeed/effect_%d.png", 1, 5, PARTICLE_KIND::STRAIGHT));
	shootParticle->isActive = false;

	ArmInit();
}

void PlayerArm::Update()
{
	ArmInit();
	StateUpdate();

	for (int i = 0; i < playerAttack.size(); ++i)
	{
		Vector3 tempPos = { 0, 0, 0 };
		tempPos.x = pos.x + GetVec3ToRotate(rotate.y).x * 1.5f;
		tempPos.y = pos.y + GetVec3ToRotate(rotate.z + 110).z * 1.5f;
		tempPos.z = pos.z + GetVec3ToRotate(rotate.y).z * 1.5f;
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
	Vector3 tempPos = { 0, 0, 0 };
	float tempRY;
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
		{
			shootParticle->isActive = false;
			armState = PLAYERARM_IDLE;
		}
		tempPos.x = pos.x + GetVec3ToRotate(rotate.y).x * 1.5f;
		tempPos.y = pos.y + GetVec3ToRotate(rotate.z + 110).z * 1.5f;
		tempPos.z = pos.z + GetVec3ToRotate(rotate.y).z * 1.5f;
		shootParticle->isActive = true;
		tempRY = (int)rotate.y % 360;
		if (tempRY > 90 && tempRY <= 270)
			tempRY -= 180;
		shootParticle->ParticleInit(tempPos, { -90, tempRY, 0 }, 0.03f, {0, 0, 0}, 0.3f, 10.0f, 0.5f);
		break;
	default:
		break;
	}
}

