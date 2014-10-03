#include <Player.hpp>

using namespace uth;

Player::Player()
{
	auto playerTexture = uthRS.LoadTexture("modzilla/modzilla_sprites02.png");
	playerTexture->SetSmooth(true);
	AddComponent(new AnimatedSprite(playerTexture,24,6,4));
	playerAnimation = GetComponent<AnimatedSprite>("AnimatedSprite");
	playerAnimation->ChangeAnimation(0, 4);
	transform.SetOrigin(uth::Origin::BottomCenter);
	transform.SetScale(0.75f);
	transform.SetPosition(
		uthEngine.GetWindow().GetSize().x / 2,
		uthEngine.GetWindow().GetSize().y / 2 + transform.GetSize().y/2);
	m_speed = 0;
	m_maxSpeed = 400;
	m_minSpeed = -400;
	m_acceleration = 750;
	m_jumpSpeed = 0;
	m_jumpHeight = 8;
	m_isGoingRight = true;
	m_isJumping = false;
	m_isCrouching = false;
}
void Player::Update(float dt)
{
	GameObject::Update(dt);
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
	m_isGoingRight = !m_isGoingRight;
}
void Player::Draw()
{
	GameObject::Draw(uthEngine.GetWindow());
}
//Player jump
void Player::Jump()
{   //This is called once, changes variables to be ready to jump
	if (!m_isJumping && !m_isCrouching)
	{
		m_tempPos = transform.GetPosition();
		m_isJumping = true;
		m_jumpSpeed = m_jumpHeight;
		playerAnimation->ChangeAnimation(17, 6, 17, 8); //jumpanim
	}
}
void Player::Jumping()
{   //After 
	m_jumpSpeed -= m_dt*15;
	transform.Move(0, -m_jumpSpeed);
	if (transform.GetPosition().y >= m_tempPos.y)
	{
		transform.SetPosition(m_tempPos);
		playerAnimation->ChangeAnimation(0, 4, 0, 5, true); //walkanim
		m_isJumping = false;
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
		playerAnimation->ChangeAnimation(6, 4, 6, 4); //crouchanim
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
		playerAnimation->ChangeAnimation(0, 4, 0, 5, true); //walkanim
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
	return m_isGoingRight;
}
// Deconstructor
Player::~Player()
{
}