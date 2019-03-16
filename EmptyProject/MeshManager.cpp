#include "DXUT.h"
#include "MeshManager.h"


MeshManager::MeshManager()
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, true);
}


MeshManager::~MeshManager()
{
	Release();
}

CMeshLoader* MeshManager::AddMeshLoader(string name, wstring route)
{
	auto iter = m_MeshLoaders.find(name);
	if (iter != m_MeshLoaders.end()) return iter->second;

	CMeshLoader* temp = new CMeshLoader();
	temp->Create(DEVICE, route.c_str());

	m_MeshLoaders.insert(make_pair(name, temp));
	return temp;
}

vector<CMeshLoader*> MeshManager::AddMeshAnime(string name, wstring route, int low, int high)
{
	vector<CMeshLoader*> temp;
	for (int i = low; i <= high; ++i)
	{
		WCHAR str[128];
		wsprintf(str, route.c_str(), i);
		char ctr[8];
		sprintf(ctr, "%d", i);
		temp.push_back(AddMeshLoader(name + ctr, str));
	}
	return temp;
}

vector<Material*>* MeshManager::AddMaterial(wstring name, vector<Material*>* materials)
{
	auto iter = m_Material.find(name);
	if (iter != m_Material.end()) return iter->second;

	m_Material.insert(make_pair(name, materials));
	return nullptr;
}

void MeshManager::RenderMesh(CMeshLoader* meshLoader, Vector3 pos, Vector3 rotate, Vector3 scale, Color color)
{
	D3DXMATRIX matW, matT, matRX, matRY, matRZ, matS;

	D3DXMatrixScaling(&matS, scale.x, scale.y, scale.z);
	D3DXMatrixRotationX(&matRX, D3DXToRadian(rotate.x));
	D3DXMatrixRotationY(&matRY, D3DXToRadian(rotate.y));
	D3DXMatrixRotationZ(&matRZ, D3DXToRadian(rotate.z));
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);

	matRX = matRX * matRY * matRZ;
	matW = matS * matRX * matT;

	DEVICE->SetTransform(D3DTS_WORLD, &matW);

	Vector3 dir(1.0f, -1.0f, 1.0f);
	D3DXCOLOR tempColor(D3DCOLOR_ARGB(color.r, color.g, color.b, color.a));
	D3DLIGHT9 light = d3d::InitDirectionalLight(&dir, &tempColor);
	 
	DEVICE->SetLight(0, &light);
	DEVICE->LightEnable(0, true);

	DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	DEVICE->SetRenderState(D3DRS_SPECULARENABLE, true);

	for (int i = 0; i < meshLoader->GetNumMaterials(); i++)
	{
		D3DMATERIAL9 mtl = meshLoader->GetMaterial(i)->mat;
		mtl.Ambient.a = meshLoader->GetMaterial(i)->fAlpha;
		mtl.Diffuse.a = meshLoader->GetMaterial(i)->fAlpha;
		mtl.Specular.a = meshLoader->GetMaterial(i)->fAlpha;
		mtl.Emissive.a = meshLoader->GetMaterial(i)->fAlpha;
		mtl.Power = 1.0f;
		
		DEVICE->SetMaterial(&mtl);
		DEVICE->SetTexture(0, meshLoader->GetMaterial(i)->pTexture);
		meshLoader->GetMesh()->DrawSubset(i);
	}
}

void MeshManager::RenderAlphaMesh(CMeshLoader* meshLoader, Vector3 pos, Vector3 rotate, Vector3 scale)
{
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	RenderMesh(meshLoader, pos, rotate, scale);

	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BOTHSRCALPHA);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BOTHSRCALPHA);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

}

void MeshManager::RenderEffect(CMeshLoader* meshLoader, Texture* texture, Vector3 pos, Vector3 rotate, Vector3 scale, float alpha)
{
	D3DXMATRIX matW, matT, matRX, matRY, matRZ, matS;

	D3DXMatrixScaling(&matS, scale.x, scale.y, scale.z);
	D3DXMatrixRotationX(&matRX, D3DXToRadian(rotate.x));
	D3DXMatrixRotationY(&matRY, D3DXToRadian(rotate.y));
	D3DXMatrixRotationZ(&matRZ, D3DXToRadian(rotate.z));
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);

	matRX = matRX * matRY * matRZ;
	matW = matS * matRX * matT;

	DEVICE->SetTransform(D3DTS_WORLD, &matW);

	Vector3 dir(1.0f, -1.0f, 1.0f);
	D3DXCOLOR tempColor(1, 1, 1, 1);
	D3DLIGHT9 light = d3d::InitDirectionalLight(&dir, &tempColor);

	DEVICE->SetLight(0, &light);
	DEVICE->LightEnable(0, true);

	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, false);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	for (int i = 0; i < meshLoader->GetNumMaterials(); i++)
	{
		D3DMATERIAL9 mtl = meshLoader->GetMaterial(i)->mat;
		mtl.Ambient.a = alpha;
		mtl.Diffuse.a = alpha;
		mtl.Specular.a = alpha;
		mtl.Emissive.a = alpha;
		mtl.Power = 1.0f;

		DEVICE->SetMaterial(&mtl);
		DEVICE->SetTexture(0, texture->tex);
		meshLoader->GetMesh()->DrawSubset(i);
	}

	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, true);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BOTHINVSRCALPHA);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BOTHINVSRCALPHA);
}

void MeshManager::Release()
{
	for (auto iter : m_MeshLoaders)
	{
		if (iter.second)
			delete iter.second;
	}
	m_MeshLoaders.clear();
	for (auto iter : m_Material)
	{
		for (auto _iter : (*iter.second))
		{
			SAFE_DELETE(_iter);
		}
		(*iter.second).clear();
	}
	m_Material.clear();
}
