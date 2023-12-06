#include "GameObject.h"
#include "Component.h"

#include "Comp_Transform.h"
#include "Comp_Mesh.h"
#include "Comp_Material.h"

GameObject::GameObject()
{


}

bool GameObject::isActive()
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