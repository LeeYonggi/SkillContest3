#pragma once
#include "Object.h"

class Player;
class PlayerAttack;
class Enemy :
	public Object
{
public:
	Enemy(Player *_player);
	virtual ~Enemy();

protected:
	PlayerAttack *eAttack;
	Player *player;
	Vector3 moveVector;
	float speed;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	void AirEnemyMove();
};

