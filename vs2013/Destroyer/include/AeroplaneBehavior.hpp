#pragma once

#include <UtH/UtHEngine.hpp>
#include <ExplosionEmitter.hpp>

class AeroplaneBehavior : public uth::Component
{
	float pathFlatnes = 55; // ++ for flatnes
	float m_speed = 700;
	float m_time = 0;
	float m_minY = 290;
	float verticalScaler = 1;
	float mainScale = 0.35;
	float m_startX = 1200;
	float m_dt;
	float angle;
	float m_sliding = 1;
	int   m_direction; // uses values 1 and -1 only.
	bool  m_isDestroyed = false;
	pmath::Vec2 m_bombPos;
	pmath::Vec2 m_bombOffset;
	pmath::Vec2f m_pos;
	pmath::Vec2f prevPos;
	uth::Rigidbody*	m_rigidBody;
	uth::GameObject* pAtomBomb = new uth::GameObject();
	uth::GameObject* pRope = new uth::GameObject();
	uth::Layer* m_layer;

	//void explodeCheck();

public:

	bool isDestroyed()
	{
		return m_isDestroyed;
	}

	AeroplaneBehavior(uth::Layer* layer) :
		m_layer(layer)
	{

	}
	
	void Init() override
	{
		m_rigidBody = parent->GetComponent<uth::Rigidbody>();
		//m_rigidBody->SetKinematic(true);
		m_rigidBody->SetPhysicsGroup(3);
		
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

		
		auto bombTex = uthRS.LoadTexture("Enemies/Projectiles/AtomBomb.png");
		bombTex->SetSmooth(true);
		auto AtomBomb = new uth::Sprite(bombTex);
		pAtomBomb->AddComponent(AtomBomb);
		pAtomBomb->transform.SetScale(pmath::Vec2(-m_direction, 1));
		m_layer->AddChild(pAtomBomb);

		auto ropeTex = uthRS.LoadTexture("Enemies/Projectiles/rope.png");
		ropeTex->SetSmooth(true);
		auto Rope = new uth::Sprite(ropeTex);
		pRope->AddComponent(Rope);
		m_layer->AddChild(pRope);

	}

	~AeroplaneBehavior()
	{
	}

	void Update(float dt)
	{
		verticalScaler = (abs(m_rigidBody->GetPosition().y) + 300) / 450;
		parent->transform.SetScale(verticalScaler * pmath::Vec2f(-m_direction * 0.35,0.35));

		m_dt = dt;
		pathFunc();
		rotation();
		
		prevPos = m_rigidBody->GetPosition();
		if (prevPos.y <= -500)
		{
			m_isDestroyed = true;
		}

		m_bombOffset = pmath::Vec2(-m_direction * 400, 200);
		m_bombPos =  m_pos + m_bombOffset;
		pAtomBomb->transform.SetPosition(m_bombPos);

		pRope->transform.SetPosition(pAtomBomb->transform.GetPosition());
		pmath::Vec2 m_ropeDir = pAtomBomb->transform.GetPosition() - m_pos;

		float angle = pmath::radiansToDegrees(atan(sin(m_ropeDir.y) / m_ropeDir.x));
		pRope->transform.SetRotation(angle);
		pRope->transform.SetScale(pmath::Vec2(m_ropeDir.length() / pRope->transform.GetSize().x));
	}

	void pathFunc()
	{
		m_pos.x = m_direction * m_speed * m_time + m_startX;
		m_pos.y = -pow((m_pos.x) / pathFlatnes, 2) + m_minY;
		m_rigidBody->SetPosition(m_pos);

		rotation();
		m_time += m_dt;
	}

	void rotation()
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
	
	void Hit()
	{
		m_isDestroyed = true;
	}

};