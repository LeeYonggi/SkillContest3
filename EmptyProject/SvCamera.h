#pragma once
#include "Camera.h"

class Player;
class SvCamera :
	public Camera
{
public:
	SvCamera(Player *_player);
	virtual ~SvCamera();

private:
	Player* player;

public:
	virtual void Update()	override;
	virtual void View()		override;
};

