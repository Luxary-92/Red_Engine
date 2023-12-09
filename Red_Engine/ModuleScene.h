#pragma once
#include "Module.h"
#include "Globals.h"
#include <vector>

class GameObject;
class ModuleScene : public Module
{
public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void SceneWindow(bool& active);

	GameObject* CreateGameObject(GameObject* parent);

	std::vector<GameObject*> Scene_Obejcts;
	GameObject* root = nullptr;
	GameObject* test;


private:

};