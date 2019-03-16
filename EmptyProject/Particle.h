#pragma once
#include "Object.h"

enum PARTICLE_KIND
{
	STRAIGHT,
	CIRCLE
};
class Particle :
	public Object
{
public:
	Particle(string _route, int _low, int _high, PARTICLE_KIND kind);
	virtual ~Particle();
	
private:
	PARTICLE_KIND kind;
public:
	Vector3 moveVector;
	float startFrame;
	string route;
	int low;
	int high;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	void ParticleInit(Vector3 _pos, float rotate, float scale, Vector3 _moveVector, float _startFrame);
};

