#pragma once
#include "Singleton.h"

enum OBJ_KINDS
{
	OBJ_BACK1,
	OBJ_BACK2,
	OBJ_BACK3,
	OBJ_BACKGROUND,
	OBJ_OBSTACLE,
	OBJ_PLAYER,
	OBJ_ENEMY,
	OBJ_PBULLET,
	OBJ_EBULLET,
	OBJ_EFFECT,
	OBJ_UI,
	OBJ_UIEFFECT
};
class ObjectManager :
	public Singleton<ObjectManager>
{
public:
	ObjectManager();
	virtual ~ObjectManager();

private:
	map<OBJ_KINDS, list<Object*>*> m_Objects;

public:
	void Init();
	void Update();
	void Render();
	void Release();
	list<Object*>* GetObjects(OBJ_KINDS kind);
	template<class T>
	T* AddObject(OBJ_KINDS state, T *obj)
	{
		auto iter = m_Objects.find(state);
		if (iter == m_Objects.end()) return nullptr;

		iter->second->push_back(obj);
		obj->Init();

		return obj;
	}
};

#define OBJECTMANAGER ObjectManager::GetInstance()