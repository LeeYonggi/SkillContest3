#include "DXUT.h"
#include "Particle.h"

#include "Effect.h"



Particle::Particle(string _route, int _low, int _high, PARTICLE_KIND kind)
{
	moveVector = { 0, 0, 0 };
	startFrame = 0.5f;
	route = _route;
	low = _low;
	high = _high;
	this->kind = kind;
}

Particle::~Particle()
{
}

void Particle::Init()
{
	frame = 0;
}

void Particle::Update()
{
	if (frame >= startFrame)
	{
		Effect *obj = OBJECTMANAGER->AddObject(OBJ_EFFECT, new Effect(pos, moveVector, scale, false, 0.6f,
			route, low, high));
		obj->rotate.z = rotate.z;
		obj->speed = GetRandomNumber<int>(10, 30);
		obj->animeSpeed = 5.0f;
		frame = 0;
	}
	frame += ELTIME;
}

void Particle::Render()
{
}

void Particle::Release()
{
}

void Particle::ParticleInit(Vector3 _pos, float rotate, float scale, Vector3 _moveVector, float _startFrame)
{
	moveVector = _moveVector;
	startFrame = _startFrame;
	pos = _pos;
	this->rotate.z = rotate;
	this->scale.x = scale;
	this->scale.y = scale;
	this->scale.z = scale;
}
