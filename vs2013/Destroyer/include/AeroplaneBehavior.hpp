#pragma once

#include <UtH/UtHEngine.hpp>
#include <ExplosionEmitter.hpp>


class AeroplaneBehavior : public uth::Component
{
	float pathFlatnes = 55; // ++ for flatnes
	float m_speed = 700;
	float m_time = 0;
	float m_minY = 320;
	float verticalScaler = 1;
	float mainScale = 0.35;
	float m_startX = 1200;
	float m_dt;
	float angle;
	float m_sliding = 1;
	int m_direction; // uses values 1 and -1 only.
	bool m_isDestroyed = false;

	pmath::Vec2f m_pos;
	pmath::Vec2f prevPos;
	uth::Rigidbody*	m_rigidBody;

	//void explodeCheck();

public:

	bool isDestroyed()
	{
		return m_isDestroyed;
	}

	AeroplaneBehavior::AeroplaneBehavior(){}
	
	void Init() override
	{
		m_rigidBody = parent->GetComponent<uth::Rigidbody>();
		m_rigidBody->SetKinematic(true);
		m_rigidBody->SetPhysicsGroup(-4);
		
		m_direction = uth::Randomizer::GetInt(0, 10);

		if (m_direction < 6)
		{
			m_direction = 1;
			m_startX = -m_startX;
		}
		else
		{
			m_direction = -1;
		}

	}

	AeroplaneBehavior::~AeroplaneBehavior()
	{
	}

	void AeroplaneBehavior::Update(float dt)
	{
		verticalScaler = (abs(m_rigidBody->GetPosition().y) + 300) / 450;
		parent->transform.SetScale(verticalScaler * pmath::Vec2f(-m_direction * 0.35,0.35));

		m_dt = dt;
		pathFunc();
		rotation();
		
		prevPos = m_rigidBody->GetPosition();
	}

	void AeroplaneBehavior::pathFunc()
	{
		m_pos.x = m_direction * m_speed * m_time + m_startX;
		m_pos.y = -pow((m_pos.x) / pathFlatnes, 2) + m_minY;
		m_rigidBody->SetPosition(m_pos);

		rotation();
		m_time += m_dt;
	}

	void AeroplaneBehavior::rotation()
	{
		pmath::Vec2f angVec = m_rigidBody->GetPosition() - prevPos;

		if (m_direction * m_rigidBody->GetPosition().x > 0)
		{
			m_sliding = 1.8;
		}
		else
		{
			m_sliding = 1;
		}

		angle = m_sliding * atanf(angVec.y / angVec.x);
		parent->transform.SetRotation(pmath::radiansToDegrees(angle));
	}
	
	void AeroplaneBehavior::Hit()
	{
		m_isDestroyed = true;
	}

};