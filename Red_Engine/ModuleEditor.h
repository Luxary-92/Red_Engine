#ifndef MODULE_EDITOR
#define MODULE_EDITOR

#include "Module.h"
#include "Globals.h"
#include "GameObject.h"

#include <vector>
#include <string>
#include <deque>

#define MAX_NAME_CHARACTERS 32

class ModuleEditor : public Module
{
private:

	void ConsoleWindow(bool& State);
	void ConfigurationWindow(bool& State);
	void HierarchyWindow(bool& State);
	void InspectorWindow(bool& State);
	void DrawHierarchyLevel(GameObject* gameObject);
	void AssetsWindow(bool& State);

public:

	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Init() override;
	void DrawEditor();
	bool CleanUp() override;

	void AddFPS(const float aFPS);
	std::vector<float> framesLog;
	float frames;
	float framesShown = 100;

	void AddMS(const float aDT);
	std::vector<float> milisecodsLog;
	float milisecods;
	float milisecodsShown = 20;

	bool ConfigState = true;
	bool HierarchyState = true;
	bool InspectorState = true;
	bool ConsoleState = true;
	bool AssetsState = true;

	int screen_width = 1280;
	int screen_height = 800;
	bool fullscreen = false;
	bool borderless = false;

	bool wireframe = false;
	bool depth_test = false;
	bool cull_face = false;
	bool color_material = false;
	bool lighting = false;
	bool texture_2d = false;

	std::deque<std::string>* logs = nullptr;

	//GameObject
	std::vector<GameObject*> AllGameObjects;

	GameObject* Selectet_GameObject = nullptr;
	char NewName[MAX_NAME_CHARACTERS];
};

#endif //MODULE_EDITOR