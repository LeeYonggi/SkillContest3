#include "DXUT.h"
#include "Effect.h"



Effect::Effect(Vector3 _pos, Vector3 _moveVector, Vector3 _scale, bool _isBilllboarding, float _endTime,
	string route, int low, int high)
{
	pos = _pos;
	moveVector3 = _moveVector;
	scale = _scale;
	isBillboarding = _isBilllboarding;
	animeTexture = IMAGEMANAGER->AddAnimeTexture(route, low, high);
	mesh = MESHMANAGER->AddMeshLoader("Plane", L"./Resource/Effect/dust.obj");
	endTime = _endTime;
	color.a = 1.0f;
	speed = 10.0f;
	animeFrame = 0;
	animeSpeed = 15.0f;
}

Effect::~Effect()
{
}

void Effect::Init()
{

}

void Effect::Update()
{
	pos += moveVector3 * speed * ELTIME;
	if (frame > endTime)
		isDestroy = true;
	frame += ELTIME;
	animeFrame = frame * animeSpeed;
	if (animeFrame >= animeTexture.size())
		animeFrame = animeTexture.size() - 1;
}

void Effect::Render()
{
	MESHMANAGER->RenderEffect(mesh, animeTexture[int(animeFrame)], pos, rotate, scale);
}

void Effect::Release()
{
}
