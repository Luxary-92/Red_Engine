#pragma once
#include "Component.h"
#include "Module.h"
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

	std::string NAME;

	bool Active();
	void Enable();
	void Disable();
	void Update();

	void Inspector_Editor();

	bool active;
	bool destroy;

	std::string Object_Name;
	
	void AddComponent(Component* component);
	std::vector<Component*> Components;

	// Hierarchy
	GameObject* PARENT;
	void SetParent(GameObject* parent);
	void AddChild(GameObject* child);
	void DeleteChild(GameObject* child);

	std::vector<GameObject*> Children;

	Comp_Material* Get_Comp_Material();
	Comp_Mesh* Get_Comp_Mesh();
	Comp_Transform* Get_Comp_Transform();
	Comp_Transform* transform;
	/*Comp_Camera* Get_Comp_amera();*/
};