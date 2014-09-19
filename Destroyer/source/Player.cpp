#include <Player.hpp>

using namespace uth;

Player::Player()
{
	auto playerTexture = uthRS.LoadTexture("modzilla/modzilla_walk.png");
	playerTexture->SetSmooth(true);
	AddComponent(new AnimatedSprite(playerTexture, 4, 4, 1));
	transform.SetOrigin(uth::Origin::BottomCenter);
	transform.SetScale(0.75f);
	transform.SetPosition(
		uthEngine.GetWindow().GetSize().x / 2,
		uthEngine.GetWindow().GetSize().y / 2 + transform.GetSize().y/2);
	m_speed = 0;
	m_isGoingRight = true;
}
void Player::Update(float dt)
{
	GameObject::Update(dt);
}
void Player::ChangeDirection()
{
	transform.SetScale(transform.GetScale().x*-1, transform.GetScale().y);
}
void Player::Draw()
{
	GameObject::Draw(uthEngine.GetWindow());
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