#include "Application.h"
#pragma once

class GameObject;



class Component {

public:

	enum class ComponentType
	{
		NONE,
		TRANSFORM,
		MESH,
		MATERIAL,
	};
	ComponentType type;

	Component(GameObject* owner);
	virtual ~Component();

	virtual void Enable();
	virtual void Disable();
	virtual void Update();
	virtual void ShowEditor();

	bool Active;

	GameObject* Object;
};