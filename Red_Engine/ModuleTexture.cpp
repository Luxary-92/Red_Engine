#include "Globals.h"
#include "Application.h"

#include "ModuleTexture.h"



ModuleTexture::ModuleTexture(Application* app, bool start_enabled) : Module(app, start_enabled) {}

ModuleTexture::~ModuleTexture() {}

bool ModuleTexture::Init() {
    // Inicializa DevIL
    ilInit();
    iluInit();
    ilutInit();

    // 

    return true;
}

bool ModuleTexture::CleanUp() {
    // Limpia DevIL
    ilShutDown();
    //iluShutDown();
    //ilutShutDown();



    return true;
}

GLuint ModuleTexture::LoadTexture(const char* path)
{
    GLuint textureID = 0;
    ILuint imageID;

    ilGenImages(1, &imageID);
    ilBindImage(imageID);
    ilLoadImage(path);

    if (ilGetError() == IL_NO_ERROR)
    {
        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH),
            ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());

        glGenerateMipmap(GL_TEXTURE_2D);
    }

    ilDeleteImages(1, &imageID);

    return textureID;
}