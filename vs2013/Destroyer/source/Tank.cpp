#include <Tank.hpp>

using namespace uth;

Tank::Tank(pmath::Vec2 pos)
{
	m_window = &uthEngine.GetWindow();
	auto tankTexture = uthRS.LoadTexture("Enemies/tank.png");
	tankTexture->SetSmooth(true);
	AddComponent(new Sprite(tankTexture));
	transform.SetPosition(m_window->GetSize().x, m_window->GetSize().y / 2 + 200);
	transform.SetScale(0.5f);

	m_playerSpeed = 0;
	m_tankSpeed = 10;
	WhichSideOfPlayer();

}
Tank::~Tank()
{

}
void Tank::Update(float dt)
{
	GameObject::Update(dt);
	m_dt = dt;
}

void Tank::Movement()
{

}

void Tank::WhichSideOfPlayer()
{
	if (m_window->GetSize().x / 2 <= transform.GetPosition().x)
	{
		m_isTankOnRight = true;
	}
	else
	{
		m_isTankOnRight = false;
		transform.SetScale(-1, 1);
	}
}

void Tank::Draw()
{
	GameObject::Draw(uthEngine.GetWindow());
}