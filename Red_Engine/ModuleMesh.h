#ifndef ModuleMesh_H
#define ModuleMesh_H

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/Importer.hpp"

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "ModuleRenderer3D.h"
#include "GameObject.h"
#include "Comp_Mesh.h"

#include <vector>

#pragma comment (lib, "Assimp/libx86/assimp.lib")

struct MeshData {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> textureCoords;
};

class ModuleMesh : public Module {
public:
    ModuleMesh(Application* app, bool start_enabled = true);
    ~ModuleMesh();

    bool Init() override;
    bool CleanUp() override;
    bool LoadFBX(const char* path);
    void DrawMesh();
    const std::vector<MeshData>& GetLoadedMeshes() const { return meshes; }
    size_t NumberOfMeshesInFBX() const { return meshes.size(); }

private:
    std::vector<MeshData> meshes;

};


#endif // ModuleMesh

