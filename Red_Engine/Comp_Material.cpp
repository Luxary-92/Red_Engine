//#pragma once
//#include "Comp_Material.h"
//#include "ImGui/imgui.h"
//#include "Globals.h"
//#include "Application.h"
//
//Comp_Material::Comp_Material() : Component(nullptr) {
//
//	type = ComponentType::MATERIAL;
//
//}
//
//Comp_Material::Comp_Material(GameObject* owner) : Component(owner){
//
//	type = ComponentType::MATERIAL;
//	Object = owner;
//}
//
//Comp_Material::~Comp_Material()
//{
//}
//
//void Comp_Material::Texture_Set(const char* path)
//{
//	if (Texture_ID != 0)
//	{
//		App->textures->CleanTexture(Texture_ID);
//		Texture_ID = 0;
//	}
//
//	Texture_Path = path;
//	Texture_ID = App->textures->LoadTexture(path);
//
//
//	Texture_Update();
//}
//
//void Comp_Material::Texture_Reset()
//{
//	if (Texture_ID != 0)
//	{
//		App->textures->CleanTexture(Texture_ID);
//		Texture_ID = 0;
//	}
//
//	Texture_Update();
//}
//
//void Comp_Material::Texture_Update()
//{
//	Comp_Mesh* Component_Mesh = Object->Get_Comp_Mesh();
//
//	if (Component_Mesh == nullptr)
//		return;
//
//	if (Texture_Selected == 0)
//	{
//		Component_Mesh->MESH->id_texture = Texture_ID;
//
//		return;
//	}
//
//	if (Texture_Selected == 2)
//	{
//		Component_Mesh->MESH->id_texture = App->textures->checkersID;
//		return;
//	}
//
//	Component_Mesh->MESH->id_texture = -1;
//
//}
//
//void Comp_Material::Inspector_Info()
//{
//	ImGui::NewLine();
//	ImGui::TextWrapped("Display texture size and path.There should be an option to view the selected GameObject with the checkers texture."); 
//	ImGui::NewLine();
//
//}
