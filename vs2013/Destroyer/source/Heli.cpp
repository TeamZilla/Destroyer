#include "Heli.hpp"
#include "Missile.hpp"
using namespace uth;

Heli::Heli(pmath::Vec2f givenPos, Player* player)
{
	auto heliTex = uthRS.LoadTexture("Enemies/copteri.png");
	heliTex->SetSmooth(true);
	this->AddComponent(new AnimatedSprite(heliTex, 2, 2, 1, 12));
	m_hoverTime = 0;
	m_hoverSpeed = 2;
	m_hoverScale = pmath::Vec2f(100, 80);
	isMoving = 0;
	m_linearSpeedBase = 1;
	m_linearSpeed = 0.5;
	m_missileCD_max = 0.7;
	m_missileCD_min = 0.2;
	m_dt = 0;
	m_pathLenght = 0;
	m_shootDelay = 0.07;
	burstTimer = 3;
	m_missileClip = 8;
	m_missileCount = 0;
	m_shootingTarget = pmath::Vec2f(0,400);
	bonVoyageTimer = 0;
	m_missileRegenTimer = 0;
	m_missileRegenTime = 1;
	m_hoverMaxTime = 0; // randomized in pilot func.
	isCool = 0;
	m_player = player;
	m_health = 100;
	m_stabilizer = 6.5;
	m_angleMod = 18;
	m_currentAngle = 0;
	m_hoverMod = 1;
	m_curPos = givenPos - pmath::Vec2(1,0);
	Navigate(pmath::Vec2f(givenPos));
	isShooting = false;



	//m_heliSound = uthRS.LoadSound("Audio/Effects/helicopter.wav");
	//m_heliSound->Play();
	//m_heliSound->SetVolume(70);
	//m_heliSound->Loop(true);
}

void Heli::slerpToAngle()
{
	float tempAngle = m_currentAngle - m_targetAngle;
	if (abs(tempAngle) > 1)
	{
		m_currentAngle -= tempAngle / m_stabilizer;
	}
	else
	{
		m_currentAngle = m_targetAngle;
	}
}
Heli::Heli()
{
}

Heli::~Heli()
{
}

void Heli::update(float dt)
{
	m_dt = dt;
	if (GetComponent<Rigidbody>())
		Pilot();

	if (m_player->m_isJumping && transform.GetPosition().y > 175 && ((transform.GetPosition().x < 185 && transform.GetPosition().x > 80 && m_player->isGoingRight == true) || (transform.GetPosition().x > -185 && transform.GetPosition().x < -90 && m_player->isGoingRight == false)))
	{
		m_health = 0;
	}
		m_lastX = transform.GetPosition().x;

#ifdef UTH_SYSTEM_ANDROID
	if (uthInput.Touch.Motion() == TouchMotion::TAP)
	{
		SetNextPos(uthInput.Common.Position());
	}
#endif

}

bool Heli::isDestroyed()
{
	if (m_health < 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

void Heli::Hover()
{
		m_hoverMod = pow(cos(pmath::pi * (m_nextPos - m_curPos).length() / m_pathLenght),2); // acceleration and deacceleration. Use pows 2 * n only.
		m_hoverTime +=  m_hoverSpeed * m_dt;
		m_hoverDisplacement = m_hoverMod * pmath::Vec2f(m_hoverScale.x * sin(m_hoverTime), m_hoverScale.y * cos(m_hoverTime / 2));
}


void Heli::Navigate(pmath::Vec2f targ)
{
	if (m_nextPos != m_curPos)
	{
		m_prevPos = m_curPos;
		std::cout << m_prevPos << std::endl;
		m_nextPos = targ;
		std::cout << m_nextPos << std::endl << std::endl;
		m_moveDir = (m_nextPos - m_prevPos);
		m_pathLenght = m_moveDir.length();
		m_moveDir = m_moveDir.normalize();
		isMoving = 1;
	}

}



void Heli::LinearMove()
{
	m_linearSpeedBoost = (1 - m_hoverMod) * (m_nextPos - m_curPos).length() / 100;  // boost kicks in on long distances. max dist is 1400 so max boost is 1400/200 = 7. (1 - m_hoverMod) gives smooth acceleration.
	m_curPos +=  (m_linearSpeed + m_linearSpeedBoost) * m_moveDir;

	if (std::abs((m_curPos - m_nextPos).length()) < 2 )
	{
		m_curPos = m_nextPos;
		isMoving = 0;
		m_hoverMaxTime = Randomizer::GetFloat(4, 8); // sets time until next transition.
	}

}


void Heli::Pilot()
{
	if (bonVoyageTimer > m_hoverMaxTime && !isShooting)
	{
		auto voyage = pmath::Vec2f(Randomizer::GetFloat(-700, 700), Randomizer::GetFloat(150, 275));
		if ((transform.GetPosition() - voyage).length() > 200 && abs(voyage.x) > 400)
		{
			SetNextPos(voyage);
			bonVoyageTimer = 0;
		}
	}

	bonVoyageTimer += m_dt;


	if (!isMoving)
	{
		Navigate(m_nextPos);
	}

	if (isMoving)
	{
		LinearMove();
	}

	Hover();
	Torque();

	// direction change
	transform.SetScale((-m_shootingTarget.x + transform.GetPosition().x) / std::abs(m_shootingTarget.x - transform.GetPosition().x), 1);
	GetComponent<Rigidbody>()->SetPosition(m_curPos + m_hoverDisplacement);
	slerpToAngle();
	GetComponent<Rigidbody>()->SetAngle(m_currentAngle);
	GetComponent<Rigidbody>()->SetPhysicsGroup(3);
	//transform.SetPosition(m_curPos + m_hoverDisplacement); // sums up hover origin and hover displacement. Puts the object into the point.


	// SHOOTING:
	m_reload();
	m_shooter();


	//Sound volume, sound volume increases when helicopter gets closer
	//TODO::COMPLETE THIS
	//auto distance = pmath::Vec2(transform.GetPosition().x, pmath::Vec2(0, 400).x).length();
	//WriteLog("%f", distance);
	//if (distance >= 100.0f)
	//	distance = 100.0f;
	//else if (distance <= 5.0f)
	//	distance = 5.0f;
	//m_heliSound->SetVolume(100/(distance/10));
}



void Heli::Torque()
{
	m_targetAngle = -m_angleMod * sin(0.5*(m_lastX - transform.GetPosition().x));
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


void Heli::m_shooter()
{
	m_reload();
	burst();
	
}


void Heli::m_reload()
{
	if (!isShooting)
	{
		if (m_missileRegenTimer >= m_missileRegenTime)
		{
			++m_missileCount;
			m_missileRegenTimer = 0;
		}
		m_missileRegenTimer += m_dt;

		if (m_missileCount >= m_missileClip)
		{
			isShooting = 1;
		}
	}
}


void Heli::m_launch()
{
	if ((transform.GetPosition() - m_shootingTarget).length() < 1000)
	{
		Parent()->AddChild(new Missile(transform.GetPosition(), m_player));
	}
}


void Heli::burst()
{
	if (burstTimer <= 0)
	{
		isCool = 1;
		burstTimer = m_shootDelay;
	}

	burstTimer -= m_dt;

	if (isCool && isShooting && !isMoving)
	{
		m_launch();
		--m_missileCount;
		isCool = 0;

		if (m_missileCount <= 0)
		{
			isShooting = 0;
		}
	}

}

void Heli::takeDamage(int amount)
{
	m_health -= amount;
}