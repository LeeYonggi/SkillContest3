#pragma once
#include "Singleton.h"

struct Texture
{
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 tex;
};

struct Color
{
	int r, b, g, a;

	Color() { }
	Color(int _r, int _b, int _g, int _a)
		: r(_r), b(_b), g(_g), a(_a)
	{
	}
};
class ImageManager :
	public Singleton<ImageManager>
{
public:
	ImageManager();
	virtual ~ImageManager();

private:
	map<string, Texture*> m_Textures;

public:
	LPD3DXSPRITE sprite;
	LPD3DXFONT font;
	Vector2 camPos;
	float camScale;

public:
	Texture *AddTexture(string name, string route);
	vector<Texture*> AddAnimeTexture(string route, int low, int high);
	void DrawTexture(string name, Vector2 pos, Vector2 scale = { 1, 1 }, Vector2 camValue = { 1, 1 },
		float rotate = 0, Vector2 length = { 1, 1 }, Color color = { 255, 255, 255, 255 });
	void DrawTexture(Texture* texture, Vector2 pos, Vector2 scale = { 1, 1 }, Vector2 camValue = { 1, 1 },
		float rotate = 0, Vector2 length = { 1, 1 }, Color color = { 255, 255, 255, 255 });
	void DrawFont(string str, Vector2 pos, Vector2 scale = { 1, 1 }, Color color = { 255, 255, 255, 255 });

	void Release();
};

#define IMAGEMANAGER ImageManager::GetInstance()