#pragma once
#ifndef AeroplaneBehavior_HPP
#define AeroplaneBehavior_HPP

#include <UtH/UtHEngine.hpp>


class AeroplaneBehavior : public uth::Component
{
private: 
	float pathFlatnes; // ++ for flatnes
	float m_speed;
	float m_time;
	float m_minY;
	float m_startX = 1200;
	int m_direction; // uses values 1 and -1 only.
	float m_dt;
	float accelerate;
	float angle;
	float sliding;
	float verticalScaler;
	float mainScale;

	pmath::Vec2f m_pos;
	pmath::Vec2f prevPos;
	uth::Rigidbody*	m_rigidBody;

	//void explodeCheck();

public:
	AeroplaneBehavior::AeroplaneBehavior()
	{

	}


	void AeroplaneBehavior::pathFunc()
	{
		m_pos.x = m_direction * m_speed * m_time + m_startX;
		m_pos.y = -pow((m_pos.x) / pathFlatnes, 2) + m_minY;
		m_rigidBody->SetPosition(m_pos);
		rotation();
		m_time += m_dt;
	}
	void Init() override
	{
		m_rigidBody = parent->GetComponent<uth::Rigidbody>();
		m_rigidBody->SetKinematic(true);
		m_rigidBody->SetPhysicsGroup(-3);
		m_direction = uth::Randomizer::GetInt(0, 1);
		if (m_direction == 0)
		{
			m_direction = -1;
			m_startX = m_direction * m_startX;
		}
		else
		{
			m_startX = m_startX * m_direction;
		}


		pathFlatnes = 55;
		sliding = 1;
	}

	AeroplaneBehavior::~AeroplaneBehavior()
	{
	}

	void AeroplaneBehavior::Update(float dt)
	{
		verticalScaler = (abs(m_rigidBody->GetPosition().y) + 300) / 450;
		parent->transform.SetScale(verticalScaler * pmath::Vec2f(-m_direction,1));

		m_dt = dt;
		pathFunc();
		rotation();
		//explodeCheck();
		prevPos = m_rigidBody->GetPosition();
	}


	void AeroplaneBehavior::rotation()
	{
		pmath::Vec2f angVec = parent->transform.GetPosition() - prevPos;

		if (m_direction * m_rigidBody->GetPosition().x > 0)
		{
			sliding = 1.8;
		}
		else
		{
			sliding = 1;
		}

		angle = sliding * atanf(angVec.y / angVec.x);
		parent->transform.SetRotation(pmath::radiansToDegrees(angle));
	}
	
};


#endif