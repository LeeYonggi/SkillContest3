#pragma once
#include "Object.h"

class Player;
class PlayerAttack;
class Enemy :
	public Object
{
public:
	Enemy(Player *_player, float _bulletDelay, Vector3 _initVector);
	virtual ~Enemy();

protected:
	PlayerAttack *eAttack;
	Player *player;
	Vector3 moveVector;
	Vector3 initVector;
	float speed;
	int hp;
	vector<bool> isEffect;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	void AirEnemyMove();
	bool AirEnemyAttack();
	void EnemyAttacked(float animeSpeed, float endTime);
	bool IsCameraZone();
};

