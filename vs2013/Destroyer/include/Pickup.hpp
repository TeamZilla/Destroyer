#pragma once

#include <UtH/UtHEngine.hpp>

class Pickup : public uth::GameObject
{
	bool m_isPressed;

public:
	//Pickup types-  0 Health  1 Score
	Pickup(int type);
	~Pickup();

	int pickupType;

	void update(float dt) override;
};