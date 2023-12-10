#include "ModuleScene.h"
#include "GameObject.h"
#include "Application.h"


ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleScene::~ModuleScene()
{
}

bool ModuleScene::Init()
{
    return false;
}

bool ModuleScene::Start() {

    root = new GameObject(nullptr);
    root->NAME = ("Scene");
    Scene_Obejcts.push_back(root);

    test = new GameObject(nullptr);
    test->NAME = ("BakerHouse"); 
    root->AddChild(test);


    App->texture->LoadTexture("Assets/Baker_house.png");

    App->mesh->LoadFBX("Assets/BakerHouse.fbx");


    //App->mesh->LoadFBX("Assets/Street environment_V01.fbx");

    return true;
}


update_status ModuleScene::PreUpdate(float dt) {

    return UPDATE_CONTINUE;
}

update_status ModuleScene::Update(float dt) {

    return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate(float dt) {

    return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp() {

    LOG("Scene Cleanup")
        delete root;
    return true;
}

GameObject* ModuleScene::CreateGameObject(GameObject* parent)
{
    GameObject* NewGameObject = new GameObject(parent);

    return NewGameObject;
}
