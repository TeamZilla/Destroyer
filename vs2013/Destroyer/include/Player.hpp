#pragma once

#include <UtH/UtHEngine.hpp>
#include <Health.hpp>

class Player : public uth::GameObject
{
	float m_speed,
		m_jumpSpeed,
		m_jumpHeight,
		m_crouchTimer,
		m_jumpTimer,
		m_tailTimer,
		m_hurtTimer,
		m_dt;
	float m_maxSpeed, m_minSpeed, m_acceleration;
	float m_tailSpeed;
	bool m_isHurting, m_isSwiping, m_isDied;

	pmath::Vec2 m_tempPos;
	pmath::Vec4 m_walkAnim;
	pmath::Vec4 m_stompAnim;
	pmath::Vec4 m_jumpAnim;
	pmath::Vec4 m_tailAnim;

	uth::Rigidbody* m_rigidbody;
	uth::GameObject* m_tailBox;
	uth::GameObject* m_headBox;
	Health* m_health;
	void Acceleration();
	void Jumping();
	void Crouching();
	void Turning();
	void Hurting();
	void Dying();

public:
	Player(uth::PhysicsWorld*);
	~Player();

	bool m_isJumping, m_isCrouching, m_isTurning, m_isDoneDying;
	static bool isGoingRight;
	void init(uth::PhysicsWorld*, Health* hp);
	void update(float) override;
	void  ChangeDirection();
	void  Jump();
	void  Crouch();
	void  SwipeTail(float);
	void  Die();
	void  Hit(float dmg);
	float getSpeed();
	bool  CheckIfGoingRight();
	void  SetAnimation(pmath::Vec4 anim, bool loop = true);

	uth::AnimatedSprite* playerAnimation;
};