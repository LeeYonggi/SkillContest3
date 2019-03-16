#include "DXUT.h"
#include "ImageManager.h"


ImageManager::ImageManager()
{
	D3DXCreateSprite(DEVICE, &sprite);
	camScale = 0;
	camPos = { 0, 0 };
}


ImageManager::~ImageManager()
{
	Release();

	SAFE_RELEASE(sprite);
}

Texture *ImageManager::AddTexture(string name, string route)
{
	auto iter = m_Textures.find(name);
	if (iter != m_Textures.end()) return iter->second;

	Texture* temp = new Texture();
	D3DXGetImageInfoFromFileA(route.c_str(), &temp->info);
	D3DXCreateTextureFromFileExA(DEVICE,
		route.c_str(), 
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		temp->info.MipLevels, 0, 
		D3DFMT_A8B8G8R8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT,
		NULL,
		&temp->info,
		nullptr,
		&temp->tex);

	m_Textures.insert(make_pair(name, temp));

	return temp;
}

vector<Texture*> ImageManager::AddAnimeTexture(string route, int low, int high)
{
	vector<Texture*> temp;
	for (int i = low; i <= high; i++)
	{
		CHAR str[128];
		sprintf(str, route.c_str(), i);
		temp.push_back(AddTexture(str, str));
	}
	return temp;
}

void ImageManager::DrawTexture(string name, Vector2 pos, Vector2 scale, Vector2 camValue, float rotate, Vector2 length, Color color)
{
	auto iter = m_Textures.find(name);
	if (iter == m_Textures.end()) return;

	D3DXMATRIX matW, matS, matR, matT;
	D3DXMatrixScaling(&matS, scale.x + camScale, scale.y + camScale, 1);
	D3DXMatrixRotationZ(&matR, D3DXToRadian(rotate));
	pos = pos - camPos + (pos * camScale);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, 0);

	matW = matS * matR * matT;

	sprite->SetTransform(&matW);

	Vector3 center = { float(iter->second->info.Width) * 0.5f, 
		float(iter->second->info.Height) * 0.5f, 0 };

	RECT re = { 0, 0, iter->second->info.Width * length.x, iter->second->info.Height * length.y };

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
	sprite->Draw(iter->second->tex, &re, &center, nullptr, D3DCOLOR_RGBA(color.r, color.g, color.b, color.a));
	sprite->End();
}

void ImageManager::DrawTexture(Texture* texture, Vector2 pos, Vector2 scale, Vector2 camValue, float rotate, Vector2 length, Color color)
{
	D3DXMATRIX matW, matS, matR, matT;
	D3DXMatrixScaling(&matS, scale.x + camScale, scale.y + camScale, 1);
	D3DXMatrixRotationZ(&matR, D3DXToRadian(rotate));
	pos = pos - Vector2(camPos.x * camValue.x, camPos.y * camValue.y) + (pos * camScale * 0.1);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, 0);

	matW = matS * matR * matT;

	sprite->SetTransform(&matW);

	Vector3 center = { float(texture->info.Width) * 0.5f,
		float(texture->info.Height) * 0.5f, 0 };

	RECT re = { 0, 0, texture->info.Width * length.x, texture->info.Height * length.y };

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture->tex, &re, &center, nullptr, D3DCOLOR_RGBA(color.r, color.g, color.b, color.a));
	sprite->End();
}

void ImageManager::Release()
{
	for (auto iter : m_Textures)
	{
		SAFE_RELEASE(iter.second->tex);
		SAFE_DELETE(iter.second);
	}
	m_Textures.clear();
}
