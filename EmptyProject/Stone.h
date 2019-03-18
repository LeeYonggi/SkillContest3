#pragma once
#include "Enemy.h"
class Stone :
	public Enemy
{
public:
	Stone(Player *_player, Vector3 _pos);
	virtual ~Stone();

protected:

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

