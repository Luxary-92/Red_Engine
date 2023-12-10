#include "Comp_Transform.h"
#include "GameObject.h"
#include "Globals.h"


Comp_Transform::Comp_Transform(GameObject* owner) : Component(owner) {

	type = ComponentType::TRANSFORM;
	Object = owner;

	Reset();
}

Comp_Transform::~Comp_Transform() {

	type = ComponentType::TRANSFORM;

	Reset();
}

void Comp_Transform::Inspector_Info() {

	ImGui::NewLine();
	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {

		ImGui::NewLine();

		ImGui::Text("Position: "); 
		bool Change_P = ImGui::DragFloat3("Pos", &POSITION[0], 0.1f);
		ImGui::NewLine();

		ImGui::Text("Rotation: "); 
		bool Change_R = ImGui::DragFloat3("Rot", &ROTATION[0], 0.1f);
		ImGui::NewLine();

		ImGui::Text("Scale: ");
		bool Change_S = ImGui::DragFloat3("Sca", &SCALE[0], 0.1f);

		
		ImGui::NewLine();
		if (ImGui::Button("Update"))
			Transformations_Update();

		ImGui::NewLine();
		if (ImGui::Button("Reset"))
			Reset();
		ImGui::NewLine();
	}

}

void Comp_Transform::Reset() {
	matrix = { 1, 0, 0, 0,
			   0, 1, 0, 0,
		       0, 0, 1, 0,
			   0, 0, 0, 1 };

	POSITION = { 0, 0, 0 };
	ROTATION = { 0, 0, 0 };
	SCALE = { 1, 1, 1 };
}

void Comp_Transform::Update() {

}

float4x4 Comp_Transform::Matrix_Global(){

	return matrix;
}

float4x4 Comp_Transform::Matrix_Local() {
	return matrix;
}

void Comp_Transform::Set_Tranform(float3 position, float3 rotation, float3 scale) {

	POSITION = position;
	ROTATION = rotation;
	SCALE = scale;
	
	Transformations_Update();
}

float3 Comp_Transform::Get_Position() {
	return POSITION;
}
float3 Comp_Transform::Get_Rotation() {
	return ROTATION;
}
float3 Comp_Transform::Get_Scale() {
	return SCALE;
}

void Comp_Transform::Transformations_Update() {

	float rx = ROTATION.x * DEGTORAD;
	float ry = ROTATION.y * DEGTORAD;
	float rz = ROTATION.z * DEGTORAD;

	Quat Q;
	Q = Quat::FromEulerXYZ(rx, ry, rz);

	matrix = float4x4::FromTRS(POSITION, Q, SCALE).Transposed();

}