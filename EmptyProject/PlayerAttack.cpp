#include "DXUT.h"
#include "PlayerAttack.h"

#include "Bullet.h"

PlayerAttack::PlayerAttack(float _startFrame, float _delay, float _gravity)
	:startFrame(_startFrame), delay(_delay), gravity(_gravity)
{
	frame = 0;
	isShootStart = false;
	isShoot = false;
}

void PlayerAttack::AttackUpdate(Vector3 _pos, Vector3 _moveVector, BULLET_STATE state, int damage)
{
	if (isShootStart)
	{
		frame += ELTIME * 10;

		if (frame >= delay)
		{
			isShootStart = false;
			isShoot = false;
			frame = 0;
		}
	}
	if (frame >= startFrame && isShoot == false)
	{
		isShoot = true;
		if(state == BULLET_STATE::BULLET_ENEMY)
			OBJECTMANAGER->AddObject(OBJ_EBULLET, new Bullet(_pos, _moveVector, state, gravity, damage));
		else
			OBJECTMANAGER->AddObject(OBJ_PBULLET, new Bullet(_pos, _moveVector, state, gravity, damage));
	}

}

void PlayerAttack::Attack()
{
	isShootStart = true;
}
