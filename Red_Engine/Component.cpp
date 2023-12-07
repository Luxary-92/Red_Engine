#include "Component.h"

Component::Component(GameObject* Owner)
{
	type = ComponentType::NONE;
	Active = false;
	this->Object = Owner;
}

Component::~Component(){}

void Component::Update(){}

void Component::Inspector_Info() {

}

void Component::Enable() {}

void Component::Disable() {}