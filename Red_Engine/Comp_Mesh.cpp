#pragma once
#include "Comp_Mesh.h"
#include "ImGui/imgui.h"

Comp_Mesh::Comp_Mesh() : Component(nullptr)
{
	type = ComponentType::MESH;
	MESH = nullptr;

	FaceNormals = false;
}
Comp_Mesh::Comp_Mesh(GameObject* owner) : Component(owner)
{
	type = ComponentType::MESH;
	Object = owner;
	MESH = nullptr;

	FaceNormals = false;
}

Comp_Mesh::Comp_Mesh::~Comp_Mesh()
{
	MESH = nullptr;
}

void Comp_Mesh::Inspector_Info()
{
	ImGui::NewLine();
	ImGui::TextWrapped("Information about the loaded mesh. There should be an option to display its normals(per - triangle and per - face).");
	ImGui::NewLine();
}