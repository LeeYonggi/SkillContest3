#pragma once
class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();

public:
	virtual void Init()		PURE;
	virtual void Update()	PURE;
	virtual void Render()	PURE;
	virtual void Release()	PURE;
};

