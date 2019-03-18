#pragma once
#include "Object.h"

enum BULLET_STATE
{
	BULLET_120MM,
	BULLET_88MM,
	BULLET_ENEMY
};
class Particle;
class Bullet :
	public Object
{
public:
	Bullet(Vector3 nowPos, Vector3 _moveVector, BULLET_STATE state, float _gravity, int _damage);
	virtual ~Bullet();

private:
	Vector3 moveVector;
	BULLET_STATE bulletState;
	float speed;
	vector<Texture*> animeTexture;
	Particle *particle;
	int damage;
	float gravity;
	float velocity;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public: 
	void DestroyBullet();

public:
	float GetDamage() { return damage; }
};

