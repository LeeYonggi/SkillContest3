#include "DXUT.h"
#include "SvCamera.h"

#include "Player.h"


SvCamera::SvCamera(Player* _player)
{
	player = _player;
}

SvCamera::~SvCamera()
{
}


void SvCamera::Update()
{
	at = player->pos;
	Vector3 temp = player->pos;
	temp.z -= 20;
	temp.y += 15;
	eye.x = temp.x;
	eye = Lerp<Vector3>(eye, temp, 0.1f);
}

void SvCamera::View()
{
	Camera::View();
}
