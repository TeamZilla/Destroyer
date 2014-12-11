#include <Pickup.hpp>
using namespace uth;

Pickup::Pickup(int type)
{
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


}