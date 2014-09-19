#include "Heli.hpp"
using namespace uth;

Heli::Heli(pmath::Vec2f givenPos)
{
	curPos = givenPos;
	auto heliTex = uthRS.LoadTexture("heli.png");
	heliTex->SetSmooth(true);
	this->AddComponent(new Sprite(heliTex));
	m_hoverTime = 0;
	m_hoverm_linearSpeed = 300;
	m_linearSpeed = 500;
	m_missileCD_max = 0.7;
	m_missileCD_min = 0.2;
}

Heli::Heli()
{
}

Heli::~Heli()
{
}

void Heli::Update(float dt)
{
	GameObject::Update(dt);
	m_dt = dt;
	Pilot();
	Draw();
}

void Heli::Hover()
{
	m_hoverTime += m_hoverm_linearSpeed * m_dt;
	m_hoverScale = 1 - m_acceleration;
	m_hoverDisplacement = pmath::Vec2f(m_hoverScale * m_hoverScale_x * sin(m_hoverTime), m_hoverScale * m_hoverScale_y * cos(m_hoverTime / 2));
	m_hoverTime += m_dt;
}


void Heli::Navigate(pmath::Vec2f targ)
{
	prevPos = curPos;
	nextPos = targ;
	float m_pathLenght = std::abs((nextPos - curPos).length());
	pmath::Vec2f moveDir = (nextPos - curPos).normalize();
}



void Heli::LinearMove()
{
	curPos = m_acceleration * m_linearSpeed * moveDir;
}


void Heli::Pilot()
{
	m_acceleration = -std::powf(((nextPos - curPos).length() / m_pathLenght - 0.5), 2);
	Hover();

	if (m_shootingTarget.x - transform.GetPosition().x < 0)
	{
		transform.SetScale(-transform.GetScale().x, transform.GetScale().y);
		isRight = 1;
	}
	else
	{
		transform.SetScale(-transform.GetScale().x, transform.GetScale().y);
		isRight = 0;
	}

	if (std::abs((curPos - nextPos).length()) > 1) // checks if transport is needed.
	{
		LinearMove();
		if (std::abs((curPos - nextPos).length()) <= 1) // aprosimates position to exact place.
		{
			curPos = nextPos;
		}
	}

	this->transform.SetPosition(curPos + m_hoverDisplacement); // sums up hover origin and hover displacement. Puts the object into the point.


	// SHOOTING:

	if (isShooting == 1 && m_missileCooldownTimer <= 0)
	{
		////// call missile spawner here
		Randomizer::GetFloat(m_missileCD_min, m_missileCD_max);
	}
	--m_missileCooldownTimer;
}

void Heli::Draw()
{
	GameObject::Draw(uthEngine.GetWindow());
}


void Heli::SetTransport(pmath::Vec2f targ)
{
	nextPos = targ;
}

void Heli::SetShootTarget(pmath::Vec2f targ)
{
	m_shootingTarget = targ;
}

void Heli::SetMisCD_min(float min)
{
	m_missileCD_max = min;
}

void Heli::SetMisCD_max(float max)
{
	m_missileCD_max = max;
}