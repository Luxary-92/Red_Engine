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
    ILuint imageID;

    ilGenImages(1, &imageID);
    ilBindImage(imageID);
    ilLoadImage(path);

    width = ilGetInteger(IL_IMAGE_WIDTH);
    height = ilGetInteger(IL_IMAGE_HEIGHT);

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

GLuint ModuleTexture::LoadCheckerTexture()
{
 

    for (int i = 0; i < CHECKERS_HEIGHT; i++) {
        for (int j = 0; j < CHECKERS_WIDTH; j++) {
            int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
            checkerImage[i][j][0] = (GLubyte)c;
            checkerImage[i][j][1] = (GLubyte)c;
            checkerImage[i][j][2] = (GLubyte)c;
            checkerImage[i][j][3] = (GLubyte)255;
        }
    }


    GLuint textureID = 0;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerImage);

    glGenerateMipmap(GL_TEXTURE_2D);

    return textureID;
}


GLuint ModuleTexture::GetTextureID() 
{
    return textureID;
}