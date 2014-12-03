#include "Missile.hpp"
#include <ExplosionEmitter.hpp>
using namespace uth;

Missile::Missile(pmath::Vec2f start, Player* player)
{
	auto missileTex = uthRS.LoadTexture("Enemies/Projectiles/copter_missile.png");
	missileTex->SetSmooth(true);
	AddComponent(new Sprite(missileTex));

	startPos = start;
	targPos = player->transform.GetPosition();
	mainDir = (targPos - startPos);
	altDir.x = mainDir.y;
	altDir.y = -mainDir.x;
	altDir.normalize();
	pathAlteration = Randomizer::GetFloat(-13.5, 13.5);
	time = 0;
	m_lenght = (targPos - startPos).length();
	curveDepth = 40;
	speed = 500 + Randomizer::GetFloat(-100, 100);
	waveFreq = 10;
	m_angle = 0;
	sliding = 0.7;
	isOrientated = 0;
	m_scale = 0.5f;
	m_isDestroyed = false;
	m_player = player;
	m_dmg = 4;

	transform.SetScale(m_scale);
}


void Missile::pathFunc()
{
	auto calc = pmath::Vec2f(
		
	startPos + 

	time * speed / m_lenght * mainDir +

	altDir * (sin(waveFreq * time + pathAlteration) + sin(waveFreq * time/ 2 + pathAlteration) + sin(waveFreq * time / 3 + pathAlteration) * curveDepth));

	transform.SetPosition(calc);

	time += m_dt;
}

Missile::Missile()
{
}

Missile::~Missile()
{
}

void Missile::update(float dt)
{
	m_dt = dt;
	pathFunc();
	rotation();
	explodeCheck();
	outOfBoundsCheck();
}

void Missile::explodeCheck()
{
}
void Missile::outOfBoundsCheck()
{
	if ((targPos - transform.GetPosition()).length() < 45 )
	{
		m_isDestroyed = true;
		Parent()->RemoveChild(this);
		ExplosionEmitter::Emit(transform.GetPosition());
		//TODO: Remove comments so it work, problem with player somehow...
		m_player->Hit(m_player->CheckIfGoingRight() == (mainDir.x < 0 ? true : false) ? m_dmg : m_dmg / 10);
	}
}


void Missile::rotation()
{
	pmath::Vec2f rotDir = transform.GetPosition() - prevPos;
	
	if (rotDir.x != 0)
	{
		m_angle = atanf(rotDir.y / rotDir.x);
		m_angle = sliding * 360 * m_angle / 3.14159;
	}
	else
	{
		m_angle = 0;
	}
	transform.SetRotation(m_angle);
	prevPos = transform.GetPosition();

	if (!isOrientated)
	{
		if (mainDir.x > 0)
		{
			transform.SetScale(-m_scale);
		}
	}
}

bool Missile::isOutOfBounds()
{
	return m_isDestroyed;
}