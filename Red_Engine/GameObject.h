#include "Application.h"
#include "Component.h"

class GameObject
{
public:

	GameObject();
	GameObject(GameObject* parent);
	~GameObject();

	bool isActive();
	void Enable();
	void Disable();

	bool active;
};