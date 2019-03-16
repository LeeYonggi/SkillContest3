#include "DXUT.h"
#include "Bullet.h"


Bullet::Bullet(Vector3 nowPos, Vector3 _moveVector, BULLET_STATE state)
{
	pos = nowPos;
	moveVector = _moveVector;
	bulletState = state;
	scale = { 0.05f, 0.05f, 0.05f };
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
		mesh = MESHMANAGER->AddMeshLoader("120MM", L"./Resource/Bullet/EnemyBullet.obj");
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
	switch (bulletState)
	{
	case BULLET_120MM:
		
		break;
	case BULLET_88MM:
		rotate.x = Billboarding(CAMERAMANAGER->GetCamera()->eye);
		break;
	default:
		break;
	}
	pos += moveVector * ELTIME * speed;

	frame += ELTIME;
}

void Bullet::Render()
{
	switch (bulletState)
	{
	case BULLET_120MM:
		MESHMANAGER->RenderAlphaMesh(mesh, pos, rotate, scale);
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
