#include "DXUT.h"
#include "Enemy.h"

#include "PlayerAttack.h"
#include "Player.h"
#include "Bullet.h"

#include "Effect.h"


Enemy::Enemy(Player * _player, float _bulletDelay, Vector3 _initVector)
{
	player = _player;
	eAttack = nullptr;
	eAttack = new PlayerAttack(3, _bulletDelay, 0);
	for (int i = 0; i < 4; ++i)
		isEffect.push_back(false);
	moveVector = { 0, 0, 0 };
	initVector = _initVector;
}

Enemy::~Enemy()
{
	SAFE_DELETE(eAttack);
	isEffect.clear();
}

void Enemy::Init()
{
}

void Enemy::Update()
{
}

void Enemy::Render()
{
}

void Enemy::Release()
{
}

void Enemy::AirEnemyMove()
{
	moveVector.x += GetTargetVec3(pos, player->pos).x;
	moveVector.z += GetTargetVec3(pos, player->pos).z;
	moveVector.x = min(max(moveVector.x, -20.0f), 20.0f);
	moveVector.z = min(max(moveVector.z, -20.0f), 20.0f);
	
	rotate.y = GetRotateToVec3(pos, pos + moveVector);
	pos += moveVector * ELTIME * speed;
}

bool Enemy::AirEnemyAttack()
{
	if (hp < 1) return false;
	Vector3 temp = GetTargetVec3(pos, player->pos);
	eAttack->AttackUpdate(pos, temp, BULLET_STATE::BULLET_ENEMY, 1);
	if (eAttack->isShootStart == false)
		eAttack->Attack();
	return false;
}

void Enemy::EnemyAttacked(float animeSpeed, float endTime)
{
	auto iter = OBJECTMANAGER->GetObjects(OBJ_PBULLET);
	for (auto _iter = iter->begin(); _iter != iter->end(); ++_iter)
	{
		if ((*_iter)->GetCircleCollision(pos, (*_iter)->pos, radius, (*_iter)->radius))
		{
			(*_iter)->isDestroy = true;
			dynamic_cast<Bullet*>((*_iter))->DestroyBullet();
			hp -= dynamic_cast<Bullet*>((*_iter))->GetDamage();
		}
	}
	if (hp < 1 && (isEffect[(int)frame % isEffect.size()] == false))
	{
		float scale = GetRandomNumber<int>(100, 300);
		int num = GetRandomNumber<int>(3, 6);
		Effect *obj = OBJECTMANAGER->AddObject(OBJ_EFFECT, new Effect(pos,
			{ 0, 0, 0 }, { 0.001f * scale, 0.001f * scale, 0.001f * scale }, true, 0.8f,
			"./Resource/Effect/bomb_effect/bomb_effect_%d.png", 1, 5));
		obj->animeSpeed = 10.0f;
		isEffect[(int)frame] = true;
	}
	if (hp < 1)
	{
		frame += ELTIME * animeSpeed;
		moveVector.y -= 0.4f;
		if (endTime <= frame)
		{
			isDestroy = true;
		}
	}
}

bool Enemy::IsCameraZone()
{
	return (pos.x < CAMERAMANAGER->GetCamera()->eye.x + 40);
}
