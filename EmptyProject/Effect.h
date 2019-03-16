#pragma once
#include "Object.h"
class Effect :
	public Object
{
public:
	Effect(Vector3 _pos, Vector3 _moveVector, Vector3 _scale, bool _isBilllboarding, float _endTime,
		string route, int low, int high);
	virtual ~Effect();

private:
	float alpha;
	bool isBillboarding;
	Vector3 moveVector3;
	vector<Texture*> animeTexture;
	float endTime;
	float animeFrame;

public:
	float animeSpeed;
	float speed;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

