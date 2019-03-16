#include "DXUT.h"
#include "Camera.h"


Camera::Camera()
{
	eye = { 0, 0, -10 };
	at = { 0, 0, 0};
	up = { 0, 1, 0 };
}


Camera::~Camera()
{
}

void Camera::Update()
{
}

void Camera::View()
{
	D3DXMATRIX mat;
	D3DXMatrixLookAtLH(&mat, &eye, &at, &up);

	DEVICE->SetTransform(D3DTS_VIEW, &mat);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.3f, (float)SCREEN_X / (float)SCREEN_Y, 1.0f, 100000.0f);
	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);
}
