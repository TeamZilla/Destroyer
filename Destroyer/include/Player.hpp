#pragma once
#ifndef Player_HPP
#define Player_HPP

#include <UtH/UtHEngine.hpp>

class Player : public uth::GameObject
{
private:

	float m_speed, m_jumpSpeed, m_jumpHeight, m_crouchTimer, m_dt;
	bool m_isGoingRight, m_isJumping, m_isCrouching;
	pmath::Vec2 m_tempPos;

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

	uth::AnimatedSprite* playerAnimation;
};

#endif //Player_HPP