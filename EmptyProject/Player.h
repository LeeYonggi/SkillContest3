#pragma once
#include "Object.h"

enum PLAYER_STATE
{
	PLAYER_IDLE,
	PLAYER_MOVE,
	PLAYER_120MMATTACK
};
class PlayerAttack;
class Background;
class Particle;
class Player :
	public Object
{
public:
	Player(Background *_background);
	virtual ~Player();

private:
	float speed;
	Vector3 moveVector;
	vector<PlayerAttack*> playerAttack;
	Vector3 cDistance;
	PLAYER_STATE pState;
	Background *background;
	Particle *particle;
	vector<int> itemCount;
	CMeshLoader *shield;
	bool isSpeedUp;
	int jumpCount;
	bool isJump;
	float speedFrame;
	int hp;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	Vector3 PlayerController(bool *param);
	void StateUpdate(bool isMove);
	void ItemUpdate();
};

