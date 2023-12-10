#pragma once
#include "Comp_Mesh.h"
#include "Application.h"
#include "ImGui/imgui.h"

//Comp_Mesh::Comp_Mesh() : Component(nullptr)
//{
//	type = ComponentType::MESH;
//	MESH = nullptr;
//
//	FaceNormals = false;
//}
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

	if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen)) {

		ImGui::TextWrapped("Information about the loaded mesh. There should be an option to display its normals(per - triangle and per - face).");

	}
	ImGui::NewLine();
}

void Comp_Mesh::SetMeshInfo(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
	
	if (!MESH) {
		MESH = new MeshData(); 
	}

	// Asignar la información de la malla
	MESH->vertices = vertices;
	MESH->indices = indices;
}