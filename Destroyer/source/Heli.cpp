#include "Heli.hpp"
#include "Missile.hpp"
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
	m_shootDelay = 1;
	burstTimer = 0;
	m_missileClip = 6;
	m_missileClip = m_missileCount;
	m_shootingTarget = pmath::Vec2f(600, -100);

	m_missileRegenTimer = 0;
	m_missileRegenTime = 3;
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

		//std::cout << "(" << m_curPos.x << " , " << m_curPos.y << ")" << std::endl;

	}
	m_missile->Update(m_dt);
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

	m_acceleration = std::pow(((m_nextPos - m_curPos).length() / m_pathLenght ), 2); // <<<< make better acceleration function!
	m_curPos += m_acceleration * m_linearSpeed * m_moveDir;

	if (std::abs((m_curPos - m_nextPos).length()) < 2)
	{
		m_curPos = m_nextPos;
		isMoving = 0;
		m_acceleration = 0;
	}

}


void Heli::Pilot()
{
	if (!isMoving)
	{
		Navigate(m_nextPos);
	}
	if (isMoving)
	{
		LinearMove();
	}
	Hover();

	// direction change
	transform.SetScale((-m_shootingTarget.x + transform.GetPosition().x) / std::abs(m_shootingTarget.x - transform.GetPosition().x), 1);


	transform.SetPosition(m_curPos + m_hoverDisplacement); // sums up hover origin and hover displacement. Puts the object into the point.


	// SHOOTING:
	m_shoot();


}

void Heli::Draw()
{
	GameObject::Draw(uthEngine.GetWindow());
}


void Heli::SetNextPos(pmath::Vec2f targ)
{
	m_nextPos = targ;
	isMoving = 0;
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

void Heli::m_shoot()
{
	std::cout << "               Shoot" << std::endl;
	if (m_missileCount >= m_missileClip)
	{
		isShooting = 1;
		burst();
	}


	if (m_missileCount < m_missileClip)
	{
		if (m_missileRegenTimer >= m_missileRegenTime)
		{
			++m_missileCount;
			m_missileCooldownTimer = 0;
		}
		m_missileCooldownTimer += m_dt;
	}

}

void Heli::m_launch()
{
	m_missile = new Missile(transform.GetPosition(), m_shootingTarget, m_dt);
	std::cout << "       Launch" << std::endl;
}

void Heli::burst()
{
	std::cout << "burst" << std::endl;
	if (burstTimer <= 0)
	{
		isCool = 1;
		burstTimer = m_shootDelay;
	}

	if (isCool && isShooting)
	{
		m_launch();
		--m_missileClip;
	}

	if (m_missileCount == 0)
	{
		isShooting = 0;
	}

	burstTimer -= m_dt;
}