#include "DXUT.h"
#include "Player.h"

#include "Background.h"
#include "Bullet.h"
#include "PlayerAttack.h"
#include "Background.h"
#include "Effect.h"
#include "Particle.h"
#include "Item.h"


Player::Player(Background* _background)
{
	background = _background;
	particle = nullptr;
}

Player::~Player()
{
	for (auto iter : playerAttack)
	{
		SAFE_DELETE(iter);
	}
	playerAttack.clear();
	if(particle)
		particle->isDestroy = true;
}

void Player::Init()
{
	cDistance = { 20.0f, 2.5f, -4.0f };
	pos = cDistance;
	pos.y += 3;
	speed = 0.2f;
	scale = { 0.05, 0.05, 0.05 };
	rotate = { 0, 90, 0 };
	smoothRotate = 90.0f;
	moveVector = { 0.2f, 0.0f, 0.0f };
	jumpCount = 1;
	isJump = false;
	pState = PLAYER_STATE::PLAYER_IDLE;
	for (int i = 0; i < ITEM_KINDS::NEWCLEAR; ++i)
		itemCount.push_back(1);
	isSpeedUp = false;
	hp = 3;
	shield = MESHMANAGER->AddMeshLoader("Run_Effect", L"./Resource/Effect/run_effect_1/run_effect.obj");
	animeMesh.push_back(MESHMANAGER->AddMeshAnime("Player_Idle", L"./Resource/Player/Idle/Body/Player_Idle%d.obj", 0, ANIMEFRAME));
	animeMesh.push_back(MESHMANAGER->AddMeshAnime("Player_Move", L"./Resource/Player/Move/Body/Player_Move%d.obj", 0, ANIMEFRAME));
	animeMesh.push_back(MESHMANAGER->AddMeshAnime("Player_120MM", L"./Resource/Player/Idle/Body/Player_Idle%d.obj", 0, ANIMEFRAME));
	playerAttack.push_back(new PlayerAttack(3, 6, OBJGRAVITY + 0.02));
	texture = IMAGEMANAGER->AddTexture("bb", "./Resource/UI/ui.png");

	particle = OBJECTMANAGER->AddObject(OBJ_EFFECT, new Particle("./Resource/Effect/Dust/dust_%d.png", 1, 4, PARTICLE_KIND::STRAIGHT));
	particle->isActive = false;
	radius = 1.5f;
}

void Player::Update()
{
	bool isControl = false;
	ItemUpdate();

	if (isJump)
	{
		velocity -= gravity;
		pos.y += velocity;
		cout << velocity << endl;
		if (velocity < 0.0)
		{
			isJump = false;
			gravity = OBJGRAVITY;
		}
	}
	else
	{
		PixelGroundCollision(background->minimap1, background->minimap2, { background->pos.x, background->pos.z });
		if (velocity == 0 && jumpCount == 0)
			jumpCount = 1;
	}

	Vector3 temp = PlayerController(&isControl);
	StateUpdate(isControl);
	particle->isActive = false;
	if (isControl == true && (pState == PLAYER_IDLE || pState == PLAYER_MOVE))
	{
		moveVector = temp;
		pos += moveVector;
		smoothRotate = GetRotateToVec3(pos, pos + moveVector);
		SmoothRotate();
		Vector3 effectVec3 = moveVector;
		effectVec3.x = -moveVector.x;
		effectVec3.z = -moveVector.z;
		float pScale  = GetRandomNumber<int>(20, 40);
		float pRotate = GetRandomNumber<int>(0, 180);
		particle->ParticleInit({ pos.x, pos.y - 2.5f, pos.z }, { 0, pRotate, 0 }, pScale * 0.001f, effectVec3, 0.15f, 5.0f, 0.6f);
		particle->isActive = true;
	}
	rotate.y = Lerp<float>(rotate.y, smoothRotate, 0.1f);

	playerAttack[0]->AttackUpdate(pos, moveVector, BULLET_STATE::BULLET_120MM, 2);

	frame += ELTIME * 15;
	if (frame >= animeMesh[0].size())
		frame = 0;
}

void Player::Render()
{
	MESHMANAGER->RenderMesh(animeMesh[pState][(int)frame], pos, { rotate.x, rotate.y - 90, -rotate.z } , scale);
	if(isSpeedUp == true)
		MESHMANAGER->RenderAlphaMesh(shield, pos, { rotate.x, rotate.y, rotate.z }, scale * 0.7f);
	IMAGEMANAGER->DrawTexture(texture, {640, 360});
}

void Player::Release()
{
}

Vector3 Player::PlayerController(bool *param)
{
	Vector3 temp = { 0, 0, 0 };
	if (INPUTMANAGER->KeyPress(VK_LEFT))
	{
		temp.x += GetVec3ToRotate(rotate.z - 90).x * speed;
		temp.y += GetVec3ToRotate(rotate.z - 90).z * speed;
		*param = true;
	}
	if (INPUTMANAGER->KeyPress(VK_UP))
	{
		temp.z += speed;
		*param = true;
	}
	if (INPUTMANAGER->KeyPress(VK_RIGHT))
	{
		temp.x += GetVec3ToRotate(rotate.z + 90).x * speed;
		temp.y += GetVec3ToRotate(rotate.z + 90).z * speed;
		*param = true;
	}
	if (INPUTMANAGER->KeyPress(VK_DOWN))
	{
		temp.z -= speed;
		*param = true;
	}
	if (INPUTMANAGER->KeyDown(VK_SPACE) && isJump == false)
	{
		if(jumpCount > 0)
		{
			isJump = true;
			velocity = 0.5f;
			jumpCount -= 1;
		}
	}
	return temp;
}

void Player::StateUpdate(bool isMove)
{
	if (INPUTMANAGER->KeyDown('Q') && playerAttack[0]->isShootStart == false)
	{
		playerAttack[0]->Attack();
		pState = PLAYER_120MMATTACK;
	}

	switch (pState)
	{
	case PLAYER_IDLE:
		if (isMove)
			pState = PLAYER_MOVE;
		break;
	case PLAYER_MOVE:
		if (!isMove)
			pState = PLAYER_IDLE;
		break;
	case PLAYER_120MMATTACK:
		if (playerAttack[0]->isShootStart == false)
			pState = PLAYER_IDLE;
		break;
	default:
		break;
	}
}

void Player::ItemUpdate()
{
	auto iter = OBJECTMANAGER->GetObjects(OBJ_ITEM);
	for (auto _iter = iter->begin(); _iter != iter->end(); ++_iter)
	{
		if ((*_iter)->GetCircleCollision(pos, (*_iter)->pos, radius, (*_iter)->radius))
		{
			itemCount[dynamic_cast<Item*>((*_iter))->GetItemKind()] += 1;
			(*_iter)->isDestroy = true;
		}
	}

	if (INPUTMANAGER->KeyDown('1') && itemCount[0] > 0)
	{
		itemCount[0] -= 1;
		isSpeedUp = true;
		speed = 0.4f;
		speedFrame = timeGetTime() + 1000;
	}
	if (speedFrame < timeGetTime() && isSpeedUp)
	{
		isSpeedUp = false;
		speed = 0.2f;
	}
}
