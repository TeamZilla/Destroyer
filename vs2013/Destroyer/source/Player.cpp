#include <Player.hpp>

using namespace uth;

bool Player::isGoingRight = true;

Player::Player()
{
	auto playerTexture = uthRS.LoadTexture("modzilla/moz_sprites.png");
	playerTexture->SetSmooth(true);
	AddComponent(new AnimatedSprite(playerTexture,24,8,3));
	playerAnimation = GetComponent<AnimatedSprite>("AnimatedSprite");

	m_walkAnim = pmath::Vec4(16,8,16,10);
	m_stompAnim = pmath::Vec4(0,3,0,4);
	m_jumpAnim = pmath::Vec4(8,6,8,5);

	playerAnimation->ChangeAnimation(m_walkAnim.x,
									 m_walkAnim.y,
									 m_walkAnim.z,
									 m_walkAnim.w);
	transform.SetOrigin(uth::Origin::BottomCenter);
	transform.SetScale(1.5f);

	transform.SetPosition(pmath::Vec2f(0, uthEngine.GetWindow().GetSize().y - transform.GetSize().y/4));
	m_speed = 0;
	m_maxSpeed = 400;
	m_minSpeed = -400;
	m_acceleration = 750;
	m_jumpSpeed = 0;
	m_jumpHeight = 8;
	m_jumpTimer = 0;
	isGoingRight = true;
	m_isJumping = false;
	m_isCrouching = false;
}
void Player::update(float dt)
{
	m_dt = dt;
	Acceleration();
	if (m_isJumping)
	{
		Jumping();
	}
	if (m_isCrouching)
	{
		Crouching();
	}
}
void Player::ChangeDirection()
{
	//Flip player sprite to create illusion that player turns
	transform.SetScale(transform.GetScale().x*-1, transform.GetScale().y);
	//Speed reduced to minspeed
	m_speed = m_minSpeed;
	//Change bool value to check is player going right or not
	isGoingRight = !isGoingRight;
}
//void Player::Draw()
//{
//	GameObject::Draw(uthEngine.GetWindow());
//}
//Player jump
void Player::Jump()
{   //This is called once, changes variables to be ready to jump
	if (!m_isJumping && !m_isCrouching)
	{
		m_tempPos = transform.GetPosition();
		m_isJumping = true;
		m_jumpSpeed = m_jumpHeight;
		m_jumpTimer = 0.4;
		playerAnimation->ChangeAnimation(m_jumpAnim.x,
										 m_jumpAnim.y,
										 m_jumpAnim.z,
										 m_jumpAnim.w);
	}
}
void Player::Jumping()
{   //After 
	m_jumpTimer -= m_dt;
	if (m_jumpTimer <= 0)
	{
		m_jumpSpeed -= m_dt * 15;
		transform.Move(0, -m_jumpSpeed);
		if (transform.GetPosition().y >= m_tempPos.y)
		{
			transform.SetPosition(m_tempPos);
			playerAnimation->ChangeAnimation(m_walkAnim.x,
											 m_walkAnim.y,
											 m_walkAnim.z,
											 m_walkAnim.w);
			m_isJumping = false;
		}
	}
}
void Player::Crouch()
{
	if (!m_isCrouching && !m_isJumping)
	{
		m_tempPos = transform.GetPosition();
		m_isCrouching = true;
		m_jumpSpeed = 4;
		m_crouchTimer = 0;
		playerAnimation->ChangeAnimation(m_stompAnim.x,
										 m_stompAnim.y,
										 m_stompAnim.z,
										 m_stompAnim.w); //stompAnim
	}
}
void Player::Crouching()
{
	m_jumpSpeed -= m_dt * 20;
	m_crouchTimer += m_dt;
	transform.Move(0, -m_jumpSpeed);
	if (transform.GetPosition().y >= m_tempPos.y)
	{
		transform.SetPosition(m_tempPos);
	}
	if (m_crouchTimer >= 1)
	{
		playerAnimation->ChangeAnimation(m_walkAnim.x,
									     m_walkAnim.y,
									     m_walkAnim.z,
										 m_walkAnim.w);
		m_isCrouching = false;
	}

}
void Player::Acceleration()
{
	if (m_maxSpeed > m_speed)
	{
		m_speed += m_dt*m_acceleration;
	}
	else
	{
		m_speed = m_maxSpeed;
	}
}
// Get player speed
float Player::getSpeed()
{
	return m_speed;
}
// Get player direction
bool  Player::CheckIfGoingRight()
{
	return isGoingRight;
}
// Deconstructor
Player::~Player()
{
}