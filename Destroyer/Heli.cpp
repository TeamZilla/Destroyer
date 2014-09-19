#include "Heli.hpp"
using namespace uth;

Heli::Heli(pmath::Vec2f givenPos)
{
	curPos = givenPos;
	auto heliTex = uthRS.LoadTexture("heli.png");
	heliTex->SetSmooth(true);
	this->AddComponent(new Sprite(heliTex));
	hoverTime = 0;
	hoverSpeed = 300;
	speed = 500;

}

Heli::Heli()
{
}

Heli::~Heli()
{
}

void Heli::hover()
{
	hoverTime += hoverSpeed * dt;
	hoverScale = 1 - acceleration;
	hoverDisplacement = pmath::Vec2f(hoverScale * hoverScale_x * sin(hoverTime), hoverScale * hoverScale_y * cos(hoverTime / 2));
	hoverTime += dt;
}


void Heli::navigate(pmath::Vec2f targ)
{
	prevPos = curPos;
	nextPos = targ;
	float pathLenght = std::abs((nextPos - curPos).length());
	pmath::Vec2f moveDir = (nextPos - curPos).normalize();
}



void Heli::linearMove()
{
	curPos = acceleration * speed * moveDir;
}


void Heli::pilot()
{
	acceleration = -std::powf(((nextPos - curPos).length() / pathLenght - 0.5), 2);
	hover();

	if (shootingTarget.x - this->transform.GetPosition().x < 0)
	{
		isRight = 1;
	}
	else
	{
		isRight = 0;
	}

	if (std::abs((curPos - nextPos).length()) > 1) // checks if transport is needed.
	{
		linearMove();
		if (std::abs((curPos - nextPos).length()) <= 1) // aprosimates position to exact place.
		{
			curPos = nextPos;
		}
	}

	this->transform.SetPosition(curPos + hoverDisplacement); // sums up hover origin and hover displacement. Puts the object into the point.
}

