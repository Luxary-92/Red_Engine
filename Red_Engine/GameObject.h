#pragma once
#include "Component.h"
#include "Module.h"
#include <vector>
#include <string>


class Comp_Material;
class Comp_Mesh;
class Comp_Transform;
class Comp_Camera;


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

	bool active;
	bool destroy;
	bool selected;

	std::string Object_Name;
	
	std::vector<Component*> Components;

	// Hierarchy
	GameObject* PARENT;
	void SetParent(GameObject* parent);
	void AddChild(GameObject* child);
	void DeleteChild(GameObject* child);

	std::vector<GameObject*> Children;

	Component* ADD_Component(ComponentType component);;
	Component* GET_Component(ComponentType type);

	std::vector<Component*> Compnet_Vector;
	std::vector<Component*> GetComponentsOfType(ComponentType type);

	Comp_Transform* transform;
	Comp_Mesh* mesh;
	Comp_Material* material;
	Comp_Camera* camera;

	template<typename T>

	T* Add_Component() {
		T* comp = new T(this);
		Compnet_Vector.push_back(comp);
		return comp;
	}

	/*Comp_Camera* Get_Comp_amera();*/
};