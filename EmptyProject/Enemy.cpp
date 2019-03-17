#include "DXUT.h"
#include "Enemy.h"

#include "PlayerAttack.h"
#include "Player.h"



Enemy::Enemy(Player * _player)
{
	player = _player;
	speed = 1.0f;
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	moveVector = { 0, 0, 0 };
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
	moveVector += GetTargetVec3(pos, player->pos);
	moveVector.x = min(max(moveVector.x, -20.0f), 20.0f);
	moveVector.z = min(max(moveVector.z, -20.0f), 20.0f);
	moveVector.y = 0;
	rotate.y = GetRotateToVec3(pos, pos + moveVector);
	pos += moveVector * ELTIME * speed;
}
