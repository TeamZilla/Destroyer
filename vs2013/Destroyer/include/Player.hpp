#pragma once
#ifndef Player_HPP
#define Player_HPP

#include <UtH/UtHEngine.hpp>

class Player : public uth::GameObject
{
private:

	float m_speed, m_jumpSpeed, m_jumpHeight, m_crouchTimer, m_dt;
	float m_maxSpeed, m_minSpeed, m_acceleration;
	bool m_isGoingRight;
	pmath::Vec2 m_tempPos;
	void Acceleration();

public:
	Player();
	~Player();

	void Update(float);
	void Draw();
	void ChangeDirection();
	void Jump();
	void Jumping();
	void Crouch();
	void Crouching();
	float getSpeed();
	bool CheckIfGoingRight();
	bool m_isJumping, m_isCrouching;

	uth::AnimatedSprite* playerAnimation;
};

#endif //Player_HPP