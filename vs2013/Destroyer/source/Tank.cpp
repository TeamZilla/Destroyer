#include <Tank.hpp>
#include <time.h>
using namespace uth;

Tank::Tank(pmath::Vec2 pos)
{
	m_tankScale = 0.5f;
	m_tankSpeed = 200;
	m_playerSpeed = 0;
	m_isSideChecked = false;
	m_maxRange = 400;
	m_minRange = 200;

	m_window = &uthEngine.GetWindow();
	auto tankTexture = uthRS.LoadTexture("Enemies/tank.png");
	tankTexture->SetSmooth(true);
	AddComponent(new Sprite(tankTexture));
	transform.SetPosition(pos.x, pos.y);
	transform.SetScale(m_tankScale);

	WhichSideOfPlayer();
	}
Tank::~Tank()
{

}
void Tank::Update(float dt)
{
	GameObject::Update(dt);
	Movement(dt);
	m_dt = dt;
}

void Tank::Movement(float dt)
{
	if (!m_isSideChecked)
	{
		m_range = Randomizer::GetInt(m_minRange, m_maxRange);
		m_isSideChecked = true;
	}

	if (m_playerPos.x + m_range <= transform.GetPosition().x)
	{
		transform.Move((dt*m_tankSpeed), 0);
	}

	transform.SetScale(Randomizer::GetFloat(m_tankScale - 0.02f, m_tankScale + 0.01f));
}

void Tank::WhichSideOfPlayer()
{
	m_playerPos = pmath::Vec2(m_window->GetSize().x / 2 <= transform.GetPosition().x, 0);

	if (m_playerPos.x <= transform.GetPosition().x)
	{
		m_isTankOnRight = true;
		transform.SetScale(transform.GetScale().x * -1, transform.GetScale().y);
		m_tankSpeed *= -1;
	}
	else
	{
		m_isTankOnRight = false;
	}

}

void Tank::Draw()
{
	GameObject::Draw(uthEngine.GetWindow());
}