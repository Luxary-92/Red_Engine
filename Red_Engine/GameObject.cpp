#include "GameObject.h"
#include "Component.h"
#include "ModuleInput.h"

#include "Comp_Transform.h"
#include "Comp_Mesh.h"
#include "Comp_Material.h"

GameObject::GameObject() 
{
	Object_Name = "GameObject";
	parent = nullptr;
	destroy = false;

}

GameObject::GameObject(GameObject* Object_parent)
{
	Object_Name = "GameObject";
	this->parent = Object_parent;
	destroy = false;

	if (Object_parent != nullptr)
		Object_parent->Children.push_back(this);
}

const std::vector<GameObject*>& GameObject::GetChildren() const {
	return Children;
}

GameObject::~GameObject()
{
	for (size_t i = 0; i < Children.size(); i++)
	{
		Children[i] = nullptr;
	}
	Children.clear();
}

bool GameObject::Active()
{
	return active;
}

void GameObject::Enable()
{
	active = true;

	if (parent != nullptr)
		parent->Enable();
}

void GameObject::Disable()
{
	active = false;

}

//GameObject Componets
Comp_Material* GameObject::Get_Comp_Material() {

	return nullptr;
}

Comp_Mesh* GameObject::Get_Comp_Mesh() {

	return nullptr;
}

Comp_Transform* GameObject::Get_Comp_Transform() {

	return nullptr;
}

