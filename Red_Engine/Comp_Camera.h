#include "Component.h"

class Comp_Camera : public Component
{
public:

	Comp_Camera();
	Comp_Camera(GameObject* owner);
	~Comp_Camera();

	void Enable();
	void Update();
	void Disable();

	void Inspector_Info();
};