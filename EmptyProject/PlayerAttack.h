#pragma once

enum BULLET_STATE;
class PlayerAttack
{
public:
	PlayerAttack(float _startFrame, float _delay, float _gravity);
	virtual ~PlayerAttack() {}

public:
	float frame;
	float startFrame;
	float delay;
	float gravity;
	bool isShootStart;
	bool isShoot;

public:
	void AttackUpdate(Vector3 _pos, Vector3 _moveVector, BULLET_STATE state);
	void Attack();

};