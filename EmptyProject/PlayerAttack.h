#pragma once

enum BULLET_STATE;
class PlayerAttack
{
public:
	PlayerAttack(float _startFrame, float _delay);
	virtual ~PlayerAttack() {}

public:
	float frame;
	float startFrame;
	float delay;
	bool isShootStart;
	bool isShoot;

public:
	void AttackUpdate(Vector3 _pos, Vector3 _moveVector, BULLET_STATE state);
	void Attack();

};