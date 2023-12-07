#pragma once

enum class ComponentType
{
	NONE,
	TRANSFORM,
	MESH,
	MATERIAL,
	CAMERA
};

class GameObject;

class Component {

public:
	Component(GameObject* Owner);
	virtual ~Component();

	ComponentType type;

	virtual void Enable();
	virtual void Disable();
	virtual void Update();
	virtual void ShowEditor();

	bool Active;

	GameObject* Object;
};