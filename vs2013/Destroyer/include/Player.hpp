#pragma once

#include <UtH/UtHEngine.hpp>

class Player : public uth::GameObject
{
private:

	float m_speed,
		m_jumpSpeed,
		m_jumpHeight,
		m_crouchTimer,
		m_jumpTimer,
		m_tailTimer,
		m_dt;
	float m_maxSpeed, m_minSpeed, m_acceleration;

	pmath::Vec2 m_tempPos;
	pmath::Vec4 m_walkAnim;
	pmath::Vec4 m_stompAnim;
	pmath::Vec4 m_jumpAnim;
	pmath::Vec4 m_tailAnim;

	uth::Rigidbody* m_rigidbody;
	uth::GameObject* m_bodyBox;
	uth::GameObject* m_headBox;
	void Acceleration();
	void Jumping();
	void Crouching();
	void Turning();

public:
	Player(uth::PhysicsWorld*);
	~Player();

	bool m_isJumping, m_isCrouching, m_isTurning;
	static bool isGoingRight;
	void init();
	void update(float) override;
	//void Draw();
	void  ChangeDirection();
	void  Jump();
	void  Crouch();
	float getSpeed();
	bool  CheckIfGoingRight();
	void  SetAnimation(pmath::Vec4 anim, bool loop = true);

	uth::AnimatedSprite* playerAnimation;
};