#pragma once
#include "BaseScene.h"

#define ANIMEFRAME 1
class LoadScene :
	public BaseScene
{
public:
	LoadScene();
	virtual ~LoadScene();

public:
	void Init()		override;
	void Update()	override;
	void Render()	override;
	void Release()	override;

};

