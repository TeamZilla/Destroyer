#pragma once

#include <UtH/UtHEngine.hpp>
#include <Player.hpp>

class SoldierBehavior : public uth::Component
{
	float				m_speed;
	bool				m_isGoingLeft;
	bool				m_isStopped = false;
	bool				m_isDead = false;
	bool				m_isGoingToExp = false;
	bool				m_isGoingToFlat = false;
	bool				m_tailWhipped = false;
	float				m_attackTime = 1;
	float				m_attackCounter = 0;

	Player*	m_player;
	uth::Rigidbody*		m_rigidBody;
	pmath::Vec2			m_direction;
	pmath::Vec2			m_maxDistance;
	pmath::Vec2			m_minDistance;
	pmath::Vec2			m_target;

public:

	SoldierBehavior(float speed, Player* player) :
		m_speed(speed),
		m_player(player)
	{
		
	}
	~SoldierBehavior()
	{

	}
	void Init() override
	{
		m_rigidBody = parent->GetComponent<uth::Rigidbody>();
		m_rigidBody->SetPhysicsGroup(-3);
		m_rigidBody->SetPhysicsCategory(uth::Physics::Category2);
		m_rigidBody->SetFriction(0);

		m_maxDistance = pmath::Vec2(m_player->transform.GetPosition().x + 
									uth::Randomizer::GetFloat(100,300));

		setTarget(m_player->transform.GetPosition());
		m_target = m_maxDistance;

	}

	void Update(float dt)
	{
		if (!m_isGoingToExp && !m_tailWhipped)
		{
			Movement();
		}

		else if (m_isGoingToExp)
		{
			//TODO: add hurt animation frame here
		}

		Attack(dt);
	}

	void Movement()
	{


		if (m_isGoingLeft && m_rigidBody->GetPosition().y > 630)
		{
			m_rigidBody->ApplyForce(pmath::Vec2(m_direction.x * m_speed, -10));
			if (m_rigidBody->GetPosition().x <= m_maxDistance.x)
			{
				m_rigidBody->SetVelocity(pmath::Vec2f(0, m_rigidBody->GetVelocity().y));
				m_rigidBody->SetAngle(0);
				m_isStopped = true;
			}
			else
			{
				m_isStopped = false;
			}
		}

		if (!m_isGoingLeft && m_rigidBody->GetPosition().y > 630)
		{
			m_rigidBody->ApplyForce(pmath::Vec2(m_direction.x * m_speed, -10));
			if (m_rigidBody->GetPosition().x >= m_maxDistance.x)
			{
				
				m_rigidBody->SetVelocity(pmath::Vec2f(0, m_rigidBody->GetVelocity().y));
				m_rigidBody->SetAngle(0);
				m_isStopped = true;

			}
			else
			{
				m_isStopped = false;
			}
		}

		m_rigidBody->SetAngle(0);
	}
	
	void Hit()
	{
		m_rigidBody->ApplyImpulse(
			pmath::Vec2(uth::Randomizer::GetFloat(-1, 1),     //X direction
			-uth::Randomizer::GetFloat(2, 4)),				  //Y direction
			pmath::Vec2(0, 0));								  //offset
	}
	void TailWhipHit()
	{
		m_rigidBody->ApplyImpulse(
			pmath::Vec2(uth::Randomizer::GetFloat(-10, 10),      //X direction
			-uth::Randomizer::GetFloat(20, 40)),				 //Y direction
			pmath::Vec2(uth::Randomizer::GetFloat(-25, 25), 0)); //offset
		m_rigidBody->SetPhysicsGroup(-2);
		m_isGoingToExp = true;
		m_isStopped = false;
	}
	void Destroy()
	{
		m_isDead = true;
	}

	void setTarget(pmath::Vec2 to)
	{
		const auto& from = parent->transform.GetPosition();
		const auto& sc = parent->transform.GetScale();

		m_direction = (to - from).normalize();
		m_direction.x < 0 ? m_isGoingLeft = true : m_isGoingLeft = false;
		m_isGoingLeft ? parent->transform.SetScale(sc.x, sc.y) : parent->transform.SetScale(-sc.x, sc.y);
		m_isGoingLeft ? m_maxDistance = m_maxDistance : m_maxDistance = -m_maxDistance;

	}

	void Shoot()
	{

	}

	bool isDestroyed()
	{
		return m_isDead;
	}
	bool isExploding()
	{
		return m_isGoingToExp;
	}

	void Attack(float dt)
	{
		if (m_isStopped)
		{
			if (m_attackTime <= m_attackCounter)
			{
				m_player->Hit(0.5);
				m_attackCounter = 0;
			}
			m_attackCounter += dt;
		}
	}
};