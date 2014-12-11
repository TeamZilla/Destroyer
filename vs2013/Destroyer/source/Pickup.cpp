#include <Pickup.hpp>
using namespace uth;

Pickup::Pickup(int type)
{
	isDestroyed = false;
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

}
Pickup::~Pickup()
{

}

void Pickup::update(float dt)
{
	m_timer += dt;
	if (m_timer <= m_displayTime)
	{
		transform.Move(0, -(m_timer * 4));
		transform.Rotate(m_timer * 2);
	}
	else
	{
		isDestroyed = true;
	}

}