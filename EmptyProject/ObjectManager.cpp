#include "DXUT.h"
#include "ObjectManager.h"


ObjectManager::ObjectManager()
{
	Init();
}


ObjectManager::~ObjectManager()
{
	Release();
}

void ObjectManager::Init()
{
	for (int i = 0; i < OBJ_UIEFFECT; ++i)
		m_Objects.insert(make_pair(OBJ_KINDS(i), new list<Object*>()));
}

void ObjectManager::Update()
{
	for (auto iter : m_Objects)
	{
		for (auto oiter = iter.second->begin(); oiter != iter.second->end(); )
		{
			if ((*oiter)->isDestroy)
			{
				SAFE_DELETE((*oiter));
				oiter = iter.second->erase(oiter);
			}
			else
			{
				if((*oiter)->isActive)
					(*oiter)->Update();
				++oiter;
			}
		}
	}
}

void ObjectManager::Render()
{
	for (auto iter : m_Objects)
	{
		for (auto oiter = iter.second->begin(); oiter != iter.second->end(); ++oiter)
		{
			if ((*oiter)->isActive)
				(*oiter)->Render();
		}
	}
}

void ObjectManager::Release()
{
	for (auto iter : m_Objects)
	{
		for (auto viter : *iter.second)
		{
			SAFE_RELEASE(viter);
			SAFE_DELETE(viter);
		}
		(*iter.second).clear();
		SAFE_DELETE(iter.second);
	}
	m_Objects.clear();
}
