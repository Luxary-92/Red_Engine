#ifndef ModuleMesh_H
#define ModuleMesh_H

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "ModuleRenderer3D.h"

#include <vector>
using namespace std;

#pragma comment (lib, "Assimp/libx86/assimp.lib")

struct MeshData {
    uint indexID = 0;
    uint numIndex = 0;
    uint* index = nullptr;
    uint vertexID = 0;
    uint numVertex = 0;
    float* vertex = nullptr;
    float* textureCoords;
    void DrawMesh();
};

class ModuleMesh : public Module
{
public:
    ModuleMesh(Application* app, bool start_enabled = true);
    ~ModuleMesh();

    vector<MeshData*> meshes;
    string pathFile;

    bool Start();

    update_status PreUpdate(float dt);
    update_status Update(float dt);
    update_status PostUpdate(float dt);

    void LoadFile(string Path);
    void DrawMesh();

    bool CleanUp();

};

#endif // ModuleMesh

