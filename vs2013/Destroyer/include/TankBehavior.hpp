#pragma once

#include <UtH/UtHEngine.hpp>
#include <TankBullet.hpp>

class TankBehavior : public uth::Component
{
	float				m_speed;
	float				m_explodeTimer = 3;
	float				m_shootTimer = 0;
	bool				m_isGoingLeft;
	bool				m_isDead = false;
	bool				m_isGoingToExp = false;
	bool				m_isShooting = true;
	Player*				m_player;
	uth::Rigidbody*		m_rigidBody;
	uth::Layer*			m_layer;
	pmath::Vec2			m_direction;
	pmath::Vec2			m_maxDistance;
	pmath::Vec2			m_minDistance;
	pmath::Vec2			m_target;
	float				m_combatIntensity = 5;
	float				m_combatTimer = 0;

public:

	TankBehavior(float speed, Player* player, uth::Layer* layer) :
		m_speed(speed),
		m_player(player),
		m_layer(layer)
	{
		
	}
	~TankBehavior()
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

	void Update(float dt)
	{
		if (m_isGoingToExp)
			Exploding(dt);
		else
		{
			Movement();
			Combat(dt);
		}
	}

	void Movement()
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
		m_rigidBody->SetAngle(0);
	}
	
	void Exploding(float dt)
	{
		m_explodeTimer -= dt;
		//auto& col = parent->GetComponent<uth::Sprite>()->GetColor();
		//auto am = (dt * m_explodeTimer)/8;
		
		//parent->GetComponent<uth::Sprite>()->SetColor(col.r + am, col.g - am, col.b - am, col.a);
		
		//parent->transform.SetOrigin(pmath::Vec2(
		//	uth::Randomizer::GetFloat(-5 / m_explodeTimer/2, 5 / m_explodeTimer/2),
		//	uth::Randomizer::GetFloat(-5 / m_explodeTimer/2, 5 / m_explodeTimer/2)));

		//if (m_explodeTimer <= 0.5f)
		//	m_isDead = true;
	}

	void Hit()
	{
		m_rigidBody->ApplyImpulse(
			pmath::Vec2(uth::Randomizer::GetFloat(-10, 10),      //X direction
			-uth::Randomizer::GetFloat(80, 110)),				 //Y direction
			pmath::Vec2(uth::Randomizer::GetFloat(-35, 35), 0)); //offset
		m_rigidBody->SetPhysicsGroup(-2);
		m_isGoingToExp = true;
		parent->GetComponent<uth::AnimatedSprite>()->ChangeAnimation(2, 1, 2, 0, false);
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

	}

	void Combat(float dt)
	{

		if (m_combatIntensity <= m_combatTimer)
		{
			Shoot();
			m_combatTimer = 0;
		}
		m_combatTimer += dt;

		parent->GetComponent<uth::AnimatedSprite>()->ChangeAnimation(0, 1, 0, 0, false);
		if (m_combatIntensity/1.12f <= m_combatTimer)
			parent->GetComponent<uth::AnimatedSprite>()->ChangeAnimation(1, 1, 1, 0, false);
	}


	void Shoot()
	{
		m_layer->AddChild(new TankBullet(m_player, parent->transform.GetPosition()));
	}

	bool isDestroyed()
	{
		return m_isDead;
	}
	bool isExploding()
	{
		return m_isGoingToExp;
	}
};