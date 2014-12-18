#pragma once

#include <UtH/UtHEngine.hpp>
#include <Player.hpp>

class SoldierBehavior : public uth::Component
{
	float				m_speed;
	bool				m_isGoingLeft;
	bool				m_isStopped;
	bool				m_isDead;
	bool				m_isGoingToExp;
	bool				m_isGoingToFlat;
	bool				m_tailWhipped;
	float				m_attackTime;
	float				m_attackCounter;
	float				m_playerSpeed;

	Player*	m_player;
	uth::Rigidbody*		m_rigidBody;
	uth::Sound*			m_slashSound;
	pmath::Vec2			m_direction;
	float m_minDistance = 120;
	pmath::Vec2			m_target;
	pmath::Vec4			m_walkAnim;
	pmath::Vec4			m_attackAnim;
	pmath::Vec4			m_curAnim;
	float m_hitRange;
public:

	SoldierBehavior(float speed, Player* player) :
		m_speed(speed),
		m_player(player)
	{
		m_slashSound = uthRS.LoadSound("Audio/Effects/Sword.ogg");
		m_isGoingLeft;
		m_isStopped = false;
		m_isDead = false;
		m_isGoingToExp = false;
		m_isGoingToFlat = false;
		m_tailWhipped = false;
		m_attackTime = 1;
		m_attackCounter = 0;
		m_playerSpeed = 2;
		m_hitRange = uth::Randomizer::GetFloat(0, 100);

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

		m_attackAnim = pmath::Vec4(0, 6, 0, 12);
		m_walkAnim = pmath::Vec4(6, 6, 6, 12);

		if (m_rigidBody->GetPosition().x < 0)
		{
			m_isGoingLeft = false;
			auto& transf = parent->transform;
			transf.SetScale(-transf.GetScale().x, transf.GetScale().y);
		}
		else
		{
			m_isGoingLeft = true;
		}

		parent->GetComponent<uth::AnimatedSprite>()->ChangeAnimation(m_walkAnim.x,
															    m_walkAnim.y,
															    m_walkAnim.z,
															    m_walkAnim.w);
		m_curAnim = m_walkAnim;

	}

	void Update(float dt)
	{
		if (!m_isGoingToExp && !m_tailWhipped)
		{
			//Call movement update
			Movement();
			//Check is the animation correct
			if (m_curAnim != m_walkAnim && !m_isStopped)
			{
				parent->GetComponent<uth::AnimatedSprite>()->ChangeAnimation(m_walkAnim.x,
					m_walkAnim.y,
					m_walkAnim.z,
					m_walkAnim.w);
				m_curAnim = m_walkAnim;
			}
		}

		else if (m_isGoingToExp)
		{
			parent->GetComponent<uth::AnimatedSprite>()->ChangeAnimation(3, 1, 3, 1);
		}

		Attack(dt);
	}

	void Movement()
	{

		if (m_isGoingLeft && !m_isDead && m_rigidBody->GetPosition().y > 630 && m_minDistance + m_hitRange < abs(m_rigidBody->GetPosition().x))
		{
			m_isStopped = false;
			m_rigidBody->SetPosition(pmath::Vec2(m_rigidBody->GetPosition().x - m_speed - ((m_player->isGoingRight)*2 - 1) * m_playerSpeed, m_rigidBody->GetPosition().y));
			m_rigidBody->SetAngle(0);
		}
		else if (!m_isGoingLeft && !m_isDead && m_rigidBody->GetPosition().y > 630 && m_minDistance + m_hitRange < abs(m_rigidBody->GetPosition().x))
		{
			m_isStopped = false;
			m_rigidBody->SetAngle(0);
			m_rigidBody->SetPosition(pmath::Vec2(m_rigidBody->GetPosition().x + m_speed - ((m_player->isGoingRight) * 2 - 1) * m_playerSpeed, m_rigidBody->GetPosition().y));
		}
		else
		{
			m_isStopped = true;
			m_rigidBody->SetAngle(0);
		}

	}

	//	if (m_isGoingLeft && !m_isDead /*&& m_rigidBody->GetPosition().y > 630*/)
	//	{
	//		m_rigidBody->ApplyForce(pmath::Vec2(m_direction.x * m_speed, -10));
	//		if (m_rigidBody->GetPosition().x <= m_maxDistance.x)
	//		{
	//			m_rigidBody->SetVelocity(pmath::Vec2f(0, m_rigidBody->GetVelocity().y));
	//			m_rigidBody->SetAngle(0);
	//			m_isStopped = true;
	//		}
	//		else
	//		{
	//			m_isStopped = false;
	//		}
	//		if (m_rigidBody->GetPosition().x <= 0)
	//			Destroy();
	//	}

	//	if (!m_isGoingLeft && !m_isDead /*&& m_rigidBody->GetPosition().y > 630*/)
	//	{
	//		m_rigidBody->ApplyForce(pmath::Vec2(m_direction.x * m_speed, -10));
	//		if (m_rigidBody->GetPosition().x >= m_maxDistance.x)
	//		{
	//			
	//			m_rigidBody->SetVelocity(pmath::Vec2f(0, m_rigidBody->GetVelocity().y));
	//			m_rigidBody->SetAngle(0);
	//			m_isStopped = true;

	//		}
	//		else
	//		{
	//			m_isStopped = false;
	//		}
	//		if (m_rigidBody->GetPosition().x >= 0)
	//			Destroy();
	//	}

	//	m_rigidBody->SetAngle(0);
	//}
	
	void Hit()
	{
		m_rigidBody->ApplyImpulse(
			pmath::Vec2(uth::Randomizer::GetFloat(-1, 1),		 //X direction
			-uth::Randomizer::GetFloat(2, 4)),					 //Y direction
			pmath::Vec2(0, 0));									 //offset
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

	//void setTarget(pmath::Vec2 to)
	//{
	//	const auto& from = parent->transform.GetPosition();
	//	const auto& sc = parent->transform.GetScale();

	//	m_direction = (to - from).normalize();
	//	m_direction.x < 0 ? m_isGoingLeft = true : m_isGoingLeft = false;
	//	m_isGoingLeft ? parent->transform.SetScale(sc.x, sc.y) : parent->transform.SetScale(-sc.x, sc.y);
	//	m_isGoingLeft ? m_maxDistance = m_maxDistance : m_maxDistance = -m_maxDistance;

	//}

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
		//Slash player with sword
		if (m_isStopped && !m_isDead)
		{
			if (m_attackTime <= m_attackCounter)
			{
				m_slashSound->PlayEffect();
				m_player->Hit(0.5);
				m_attackCounter = 0;
			}

			//Check is the animation correct animation
			if (m_curAnim != m_attackAnim)
			{
				parent->GetComponent<uth::AnimatedSprite>()->ChangeAnimation(m_attackAnim.x,
					m_attackAnim.y,
					m_attackAnim.z,
					m_attackAnim.w);
				m_curAnim = m_attackAnim;
			}

			m_attackCounter += dt;
		}
	}
};