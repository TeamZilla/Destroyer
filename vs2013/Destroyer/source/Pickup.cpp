#include <Pickup.hpp>
using namespace uth;

Pickup::Pickup(int type, pmath::Vec2 pos)
{
	m_type = type;
	isDestroyed = false;
	m_smaller = false;
	m_timer = 0;
	m_vertSpeed = 120;
	m_angleSpeed = 5;
	m_enlargement = 0.3;
	m_angleAcc = 1;

	m_displayTime = 2.5;

	std::string filepath;
	switch (type)
	{
	case 0:
		filepath = "Pickups/heart.png";
		break;
	case 1:
		filepath = "Pickups/star.png";
		break;
	case 2:
		filepath = "UI/boss.png";
		break;
	case 3:
		filepath = "UI/boss_victory.png";
		break;
	default:
		break;
	}

	auto tex = uthRS.LoadTexture(filepath);
	AddComponent(new Sprite(tex));
	pickupType = type;
	m_Xdirection = Randomizer::GetFloat(-2, 2);
	m_rotation = Randomizer::GetFloat(-4, 4);

	transform.SetScale(pmath::Vec2(0, 0));
	transform.SetOrigin(5);
	m_horizontal = 0;
	m_size = 1;
	m_pos = pos;
}
Pickup::~Pickup()
{

}

void Pickup::update(float dt)
{
	switch (m_type)
	{
	case 0:

		m_timer += dt;
		if (m_timer <= m_displayTime)
		{
			GetComponent<Sprite>()->SetColor(1, 1, 1, 1.5 - (m_timer / m_displayTime));
			transform.SetPosition(m_pos + pmath::Vec2(50 * sin(3 * m_timer), -100 * m_timer));
			transform.Rotate( m_timer);
			transform.SetScale(0.5 + 0.5 * abs(sin(3 * m_timer)));
		}
		else
		{
			isDestroyed = true;
		}
		break;

	case 1:
		m_timer += dt;
		if (m_timer <= m_displayTime)
		{
			m_angleAcc += m_timer / 190;
			m_horizontal = 10 * m_timer * sin(m_angleSpeed * m_timer * m_angleAcc) * (1 + m_angleAcc);
			m_size = 0.4 + 0.6 *m_timer * m_enlargement;
			m_scale = 1 + 0.3 * cos(m_angleSpeed * m_timer * m_angleAcc);
			GetComponent<Sprite>()->SetColor(1, 1, 1, 1.3 - (m_timer / m_displayTime));


			transform.SetPosition(m_pos + pmath::Vec2(m_horizontal, -m_timer * m_vertSpeed * m_angleAcc));
			transform.Rotate(m_timer * m_rotation);
			transform.SetScale(m_scale * m_size);
		}
		else
		{
			isDestroyed = true;
		}
		break;

	case 2:
	
		m_timer += dt;
			transform.SetRotation(360 *sin( 2* m_timer));
			transform.SetScale(abs(0.2 + 0.8 * sin(2 * m_timer)));

			if (m_timer > 4.05)
			{
				isDestroyed = true;
			}

		break;
	case 3:

		m_timer += dt;
		transform.SetRotation(360 * sin(2 * m_timer));
		transform.SetScale(abs(0.2 + 0.8 * sin(2 * m_timer)));

		if (m_timer > 4.05)
		{
			isDestroyed = true;
		}

		break;


	}
}