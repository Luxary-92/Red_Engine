#ifndef MODULE_EDITOR
#define MODULE_EDITOR

#include "Module.h"
#include "Globals.h"

#include <vector>
#include <string>

class ModuleEditor : public Module
{
public:

	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Init() override;
	void DrawEditor();
	bool CleanUp() override;

	void AddFPS(const float aFPS);
	std::vector<float> framesLog;
	float frames;
	float framesMax = 30;

	void AddMS(const float aDT);
	std::vector<float> milisecodsLog;
	float milisecods;
	float milisecodsMax = 30;
};

#endif //MODULE_EDITOR