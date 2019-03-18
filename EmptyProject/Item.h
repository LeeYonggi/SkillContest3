#pragma once
#include "Object.h"

enum ITEM_KINDS
{
	SPEED_UP,
	NEWCLEAR
};
class Item :
	public Object
{
public:
	Item(ITEM_KINDS _kind, Vector3 _pos);
	virtual ~Item();

private:
	ITEM_KINDS kind;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	ITEM_KINDS GetItemKind() { return kind; }
};

