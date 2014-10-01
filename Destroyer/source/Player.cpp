#include <Player.hpp>

using namespace uth;

Player::Player()
{
	auto playerTexture = uthRS.LoadTexture("modzilla/modzilla_sheet.png");
	playerTexture->SetSmooth(true);
	AddComponent(new AnimatedSprite(playerTexture,16,4,4));
	GetComponent<AnimatedSprite>("AnimatedSprite")->ChangeAnimation(0, 4);
	transform.SetOrigin(uth::Origin::BottomCenter);
	transform.SetScale(0.75f);
	transform.SetPosition(
		uthEngine.GetWindow().GetSize().x / 2,
		uthEngine.GetWindow().GetSize().y / 2 + transform.GetSize().y/2);
	m_speed = 0;
	m_jumpSpeed = 0;
	m_jumpHeight = 2;
	m_isGoingRight = true;
	m_isJumping = false;
}
void Player::Update(float dt)
{
	GameObject::Update(dt);
	m_dt = dt;
	if (m_isJumping)
	{
		Jumping();
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
	WriteLog("Jump!");
	if (!m_isJumping)
	{
		m_tempPos = transform.GetPosition();
		m_isJumping = true;
		m_jumpSpeed = m_jumpHeight;
		GetComponent<AnimatedSprite>("AnimatedSprite")->ChangeAnimation(5, 4, 5, 3, false);
	}
}
void Player::Jumping()
{
	WriteLog("HEHE\n");
	m_jumpSpeed -= m_dt*4;
	transform.Move(0, -m_jumpSpeed);
	if (transform.GetPosition().y >= m_tempPos.y)
	{
		transform.SetPosition(m_tempPos);
		GetComponent<AnimatedSprite>("AnimatedSprite")->ChangeAnimation(0, 4, 0, 5, true);
		m_isJumping = false;
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