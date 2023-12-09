#include "GameObject.h"
#include "Module.h"
#include "ImGui/imgui.h"
#include "Comp_Camera.h"



Comp_Camera::Comp_Camera() :Component(nullptr) {

	type = ComponentType::CAMERA;
}

Comp_Camera::Comp_Camera(GameObject* owner) : Component(owner) {

	type = ComponentType::MATERIAL;
	Object = owner;
}


Comp_Camera::~Comp_Camera() {

}

void Comp_Camera::Enable()
{

}

void Comp_Camera::Update()
{

}

void Comp_Camera::Disable()
{

}

void Comp_Camera::Inspector_Info()
{
	ImGui::NewLine();
	ImGui::TextWrapped("a component with settings that can be modified.");
	ImGui::NewLine();

}