#include "Component.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "ImGui/imgui.h"
#include <vector>
#include <string>

#pragma once

class Comp_Transform : public Component
{
public:
	Comp_Transform(GameObject* owner);
	~Comp_Transform();

	void Inspector_Info();

	void Reset();
	void Update();

	float4x4 Matrix_Global(), Matrix_Local();

	void Set_Tranform(float3 position, float3 rotation, float3 scale);

	float3 Get_Position();
	float3 Get_Rotation();
	float3 Get_Scale();

private:

	void Transformations_Update();

	float4x4 matrix;
	float3 POSITION, ROTATION, SCALE;
};