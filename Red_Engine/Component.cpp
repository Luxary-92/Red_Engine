#include "Component.h"

Component::Component(GameObject* Owner)
{
	type = ComponentType::NONE;
	Active = false;
	this->Object = Owner;
}

Component::~Component(){}

void Component::Update(){}

void Component::ShowEditor() {}

void Component::Enable() {}

void Component::Disable() {}