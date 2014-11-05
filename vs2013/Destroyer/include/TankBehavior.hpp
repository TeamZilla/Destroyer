#pragma once
#ifndef TankBehavior_HPP
#define TankBehavior_HPP

#include <UtH/UtHEngine.hpp>


class TankBehavior : public uth::Component
{
	float m_speed;
	uth::GameObject* m_player;
	uth::Rigidbody *m_rigidBody;

public:

	TankBehavior::TankBehavior(float speed, uth::GameObject* player) :
		m_speed(speed),
		m_player(player)
	{
		m_rigidBody = parent->GetComponent<uth::Rigidbody>();
	}
	TankBehavior::~TankBehavior()
	{

	}
	void Init() override { }
	void Draw(uth::RenderTarget& target) override { }
	void TankBehavior::Update(float dt)
	{
		//auto& rbody = *parent->GetComponent<uth::Rigidbody>();
		const auto& from = parent->transform.GetPosition();
		const auto& to = m_player->transform.GetPosition();

		auto& direction = (to - from).normalize();

		m_rigidBody->SetVelocity(direction * m_speed);

	}
	void TankBehavior::Hit()
	{
		m_rigidBody->ApplyImpulse(pmath::Vec2(uth::Randomizer::GetFloat(-20, 20),     //X direction
			-uth::Randomizer::GetFloat(50, 70)),				 //Y direction
			pmath::Vec2(uth::Randomizer::GetFloat(-25, 25), 0)); //offset
	}

};


#endif