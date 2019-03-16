#include "DXUT.h"
#include "SkyBox.h"



SkyBox::SkyBox(Camera* _camera)
{
	camera = _camera;
}

SkyBox::~SkyBox()
{
}

void SkyBox::Init()
{
	mesh = MESHMANAGER->AddMeshLoader("SkyBox", L"./Resource/SkyBox/skybox.obj");
	pos = { 0, 0, 0 };
}

void SkyBox::Update()
{


}

void SkyBox::Render()
{
	pos = { 260, 87, 0 };
	DEVICE->SetRenderState(D3DRS_ZENABLE, false);
	MESHMANAGER->RenderMesh(mesh, pos, rotate, scale);
	DEVICE->SetRenderState(D3DRS_ZENABLE, true);
}

void SkyBox::Release()
{
}
