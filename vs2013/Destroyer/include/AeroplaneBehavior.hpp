#pragma once

#include <UtH/UtHEngine.hpp>
#include <ExplosionEmitter.hpp>
#include <Player.hpp>
#include <GameStats.hpp>

class AeroplaneBehavior : public uth::Component
{
	float pathFlatnes = 55; // ++ for flatnes
	float m_speed = 700;
	float m_time = 0;
	float m_minY = 290;
	float verticalScaler = 1;
	float mainScale = 0.35;
	float m_startX = 1400;
	float m_dt;
	float angle;
	float m_sliding = 1;
	float m_bending = 0;
	float m_dmg = 60;
	int   m_direction; // uses values 1 and -1 only.
	bool  m_isDestroyed = false;
	bool isDetonated = false;
	Player* m_player;
	pmath::Vec2 m_bombPos;
	pmath::Vec2 m_bombOffset;
	pmath::Vec2f m_pos;
	pmath::Vec2f m_BombLastPos;
	pmath::Vec2f prevPos;
	uth::GameObject* pAtomBomb = new uth::GameObject();
	uth::GameObject* pRope = new uth::GameObject();
	uth::Layer* m_layer;

	//void explodeCheck();

public:

	uth::Rigidbody*	m_rigidBody;

	bool isDestroyed()
	{
		return m_isDestroyed;
	}

	AeroplaneBehavior(uth::Layer* layer, Player* player) :
		m_layer(layer), m_player(player)
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
		pAtomBomb->transform.SetOrigin(4);
		m_layer->AddChild(pAtomBomb);

		uth::Texture* ropeTex = uthRS.LoadTexture("Enemies/Projectiles/rope.png");
		ropeTex->SetSmooth(true);
		auto Rope = new uth::Sprite(ropeTex);
		pRope->AddComponent(Rope);
		pRope->transform.SetOrigin(9);
		m_layer->AddChild(pRope);

	}

	~AeroplaneBehavior()
	{
		if (pRope)
		m_layer->RemoveChild(pRope);
		if (pAtomBomb)
		m_layer->RemoveChild(pAtomBomb);
	}

	void Update(float dt)
	{
	
		
			verticalScaler = (abs(m_rigidBody->GetPosition().y) + 450) / 500;
	
	

		parent->transform.SetScale(verticalScaler * pmath::Vec2f(-m_direction * 0.35,0.35));				// Aeroplane scale
		pAtomBomb->transform.SetScale(pmath::Vec2(-m_direction * 2 * verticalScaler, 2 * verticalScaler));	// bomb scale
		m_dt = dt;
		pathFunc();
		rotation();
		
		prevPos = m_rigidBody->GetPosition();
		if (prevPos.y <= -800)
		{
			m_isDestroyed = true;
		}

		m_bending = 350 - m_pos.y;
		
	
		m_bombOffset = pmath::Vec2(-m_direction * 400 + m_direction * m_bending, 200);
		m_bombPos =  m_pos + m_bombOffset;
		pAtomBomb->transform.SetPosition(m_bombPos);

		if (m_direction * pAtomBomb->transform.GetPosition().x > -40 && !isDetonated)
		{
			// ExplosionEmitter::Emit(pAtomBomb->transform.GetPosition());
			m_player->Hit(m_player->CheckIfGoingRight() == (m_direction == 1 ? true : false) ? m_dmg / 3 : m_dmg);
			isDetonated = true;

		}
			
		if (m_player->m_isJumping && m_direction * m_pos.x > -60 && m_direction * m_pos.x < -40 && (m_player->isGoingRight * 2 - 1) * m_direction == -1)
		{
			m_isDestroyed = true;
			m_layer->RemoveChild(pRope);
			m_layer->RemoveChild(pAtomBomb);
		}

			////////////

		pRope->transform.SetPosition(pAtomBomb->transform.GetPosition());
		pmath::Vec2 ropeDir = pAtomBomb->transform.GetPosition() - m_pos;

		float angle = pmath::radiansToDegrees(atan2(ropeDir.y,ropeDir.x));

		pAtomBomb->transform.SetRotation(cos(m_pos.x / 170) * 10 + - m_direction * 15);

		std::cout << angle << std::endl;
		pRope->transform.SetRotation(angle);
		pRope->transform.ScaleToSize(ropeDir.length(), -m_direction * pRope->transform.GetSize().y);
	}

	void pathFunc()
	{
		m_pos.x = m_direction * m_speed * m_time + m_startX;
		m_pos.y = -pow((m_pos.x) / pathFlatnes, 2) + m_minY - 10;
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