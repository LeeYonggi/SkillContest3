#include "DXUT.h"
#include "Background.h"


Background::Background()
{

}


Background::~Background()
{
}

void Background::Init()
{
	pos = { 0, 0, 0 };
	mesh = MESHMANAGER->AddMeshLoader("Background1", L"./Resource/Background/Map.obj");
	minimap1 = IMAGEMANAGER->AddTexture("Minimap1", "./Resource/Background/Minimap1.png");
	minimap2 = IMAGEMANAGER->AddTexture("Minimap2", "./Resource/Background/Minimap2.png");
}

void Background::Update()
{

}

void Background::Render()
{
	MESHMANAGER->RenderMesh(mesh, pos, rotate, scale);
}

void Background::Release()
{
}
