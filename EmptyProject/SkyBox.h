#pragma once
#include "Object.h"
class SkyBox :
	public Object
{
public:
	SkyBox(Camera* _camera);
	virtual ~SkyBox();

private:
	Camera *camera;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

