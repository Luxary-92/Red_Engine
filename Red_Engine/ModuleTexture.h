#ifndef ModuleTexture_H
#define ModuleTexture_H

#include "Globals.h"
#include "Application.h"
#include "Module.h"
#include "DevIL/include/il.h"
#include "DevIL/include/ilu.h"
#include "DevIL/include/ilut.h"

#pragma comment (lib, "DevIL/libx86/DevIL.lib")
#pragma comment (lib, "DevIL/libx86/ILU.lib")
#pragma comment (lib, "DevIL/libx86/ILUT.lib")

#define CHECKERS_HEIGHT 64
#define CHECKERS_WIDTH 64

class ModuleTexture : public Module {
public:
    ModuleTexture(Application* app, bool start_enabled = true);
    ~ModuleTexture();

    bool Init() override;
    bool CleanUp() override;
    GLuint LoadTexture(const char* path);
    GLuint LoadCheckerTexture();
    GLuint GetTextureID();



    GLuint textureID = 0;
    GLuint width;
    GLuint height;
    GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
    
};

#endif // ModuleTexture