#pragma once
#include "Object.h"


class Player;
class PlayerAttack;
enum PLAYERARM_STATE
{
	PLAYERARM_IDLE,
	PLAYERARM_88MM
};
class Particle;
class PlayerArm :
	public Object
{
public:
	PlayerArm(Player *_player);
	virtual ~PlayerArm();

private:
	Player *player;
	PLAYERARM_STATE armState;
	vector<PlayerAttack*> playerAttack;
	Particle *shootParticle;
	bool isFront;


public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	void ArmInit();
	void StateUpdate();
};

