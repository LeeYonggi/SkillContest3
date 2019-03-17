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

void PlayerAttack::AttackUpdate(Vector3 _pos, Vector3 _moveVector, BULLET_STATE state)
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
		OBJECTMANAGER->AddObject(OBJ_PBULLET, new Bullet(_pos, _moveVector, state, gravity));
	}

}

void PlayerAttack::Attack()
{
	isShootStart = true;
}
