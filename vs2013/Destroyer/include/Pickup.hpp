#pragma once

#include <UtH/UtHEngine.hpp>

class Pickup : public uth::GameObject
{
	float m_timer, m_displayTime, m_Xdirection;
	bool m_smaller;

public:
	//Pickup types-  0 Health  1 Score
	Pickup(int type);
	~Pickup();

	int pickupType;
	bool isDestroyed;

	void update(float dt) override;
};