#pragma once
class Camera
{
public:
	Camera();
	virtual ~Camera();

public:
	Vector3 eye;
	Vector3 at;
	Vector3 up;

public:
	virtual void Update();
	virtual void View();
};

