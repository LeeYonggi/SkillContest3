#include "DXUT.h"
#include "Object.h"


Object::Object()
{
	pos = { 0, 0, 0 };
	scale = { 1, 1, 1 };
	rotate = { 0, 0, 0 };
	isDestroy = false;
	isActive = true;
	texture = nullptr;
	frame = 0;
	color = { 255, 255, 255, 255 };
	nowAnime = 0;
	smoothRotate = 0;
	mesh = nullptr;
	velocity = 0;
	gravity = OBJGRAVITY;
}


Object::~Object()
{
	for (auto iter : animeMesh)
	{
		iter.clear();
	}
	animeMesh.clear();
}

bool Object::GetPixelCollision(Texture * tex, Vector2 p1, Vector2 p2)
{
	bool isCollision = false;
	D3DLOCKED_RECT lockRect;

	if (!tex)
		return false;
	tex->tex->LockRect(0, &lockRect, nullptr, D3DLOCK_DISCARD);
	DWORD *pColor = (DWORD*)lockRect.pBits;

	int x = p1.x - p2.x;
	int y = (tex->info.Height * 0.5f) - p1.y;

	int texW = tex->info.Width;

	if (x <= 0 || x >= tex->info.Width || y <= 0 || y >= tex->info.Height)
	{
		tex->tex->UnlockRect(0);
		return false;
	}

	D3DXCOLOR color = pColor[(y * tex->info.Width) + x];

	if (color == D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f))
		isCollision = true;

	tex->tex->UnlockRect(0);
	
	return isCollision;
}

Vector3 Object::GetVec3ToRotate(float _rotate)
{
	Vector3 temp = { 0, 0, 0 };
	temp.x = sin(D3DXToRadian(_rotate));
	temp.z = cos(D3DXToRadian(_rotate));
	D3DXVec3Normalize(&temp, &temp);
	return temp;
}

float Object::GetRotateToVec3(Vector3 p1, Vector3 p2)
{
	return D3DXToDegree(-atan2f(p2.z - p1.z, p2.x - p1.x)) + 90;
}

void Object::SmoothRotate()
{
	float temp = 360 * ((int)(rotate.y / 360) + 1) - rotate.y;
	float d1 = temp + smoothRotate;
	if (d1 < 180)
		smoothRotate = rotate.y + d1;
	else
	{
		smoothRotate = 360 * (int)(rotate.y / 360) + smoothRotate;
	}
}

void Object::PixelGroundCollision(Texture* tex1, Texture* tex2, Vector2 p1)
{
	velocity -= gravity;
	Vector2 tempPos1, tempPos2;
	tempPos1.x = pos.x;
	tempPos1.y = pos.z;
	tempPos2.x = pos.x;
	tempPos2.y = pos.y;
	//cout << tempPos2.x << " " << tempPos2.y << endl;
	if (GetPixelCollision(tex1, tempPos1, p1))
	{
		Vector2 point1, point2;
		point1.x = pos.x + GetVec3ToRotate(rotate.z - 90).x * 2.0f;
		point1.y = pos.y + GetVec3ToRotate(rotate.z - 90).z * 2.0f;
		point2.x = pos.x + GetVec3ToRotate(rotate.z + 90).x * 2.0f;
		point2.y = pos.y + GetVec3ToRotate(rotate.z + 90).z * 2.0f;
		if (GetPointCollision(tex2, &point1, p1) && GetPointCollision(tex2, &point2, p1))
		{
			rotate.z = GetRotateToVec3({ point1.x, 0, point1.y }, { point2.x, 0, point2.y }) - 90;
			Vector2 center = Lerp<Vector2>(point1, point2, 0.5f);
			pos.x = center.x + GetVec3ToRotate(rotate.z).x * 3.0f;
			pos.y = center.y + GetVec3ToRotate(rotate.z).z * 3.0f;
			velocity = 0;
		}
		
	}
	pos.y += velocity;
}

bool Object::GetPointCollision(Texture* tex1, Vector2 *p1, Vector2 p2)
{
	if (GetPixelCollision(tex1, *p1, p2))
	{
		for (int i = 0; i < 40; ++i)
		{
			if (!GetPixelCollision(tex1, *p1 * 10, p2))
			{
				p1->x = p1->x + GetVec3ToRotate(rotate.z - 180).x * 0.1;
				p1->y = p1->y + GetVec3ToRotate(rotate.z - 180).z * 0.1;
				return true;
			}
			p1->x = p1->x + GetVec3ToRotate(rotate.z + 180).x * 0.1;
			p1->y = p1->y + GetVec3ToRotate(rotate.z + 180).z * 0.1;
		}
	}
	else
	{
		for (int i = 0; i < 40; ++i)
		{
			if (GetPixelCollision(tex1, *p1 * 10, p2))
			{
				return true;
			}
			p1->x = p1->x + GetVec3ToRotate(rotate.z - 180).x * 0.1;
			p1->y = p1->y + GetVec3ToRotate(rotate.z - 180).z * 0.1;
		}
	}
	return false;
}

float Object::Billboarding(Vector3 p1)
{
	Vector3 temp = pos;
	temp.x = pos.z;
	temp.z = pos.y;
	p1.x = p1.z;
	p1.z = p1.y;
	return GetRotateToVec3(temp, p1);
}
