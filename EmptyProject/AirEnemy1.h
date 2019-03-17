#pragma once
#include "Enemy.h"

class AirEnemy1 :
	public Enemy
{
public:
	AirEnemy1(Player *_player);
	virtual ~AirEnemy1();

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

