#pragma once
#include "BaseScene.h"

class InGameScene :
	public BaseScene
{
public:
	InGameScene();
	virtual ~InGameScene();

private:
	CMeshLoader* mesh;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

