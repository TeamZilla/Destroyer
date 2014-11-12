#pragma once
#ifndef TankBehavior_HPP
#define TankBehavior_HPP

#include <UtH/UtHEngine.hpp>


class AeroplaneBehavior : public uth::Component
{
private: 
	float pathFlatnes; // ++ for flatnes
	float m_speed;
	void rotation();
	float m_time;
	float m_minY;
	float m_startX;
	int m_direction; // uses values 1 and -1 only.
	pmath::Vec2f m_pos;
	void pathFunc();
	void explodeCheck();
	float m_dt;
	pmath::Vec2f prevPos;
	float accelerate;
	float angle;
	float sliding;
	float verticalScaler;
	float mainScale;

public:
	AeroplaneBehavior::AeroplaneBehavior(float spawnX)
	{
		if (m_startX < 0)
		{
			m_direction = 1;
			parent->GetComponent<uth::Transform>.SetScale(verticalScaler * pmath::Vec2f(-0.35, 0.35));
		}
		else
		{
			m_direction = -1;
		}

		pathFlatnes = 55;
		sliding = 1;
	}


	void AeroplaneBehavior::pathFunc()
	{

		m_pos.x = m_direction * m_speed * m_time + m_startX;
		m_pos.y = -pow((m_pos.x) / pathFlatnes, 2) + m_minY;
		transform.SetPosition(m_pos);
		rotation();
		m_time += m_dt;
	}


	AeroplaneBehavior::~AeroplaneBehavior()
	{
	}

	void AeroplaneBehavior::update(float dt, float startx)
	{
		m_startX = startx;
		verticalScaler = (abs(parent->GetComponent<uth::Transform>.GetPosition().y) + 300) / 450;
		parent->GetComponent<uth::Transform>.SetScale(verticalScaler * pmath::Vec2f(-m_direction * 0.35, 0.35));

		m_dt = dt;
		pathFunc();
		rotation();
		explodeCheck();
		prevPos = parent->GetComponent<uth::Transform>.GetPosition();
	}

	void AeroplaneBehavior::explodeCheck()
	{
	}

	void AeroplaneBehavior::rotation()
	{
		pmath::Vec2f angVec = transform.GetPosition() - prevPos;

		if (m_direction * transform.GetPosition().x > 0)
		{
			sliding = 1.8;
		}
		else
		{
			sliding = 1;
		}

		angle = sliding * atanf(angVec.y / angVec.x);
		transform.SetRotation(pmath::radiansToDegrees(angle));
	}
	
};


#endif