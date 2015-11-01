#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Common.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void addChild(shared_ptr<GameObject> child);
private:
	vector<shared_ptr<GameObject> > m_ChildObjects;
};


#endif