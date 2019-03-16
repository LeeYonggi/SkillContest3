#pragma once
#include "Singleton.h"

class MeshManager :
	public Singleton<MeshManager>
{
public:
	MeshManager();
	virtual ~MeshManager();

private:
	map<string, CMeshLoader*> m_MeshLoaders;
	map<wstring, vector<Material*>*> m_Material;

public:
	CMeshLoader *AddMeshLoader(string name, wstring route);
	vector<CMeshLoader*> AddMeshAnime(string name, wstring route, int low, int high);
	vector<Material*>* AddMaterial(wstring name, vector<Material*>* materials);
	void RenderMesh(CMeshLoader* meshLoader, Vector3 pos, Vector3 rotate = { 0, 0, 0 },
		Vector3 scale = { 1, 1, 1 }, Color color = { 255, 255, 255, 255 });
	void RenderAlphaMesh(CMeshLoader* meshLoader, Vector3 pos, Vector3 rotate = { 0, 0, 0 }, Vector3 scale = { 1, 1, 1 });
	void RenderEffect(CMeshLoader* meshLoader, Texture *texture, Vector3 pos, Vector3 rotate = { 0, 0, 0 }, Vector3 scale = { 1, 1, 1 },
		float alpha = 1.0f);
	
	void Release();

};

#define MESHMANAGER MeshManager::GetInstance()