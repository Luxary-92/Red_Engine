#pragma once
#include "Globals.h"
#include "GameObject.h"
#include "Component.h"
//#include "ModuleMesh.h"
#include <string>

struct MeshData;

class Comp_Mesh : public Component
{
public:
	Comp_Mesh();
	Comp_Mesh(GameObject* owner);
	~Comp_Mesh();

	MeshData* MESH;

	bool FaceNormals;

	void Inspector_Info();
	void SetMeshInfo(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
};