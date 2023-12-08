#pragma once
#include "Component.h"

class Mesh;

class Comp_Mesh : public Component
{
public:
	Comp_Mesh();
	Comp_Mesh(GameObject* owner);
	~Comp_Mesh();

	Mesh* MESH;

	bool FaceNormals;

	void Inspector_Info();
};