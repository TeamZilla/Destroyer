#pragma once

#include <UtH/UtHEngine.hpp>

class Pickup : public uth::GameObject
{
	float m_timer, m_displayTime, m_Xdirection;
	bool m_smaller;
	int m_type;

public:
	//Pickup types-  0 Health  1 Score
	Pickup(int type, pmath::Vec2);
	~Pickup();

	int pickupType;
	bool isDestroyed;
	float m_rotation;
	float m_horizontal;
	float m_size;
	float m_vertSpeed;
	pmath::Vec2 m_pos;
	float m_scale;
	float m_angleSpeed;
	float m_angleAcc;
	float m_enlargement;

	void update(float dt) override;
};