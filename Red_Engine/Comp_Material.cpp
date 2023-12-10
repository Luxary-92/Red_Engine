#pragma once
#include "Comp_Material.h"
#include "ImGui/imgui.h"
#include "Globals.h"
#include "Application.h"

Comp_Material::Comp_Material() : Component(nullptr) {

	type = ComponentType::MATERIAL;

}

Comp_Material::Comp_Material(GameObject* owner) : Component(owner){

	type = ComponentType::MATERIAL;
	Object = owner;
}

Comp_Material::~Comp_Material()
{
}

void Comp_Material::Texture_Update() {

}
void Comp_Material::Texture_Set(const char* path) {

}
void Comp_Material::Texture_Reset() {

}

void Comp_Material::Inspector_Info()
{
	ImGui::NewLine();

	if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen)) {
		ImGui::TextWrapped("Display texture size and path.There should be an option to view the selected GameObject with the checkers texture.");
	}

	ImGui::NewLine();
}
