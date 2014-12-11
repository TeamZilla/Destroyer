#include <Pickup.hpp>
using namespace uth;

Pickup::Pickup(int type)
{
	isDestroyed = false;
	m_timer = 0;

	m_displayTime = 2;

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
}
Pickup::~Pickup()
{

}

void Pickup::update(float dt)
{
	m_timer += dt;
	if (m_timer <= m_displayTime)
	{
		transform.Move(m_Xdirection, -(m_timer * 4));
		transform.Rotate(m_timer * 2);
		//transform.SetScale(transform.GetScale() / m_timer);
	}
	else
	{
		isDestroyed = true;
	}

}