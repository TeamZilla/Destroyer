#include <Background.hpp>
#include <Player.hpp>

using namespace uth;

Background::Background(float speed, float spawnY, float shakeMultiplier, bool first, const std::string& filePath)
	:m_speed(speed),
	m_spawnY(spawnY),
	m_shakeMultiplier(shakeMultiplier),
	m_first(first),
	Sprite(filePath)
{
}

Background::~Background()
{
}

void Background::Init()
{
	Sprite::Init();
	parent->transform.SetOrigin(uth::Origin::TopLeft);
	if (m_first)
		parent->transform.SetPosition(0, m_spawnY);
	else
		parent->transform.SetPosition(m_size.x, m_spawnY);
}

void Background::Update(float dt)
{
	parent->transform.Move(m_speed *2* (Player::isGoingRight ? -1 : 1) * dt, 0);

	if (parent->transform.GetPosition().x + m_size.x <
		uthEngine.GetWindow().GetCamera().GetPosition().x - uthEngine.GetWindow().GetSize().x / 2)
	{
		parent->transform.Move(m_size.x * 2,0);
	}
	else if (parent->transform.GetPosition().x >
		uthEngine.GetWindow().GetCamera().GetPosition().x + uthEngine.GetWindow().GetSize().x / 2)
	{
		parent->transform.Move(-m_size.x * 2, 0);
	}

	if (m_shakeTimer >= 0)
	{
		m_shakeTimer -= dt;
		float shake = m_shakeTimer*m_shakeMultiplier;
		auto amX = Randomizer::GetFloat(-shake, shake);
		auto amY = Randomizer::GetFloat(-shake, shake);

		parent->transform.SetOrigin({ -m_size.x / 2 + amX, -m_size.y / 2 + amY });		
	}
	else
	{
		parent->transform.SetOrigin(uth::Origin::TopLeft);
	}

}

void Background::Shake(float time)
{
	m_shakeTimer = time;
}