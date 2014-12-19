#include <Pickup.hpp>
using namespace uth;

Pickup::Pickup(int type)
{
	m_type = type;
	isDestroyed = false;
	m_smaller = false;
	m_timer = 0;

	m_displayTime = 1.8;

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
			transform.Move(m_Xdirection, -4 + m_timer);
			transform.Rotate(m_timer * m_rotation);
			//transform.SetScale(transform.GetScale() / m_timer);

	/*		m_height = m_timer;
			m_size = 0.5 + 0.5 * abs(cos(m_timer))
			m_horizontal = */
		}
		else
		{
			isDestroyed = true;
		}

		//Set scale from 0 to 1 and back to 0
		if (!m_smaller)
		{
			if (transform.GetScale().x < 1.3)
				transform.SetScale(pmath::Vec2(transform.GetScale().x + dt, transform.GetScale().y + dt));
			else
				m_smaller = true;
		}
		else
		{
			if (transform.GetScale().x > 0)
				transform.SetScale(pmath::Vec2(transform.GetScale().x - dt * 4, transform.GetScale().y - dt * 4));
		}
		break;
		break;






	case 1:
		m_timer += dt;
		if (m_timer <= m_displayTime)
		{
			transform.Move(m_Xdirection, -4 + m_timer);
			transform.Rotate(m_timer * m_rotation);
			//transform.SetScale(transform.GetScale() / m_timer);
		}
		else
		{
			isDestroyed = true;
		}

		//Set scale from 0 to 1 and back to 0
		if (!m_smaller)
		{
			if (transform.GetScale().x < 1.3)
				transform.SetScale(pmath::Vec2(transform.GetScale().x + dt, transform.GetScale().y + dt));
			else
				m_smaller = true;
		}
		else
		{
			if (transform.GetScale().x > 0)
				transform.SetScale(pmath::Vec2(transform.GetScale().x - dt * 4, transform.GetScale().y - dt * 4));
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