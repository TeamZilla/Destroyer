#pragma once

#include <UtH/UtHEngine.hpp>
#include <TankBullet.hpp>

class TankBehavior : public uth::Component
{
	float				m_speed;
	float				m_explodeTimer = 3;
	float				m_shootTimer = 3;
	bool				m_isGoingLeft;
	bool				m_isDead = false;
	bool				m_isGoingToExp = false;
	bool				m_isShooting = true;
	uth::GameObject*	m_player;
	uth::Rigidbody*		m_rigidBody;
	pmath::Vec2			m_direction;
	pmath::Vec2			m_maxDistance;
	pmath::Vec2			m_minDistance;
	pmath::Vec2			m_target;

public:

	TankBehavior::TankBehavior(float speed, uth::GameObject* player) :
		m_speed(speed),
		m_player(player)
	{
		
	}
	TankBehavior::~TankBehavior()
	{

	}
	void Init() override
	{
		m_rigidBody = parent->GetComponent<uth::Rigidbody>();
		m_rigidBody->SetPhysicsGroup(-3);
		m_rigidBody->SetFriction(0);

		m_maxDistance = pmath::Vec2(
			uth::Randomizer::GetFloat(m_player->transform.GetPosition().x + 400,
									  m_player->transform.GetPosition().x + 500), 300);
		m_minDistance = pmath::Vec2(
			uth::Randomizer::GetFloat(m_player->transform.GetPosition().x + 200,
									  m_player->transform.GetPosition().x + 300), 300);

		setTarget(m_player->transform.GetPosition());
		m_target = m_maxDistance;

	}

	void TankBehavior::Update(float dt)
	{
		if (m_isGoingToExp)
			Exploding(dt);
		else
			Movement();
	}

	void TankBehavior::Movement()
	{
		if (m_isGoingLeft)
		{
			if (m_rigidBody->GetPosition().x > m_target.x)
				m_rigidBody->ApplyForce(pmath::Vec2(m_direction.x * m_speed, 0));
			else
				m_rigidBody->ApplyForce(pmath::Vec2(-m_direction.x * 30, 0));
		}
		else
		{
			if (m_rigidBody->GetPosition().x < -m_target.x)
				m_rigidBody->ApplyForce(pmath::Vec2(m_direction.x * m_speed, 0));
			else
				m_rigidBody->ApplyForce(pmath::Vec2(-m_direction.x * 30, 0));
		}
	}
	
	void TankBehavior::Exploding(float dt)
	{
		m_explodeTimer -= dt;
		auto& col = parent->GetComponent<uth::Sprite>()->GetColor();
		auto am = (dt * m_explodeTimer)/8;
		
		parent->GetComponent<uth::Sprite>()->SetColor(col.r + am, col.g - am, col.b - am, col.a);
		
		parent->transform.SetOrigin(pmath::Vec2(
			uth::Randomizer::GetFloat(-5 / m_explodeTimer, 5 / m_explodeTimer),
			uth::Randomizer::GetFloat(-5 / m_explodeTimer, 5 / m_explodeTimer)));

		if (m_explodeTimer <= 0.5f)
			m_isDead = true;
	}

	void TankBehavior::Hit()
	{
		m_rigidBody->ApplyImpulse(
			pmath::Vec2(uth::Randomizer::GetFloat(-40, 40),      //X direction
			-uth::Randomizer::GetFloat(60, 80)),				 //Y direction
			pmath::Vec2(uth::Randomizer::GetFloat(-25, 25), 0)); //offset
		m_rigidBody->SetPhysicsGroup(-2);
		m_isGoingToExp = true;
	}
	void TankBehavior::Destroy()
	{
		m_isDead = true;
	}

	void TankBehavior::setTarget(pmath::Vec2 to)
	{
		const auto& from = parent->transform.GetPosition();
		const auto& sc = parent->transform.GetScale();

		m_direction = (to - from).normalize();
		m_direction.x < 0 ? m_isGoingLeft = true : m_isGoingLeft = false;
		m_isGoingLeft ? parent->transform.SetScale(sc.x, sc.y) : parent->transform.SetScale(-sc.x, sc.y);

	}

	void TankBehavior::Shoot()
	{

	}

	bool TankBehavior::isDestroyed()
	{
		return m_isDead;
	}
	bool TankBehavior::isExploding()
	{
		return m_isGoingToExp;
	}
};