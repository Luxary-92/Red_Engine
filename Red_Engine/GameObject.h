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
	bool selected;

	std::string Object_Name;
	
	void AddComponent(Component* component);
	std::vector<Component*> Components;

	// Hierarchy
	GameObject* PARENT;
	void SetParent(GameObject* parent);
	void AddChild(GameObject* child);
	void DeleteChild(GameObject* child);

	std::vector<GameObject*> Children;

	Component* Add_Component(ComponentType component);;
	Component* Get_Component(ComponentType type);

	std::vector<Component*> Compnet_Vector;
	std::vector<Component*> GetComponentsOfType(ComponentType type);

	Comp_Transform* transform;


	template<typename T>
	T* Add_Component() {
		T* comp = new T(this);
		Compnet_Vector.push_back(comp);
		return comp;
	}

	/*Comp_Camera* Get_Comp_amera();*/
};