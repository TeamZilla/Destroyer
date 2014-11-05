#pragma once
#ifndef TankBehavior_HPP
#define TankBehavior_HPP

#include <UtH/UtHEngine.hpp>


class TankBehavior : public uth::Component
{
	float				m_speed;
	bool				m_isGoingLeft;
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

		//const auto& from = parent->transform.GetPosition();
		//const auto& to = m_player->transform.GetPosition();

		//m_direction = (to - from).normalize();

		//m_direction.x < 0 ? m_isGoingLeft = true : m_isGoingLeft = false;

		setTarget(m_player->transform.GetPosition());

		m_maxDistance = pmath::Vec2(
			uth::Randomizer::GetFloat(m_player->transform.GetPosition().x + 400,
									  m_player->transform.GetPosition().x + 600));
		m_minDistance = pmath::Vec2(
			uth::Randomizer::GetFloat(m_player->transform.GetPosition().x + 200,
									  m_player->transform.GetPosition().x + 300));

		m_target = m_maxDistance;

	}
	void Draw(uth::RenderTarget& target) override { }
	void TankBehavior::Update(float dt)
	{
		//auto& rbody = *parent->GetComponent<uth::Rigidbody>();
		//const auto& from = parent->transform.GetPosition();
		//const auto& to = m_player->transform.GetPosition();

		//auto& direction = (to - from).normalize();
		//if (m_rigidBody->GetPosition().x < -m_maxDistance.x && !m_isGoingLeft ||
		//	m_rigidBody->GetPosition().x > m_maxDistance.x && m_isGoingLeft)
		//{
		//	m_rigidBody->SetVelocity(
		//		pmath::Vec2(m_direction.x * m_speed,
		//		m_rigidBody->GetVelocity().y));
		//}
		if (m_rigidBody->GetPosition().x > m_maxDistance.x)
			m_rigidBody->ApplyForce(pmath::Vec2(m_direction.x * m_speed,0));
		else
			m_rigidBody->ApplyForce(pmath::Vec2(40,0));




		//else if (m_rigidBody->GetPosition().x < m_maxDistance.x && m_isGoingLeft ||
		//	m_rigidBody->GetPosition().x > -m_maxDistance.x && !m_isGoingLeft)
		//{
		//	m_rigidBody->SetVelocity(
		//		pmath::Vec2(m_direction.x * m_speed,
		//		m_rigidBody->GetVelocity().y));
		//}

	}
	
	void TankBehavior::Hit()
	{
		m_rigidBody->ApplyImpulse(
			pmath::Vec2(uth::Randomizer::GetFloat(-20, 20),     //X direction
			-uth::Randomizer::GetFloat(50, 70)),				 //Y direction
			pmath::Vec2(uth::Randomizer::GetFloat(-25, 25), 0)); //offset
	}

	void TankBehavior::setTarget(pmath::Vec2 to)
	{
		const auto& from = parent->transform.GetPosition();

		m_direction = (to - from).normalize();
		m_direction.x < 0 ? m_isGoingLeft = true : m_isGoingLeft = false;

	}

};


#endif