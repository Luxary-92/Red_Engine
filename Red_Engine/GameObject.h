#include "Component.h"
#include "Module.h"
#pragma once
#include <vector>
#include <string>


class Comp_Material;
class Comp_Mesh;
class Comp_Transform;

class GameObject
{
public:

	GameObject();
	GameObject(GameObject* Object_parent);
	~GameObject();

	bool Active();
	void Enable();
	void Disable();

	bool active;
	bool destroy;

	std::string Object_Name;

	GameObject* parent;
	const std::vector<GameObject*>& GetChildren() const;
	std::vector<Component*> Components;
	std::vector<GameObject*> Children;

	Comp_Material* Get_Comp_Material();
	Comp_Mesh* Get_Comp_Mesh();
	Comp_Transform* Get_Comp_Transform();	
};