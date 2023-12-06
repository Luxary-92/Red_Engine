#include "GameObject.h"
#include "Component.h"

#include "Comp_Transform.h"
#include "Comp_Mesh.h"
#include "Comp_Material.h"

GameObject::GameObject()
{


}

bool GameObject::isActive() const
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
	//for (size_t i = 0; i < children.size(); i++)
	//{
	//	children[i]->Disable();
	//}
}