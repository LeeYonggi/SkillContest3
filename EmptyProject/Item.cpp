#include "DXUT.h"
#include "Item.h"



Item::Item(ITEM_KINDS _kind, Vector3 _pos)
{
	kind = _kind;
	pos = _pos;
}

Item::~Item()
{
}

void Item::Init()
{
	switch (kind)
	{
	case SPEED_UP:
		mesh = MESHMANAGER->AddMeshLoader("speedUp", L"./Resource/Item/SpeedUp/Item.obj");
		scale = { 0.1f, 0.1f, 0.1f };
		break;
	default:
		break;
	}
}

void Item::Update()
{
	switch (kind)
	{
	case SPEED_UP:

		break;
	default:
		break;
	}
	pos.y += sin(frame) * 0.02f;
	frame += ELTIME;
}

void Item::Render()
{
	switch (kind)
	{
	case SPEED_UP:
		MESHMANAGER->RenderAlphaMesh(mesh, pos, rotate, scale);
		break;
	default:
		break;
	}
}

void Item::Release()
{
}
