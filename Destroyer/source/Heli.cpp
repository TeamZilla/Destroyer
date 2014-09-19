#include "Heli.hpp"
using namespace uth;

Heli::Heli(pmath::Vec2f givenPos)
{
	m_curPos = givenPos;
	m_nextPos = m_curPos;
	m_prevPos = m_curPos;
	auto heliTex = uthRS.LoadTexture("heli.tga");
	heliTex->SetSmooth(true);
	this->AddComponent(new Sprite(heliTex));
	m_hoverTime = 0;
	m_hoverSpeed = 2;
	m_hoverScale = 70;
	m_hoverScale_x = 1;
	m_hoverScale_y = 1;
	m_hoverRatio = 100;
	isMoving = 0;
	m_linearSpeed = 50;
	m_missileCD_max = 0.7;
	m_missileCD_min = 0.2;
	m_dt = 0;
	m_acceleration = 0;
	m_pathLenght = 0;
	m_shootingTarget = pmath::Vec2f(500,0);
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
	if (uthInput.Common.Event() == CLICK)
	{
		SetNextPos(uthInput.Common.Position());

		std::cout << "(" << m_nextPos.x << " , " << m_nextPos.y << ")" << std::endl;
		std::cout << "LinearSpeed: "<<m_linearSpeed << std::endl;
		std::cout << "(" << m_moveDir.x << " , " << m_moveDir.y << ")" << std::endl;
	}
}

void Heli::Hover()
{
	m_hoverTime += m_hoverSpeed * m_dt;
	m_hoverRatio = std::abs(1 - m_acceleration);
	m_hoverDisplacement = pmath::Vec2f(m_hoverRatio * m_hoverScale * m_hoverScale_x * sin(m_hoverTime), m_hoverRatio * m_hoverScale * m_hoverScale_y * cos(m_hoverTime / 2));
	m_hoverTime += m_dt;}


void Heli::Navigate(pmath::Vec2f targ)
{
	if (m_nextPos != m_curPos)
	{
		m_prevPos = m_curPos;
		m_nextPos = targ;
		m_moveDir = (m_nextPos - m_prevPos);
		m_pathLenght = m_moveDir.length();
		m_moveDir = m_moveDir.normalize();
		isMoving = 1;
	}
}



void Heli::LinearMove()
{
	if (isMoving)
	{ 
	m_curPos = m_prevPos + m_acceleration * m_linearSpeed * m_moveDir;
	}
}


void Heli::Pilot()
{
	Navigate(m_nextPos);

	if (m_pathLenght != 0)
	{
		m_acceleration = std::powf(((m_nextPos - m_curPos).length() / m_pathLenght - 0.5), 2);
		isMoving = 1;
	}
	else
	{
		m_acceleration = 0;
		isMoving = 0;
	}

	Hover();

	// direction change
	transform.SetScale((m_shootingTarget.x - transform.GetPosition().x) / std::abs(m_shootingTarget.x - transform.GetPosition().x), 1);


	// linear move
	if (std::abs((m_curPos - m_nextPos).length()) > 1 && isMoving) // checks if transport is needed. 4 pixel accuracy.
	{
		if (std::abs((m_curPos - m_nextPos).length()) <= 1) // aprosimates position to exact place.
		{
			m_curPos = m_nextPos;
			isMoving = 0;
		}

		else
		{
			LinearMove();
		}
	}

	transform.SetPosition(m_curPos + m_hoverDisplacement); // sums up hover origin and hover displacement. Puts the object into the point.


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


void Heli::SetNextPos(pmath::Vec2f targ)
{
	m_nextPos = targ;
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

void Heli::SetLinearSpeed(float linear)
{
	m_linearSpeed = linear;
}

void Heli::SetHoverSpeed(float hover)
{
	m_hoverSpeed = hover;
}