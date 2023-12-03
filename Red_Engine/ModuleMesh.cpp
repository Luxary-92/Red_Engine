#include "Globals.h"
#include "Application.h"

#include "ModuleMesh.h"

#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "Glew/include/glew.h"


ModuleMesh::ModuleMesh(Application* app, bool start_enabled) : Module(app, start_enabled) {}

ModuleMesh::~ModuleMesh() {}

bool ModuleMesh::Init() {
    return true;
}

bool ModuleMesh::CleanUp() {
    meshes.clear();
    return true;
}

bool ModuleMesh::LoadFBX(const char* path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        // Error al cargar el archivo FBX
        return false;
    }

    // 1 textura
    aiString texturePath;
    if (scene->mMaterials[0]->GetTextureCount(aiTextureType_DIFFUSE) > 0 &&
        scene->mMaterials[0]->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) {
        std::string fullPath = std::string(path) + "/" + std::string(texturePath.C_Str());
        App->texture->LoadTexture(fullPath.c_str()); // Cargar textura
    }

    // Procesar mallas
    meshes.clear();
    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        MeshData mesh;
        aiMesh* aiMesh = scene->mMeshes[i];

        // Procesar vértices
        for (unsigned int j = 0; j < aiMesh->mNumVertices; ++j) {
            mesh.vertices.push_back(aiMesh->mVertices[j].x);
            mesh.vertices.push_back(aiMesh->mVertices[j].y);
            mesh.vertices.push_back(aiMesh->mVertices[j].z);

            if (aiMesh->HasTextureCoords(0)) {
                mesh.textureCoords.push_back(aiMesh->mTextureCoords[0][j].x);
                mesh.textureCoords.push_back(aiMesh->mTextureCoords[0][j].y);
            }
        }

        // Procesar índices
        for (unsigned int j = 0; j < aiMesh->mNumFaces; ++j) {
            aiFace face = aiMesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; ++k) {
                mesh.indices.push_back(face.mIndices[k]);
            }
        }

        meshes.push_back(mesh);
    }

    return true;
}

void ModuleMesh::DrawMesh() {
    glBindTexture(GL_TEXTURE_2D, App->texture->GetTextureID()); // Textura

    for (const auto& mesh : meshes) {
        glBegin(GL_TRIANGLES);

        for (size_t i = 0; i < mesh.indices.size(); ++i) {
            glTexCoord2f(mesh.textureCoords[i * 2], mesh.textureCoords[i * 2 + 1]);
            glVertex3f(mesh.vertices[mesh.indices[i] * 3], mesh.vertices[mesh.indices[i] * 3 + 1], mesh.vertices[mesh.indices[i] * 3 + 2]);
        }

        glEnd();
    }
}
