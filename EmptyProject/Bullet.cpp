#include "DXUT.h"
#include "Bullet.h"

#include "Particle.h"
#include "Background.h"


Bullet::Bullet(Vector3 nowPos, Vector3 _moveVector, BULLET_STATE state, float _gravity)
{
	pos = nowPos;
	moveVector = _moveVector;
	bulletState = state;
	scale = { 0.05f, 0.05f, 0.05f };
	gravity = _gravity;
	velocity = 0.5f;
}

Bullet::~Bullet()
{
	animeTexture.clear();
}

void Bullet::Init()
{
	switch (bulletState)
	{
	case BULLET_120MM:
		speed = 200;
		mesh = MESHMANAGER->AddMeshLoader("Bullet_120MM", L"./Resource/Bullet/120MM/rocket.obj");
		particle = OBJECTMANAGER->AddObject(OBJ_EFFECT, new Particle("./Resource/Effect/Dust/dust_%d.png", 1, 4, PARTICLE_KIND::STRAIGHT));
		break;
	case BULLET_88MM:
		speed = 100;
		mesh = MESHMANAGER->AddMeshLoader("Plane", L"./Resource/Effect/dust.obj");
		animeTexture = IMAGEMANAGER->AddAnimeTexture("./Resource/Bullet/88MM/88MM.png", 0, 0);
		scale = { 0.01f, 0.01f, 0.01f };
		break;
	default:
		break;
	}
}

void Bullet::Update()
{
	Vector3 temp = pos;
	pos += moveVector * ELTIME * speed;
	Vector3 effectMoveVector;
	float randY;
	float effectScale;
	auto iter = OBJECTMANAGER->GetObjects(OBJ_BACKGROUND)->begin();
	switch (bulletState)
	{
	case BULLET_120MM:
		velocity -= gravity;
		pos.y += velocity;
		if (temp.x > pos.x)
			rotate.z = -GetRotateToVec3({ temp.x, temp.y, temp.y }, { pos.x, pos.y, pos.y }) - 90;
		else
			rotate.z = -GetRotateToVec3({ pos.x, pos.y, pos.y }, { temp.x, temp.y, temp.y }) - 90;

		rotate.y = GetRotateToVec3({ temp.x, temp.y, temp.z }, { pos.x, pos.y, pos.z });

		effectMoveVector = temp - pos;
		D3DXVec3Normalize(&temp, &temp);
		randY = GetRandomNumber<int>(0, 180);
		effectScale = GetRandomNumber<int>(20, 50);
		particle->isActive = true;
		particle->ParticleInit(pos, { -90, 0, randY }, effectScale * 0.001f, effectMoveVector, 0.01f, 2.0f, 1.0f);
		if (GetPixelCollision(dynamic_cast<Background*>(*iter)->minimap2, { pos.x, pos.y }, { 0, 0 }))
		{
			particle->isActive = false;
		}
		
		break;
	case BULLET_88MM:
		rotate.x = Billboarding(CAMERAMANAGER->GetCamera()->eye);
		break;
	default:
		break;
	}
	if (GetPixelCollision(dynamic_cast<Background*>(*iter)->minimap2, { pos.x, pos.y }, { 0, 0 }))
	{
		isDestroy = true;
	}
	if (pos.x > 700 || pos.x < -100 ||
		pos.y > 100 || pos.y < -100 ||
		pos.z > 300 || pos.z < -300)
		isDestroy = true;

	frame += ELTIME;
}

void Bullet::Render()
{
	switch (bulletState)
	{
	case BULLET_120MM:
		MESHMANAGER->RenderAlphaMesh(mesh, pos, { rotate.x, rotate.y, rotate.z }, scale);
		break;
	case BULLET_88MM:
		MESHMANAGER->RenderEffect(mesh, animeTexture[0], pos, rotate, scale);
		break;
	default:
		break;
	}
}

void Bullet::Release()
{
}
