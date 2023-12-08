#include "GameObject.h"
#include "Component.h"
#include "ModuleInput.h"

#include "Comp_Transform.h"
#include "Comp_Mesh.h"
#include "Comp_Material.h"

GameObject::GameObject()
{
	NAME = "GameObject";

	PARENT = nullptr;

	transform = new Comp_Transform(this);
	Components.push_back(transform);

	destroy = false;

}

GameObject::GameObject(GameObject* Object_parent)
{
	NAME = "GameObject";

	this->PARENT = Object_parent;
	destroy = false;

	if (Object_parent != nullptr) {
		Object_parent->Children.push_back(this);
	}

	transform = new Comp_Transform(this);
	Components.push_back(transform);
}


GameObject::~GameObject()
{
	NAME = "";
	transform = nullptr;

	if (destroy && PARENT != nullptr) {
		PARENT->DeleteChild(this);
	}

	for (size_t i = 0; i < Components.size(); ++i)
	{
		delete Components[i];
		Components[i] = nullptr;
	}
	Components.clear();

	for (size_t i = 0; i < Children.size(); i++)
	{
		Children[i] = nullptr;
	}


}

bool GameObject::Active()
{
	return active;
}

void GameObject::Enable()
{
	active = true;

	if (PARENT != nullptr)
		PARENT->Enable();
}

void GameObject::Disable()
{
	active = false;

}

void GameObject::Update()
{
	// No tots els children o components tenen un update
	for (size_t i = 0; i < Children.size(); ++i)
	{
		Children[i]->Update();
	}

	for (size_t i = 0; i < Components.size(); ++i)
	{
		Components[i]->Update();
	}
}

void GameObject::AddComponent(Component* component)
{
	component->Object = this;
	Components.push_back(component);
}

//Hierarchy
void GameObject::SetParent(GameObject* parent) {
	PARENT = parent;
}

void GameObject::DeleteChild(GameObject* child) {

	for (size_t i = 0; i < Children.size(); i++)
	{
		if (child == Children[i]) {
			Children.erase(Children.begin() + i);
		}
	}
	child->PARENT = nullptr;
}

void GameObject::AddChild(GameObject* child) {

	if (child->PARENT != nullptr) {
		child->PARENT->DeleteChild(child);
	}

	child->SetParent(this);

	Children.push_back(child);
}

//GameObject Componets
Comp_Material* GameObject::Get_Comp_Material() {

	for (size_t i = 0; i < Components.size(); i++)
	{
		if (Components[i]->type == ComponentType::MATERIAL)
		{
			return (Comp_Material*)Components[i];
		}
	}

	return nullptr;
}

Comp_Mesh* GameObject::Get_Comp_Mesh() {

	for (size_t i = 0; i < Components.size(); i++)
	{
		if (Components[i]->type == ComponentType::MESH)
		{
			return (Comp_Mesh*)Components[i];
		}
	}

	return nullptr;
}

Comp_Transform* GameObject::Get_Comp_Transform() {

	for (size_t i = 0; i < Components.size(); i++)
	{
		if (Components[i]->type == ComponentType::TRANSFORM)
		{
			return (Comp_Transform*)Components[i];
		}
	}
	return nullptr;
}

//Editor
void GameObject::Inspector_Editor() {

	for (size_t i = 0; i < Components.size(); i++)
	{
		ImGui::Separator();

		Components[i]->Inspector_Info();
	}
}

