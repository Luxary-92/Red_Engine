#include "Globals.h"
#include "Application.h"

#include "ModuleMesh.h"

#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "Glew/include/glew.h"

ModuleMesh::ModuleMesh(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleMesh::~ModuleMesh()
{
}

bool ModuleMesh::Start()
{
    bool ret = true;

    struct aiLogStream stream;

    stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
    aiAttachLogStream(&stream);

   

    LoadFile(pathFile);

    return ret;
}

update_status ModuleMesh::PreUpdate(float dt)
{
    return UPDATE_CONTINUE;
}

update_status ModuleMesh::Update(float dt)
{
    return UPDATE_CONTINUE;
}

update_status ModuleMesh::PostUpdate(float dt)
{
    return UPDATE_CONTINUE;
}

void ModuleMesh::LoadFile(std::string Path)
{
    const aiScene* scene = aiImportFile(Path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
    if (scene != nullptr && scene->HasMeshes())
    {
        for (int i = 0; i < scene->mNumMeshes; i++)
        {
            MeshData* mesh = new MeshData();

            mesh->numVertex = scene->mMeshes[i]->mNumVertices;
            mesh->vertex = new float[mesh->numVertex * 3];

            memcpy(mesh->vertex, scene->mMeshes[i]->mVertices, sizeof(float) * mesh->numVertex * 3);

            if (scene->mMeshes[i]->HasFaces())
            {
                mesh->numIndex = scene->mMeshes[i]->mNumFaces * 3;
                mesh->index = new uint[mesh->numIndex];
                for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
                {
                    if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3) {
                        LOG("WARNING, geometry face with != 3 index!");
                    }
                    else
                        memcpy(&mesh->index[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));

                }
                meshes.push_back(mesh);
            }
            else
                delete mesh;
        }
        aiReleaseImport(scene);
    }
    else
        LOG("ERROR loading scene %s", Path);
}

void ModuleMesh::DrawMesh()
{
    for (int i = 0; i < meshes.size(); i++) {
        meshes[i]->DrawMesh();
    }
}

void MeshData::DrawMesh()
{
    glBegin(GL_TRIANGLES);

    for (int i = 0; i < numIndex; i++)
    {
        glVertex3f(vertex[index[i] * 3], vertex[index[i] * 3 + 1], vertex[index[i] * 3 + 2]);
    }
    glEnd();
}

bool ModuleMesh::CleanUp()
{
    aiDetachAllLogStreams();
    return true;
}
