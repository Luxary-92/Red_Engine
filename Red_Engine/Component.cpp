#include "Component.h"

Component::Component(GameObject* owner)
{
	type = ComponentType::NONE;
	Active = false;
	this->Object = owner;
}

Component::~Component(){}

void Component::Update(){}

void Component::ShowEditor() {}

void Component::Enable() {}

void Component::Disable() {}