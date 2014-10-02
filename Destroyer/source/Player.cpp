#include <Player.hpp>

using namespace uth;

Player::Player()
{
	auto playerTexture = uthRS.LoadTexture("modzilla/modzilla_sheet.png");
	playerTexture->SetSmooth(true);
	AddComponent(new AnimatedSprite(playerTexture,16,4,4));
	playerAnimation = GetComponent<AnimatedSprite>("AnimatedSprite");
	playerAnimation->ChangeAnimation(0, 4);
	transform.SetOrigin(uth::Origin::BottomCenter);
	transform.SetScale(0.75f);
	transform.SetPosition(
		uthEngine.GetWindow().GetSize().x / 2,
		uthEngine.GetWindow().GetSize().y / 2 + transform.GetSize().y/2);
	m_speed = 0;
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
	transform.SetScale(transform.GetScale().x*-1, transform.GetScale().y);
}
void Player::Draw()
{
	GameObject::Draw(uthEngine.GetWindow());
}
//Player jump
void Player::Jump()
{
	if (!m_isJumping && !m_isCrouching)
	{
		m_tempPos = transform.GetPosition();
		m_isJumping = true;
		m_jumpSpeed = m_jumpHeight;
		playerAnimation->ChangeAnimation(5, 4, 5, 3); //jumpanim
	}
}
void Player::Jumping()
{
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
		playerAnimation->ChangeAnimation(9, 4, 9, 4); //crouchanim
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