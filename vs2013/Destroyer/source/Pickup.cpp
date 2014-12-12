#include <Pickup.hpp>
using namespace uth;

Pickup::Pickup(int type)
{
	isDestroyed = false;
	m_smaller = false;
	m_timer = 0;

	m_displayTime = 1;

	std::string filepath;
	switch (type)
	{
	case 0:
		filepath = "Pickups/heart.png";
		break;
	case 1:
		filepath = "Pickups/star.png";
		break;
	default:
		break;
	}

	auto tex = uthRS.LoadTexture(filepath);
	AddComponent(new Sprite(tex));
	pickupType = type;
	m_Xdirection = Randomizer::GetFloat(-2, 2);

	transform.SetScale(pmath::Vec2(0, 0));
}
Pickup::~Pickup()
{

}

void Pickup::update(float dt)
{
	m_timer += dt;
	if (m_timer <= m_displayTime)
	{
		transform.Move(m_Xdirection, -5);
		transform.Rotate(m_timer * 2);
		//transform.SetScale(transform.GetScale() / m_timer);
	}
	else
	{
		isDestroyed = true;
	}

	//Set scale from 0 to 1 and back to 0
	if (!m_smaller)
	{
		if (transform.GetScale().x < 1)
			transform.SetScale(pmath::Vec2(transform.GetScale().x + dt * 2, transform.GetScale().y + dt * 2));
		else
			m_smaller = true;
	}
	else
	{
		if (transform.GetScale().x > 0)
			transform.SetScale(pmath::Vec2(transform.GetScale().x - dt * 2, transform.GetScale().y - dt * 2));
	}

}