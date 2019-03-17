#pragma once

#define OBJGRAVITY 0.02f
class Object
{
public:
	Object();
	virtual ~Object();

public:
	Vector3 pos;
	Vector3 scale;
	Vector3 rotate;
	bool isDestroy;
	bool isActive;
	Texture *texture;
	Color color;
	CMeshLoader *mesh;
	float velocity;
	float gravity;
	

protected:
	int nowAnime;
	float frame;
	float smoothRotate;
	vector<vector<CMeshLoader*>> animeMesh;

public:
	virtual void Init()		PURE;
	virtual void Update()	PURE;
	virtual void Render()	PURE;
	virtual void Release()	PURE;

public:
	bool GetPixelCollision(Texture *tex, Vector2 p1, Vector2 p2);
	Vector3 GetVec3ToRotate(float _rotate);
	float GetRotateToVec3(Vector3 p1, Vector3 p2);
	void SmoothRotate();
	void PixelGroundCollision(Texture *tex1, Texture* tex2, Vector2 p1);
	bool GetPointCollision(Texture *tex1, Vector2 *p1, Vector2 p2);
	float Billboarding(Vector3 p1);
	Vector3 GetTargetVec3(Vector3 p1, Vector3 target);
};

