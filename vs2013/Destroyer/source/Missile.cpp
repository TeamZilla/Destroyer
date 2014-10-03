#include "Missile.hpp"
using namespace uth;

Missile::Missile(pmath::Vec2f start, pmath::Vec2f targ, float dt)
{
	auto missileTex = uthRS.LoadTexture("missile.png");
	missileTex->SetSmooth(true);
	this->AddComponent(new Sprite(missileTex));

	startPos = start;
	targPos = targ;
	mainDir = (targPos - startPos);
	altDir.x = mainDir.y;
	altDir.y = -mainDir.x;
	altDir.normalize();
	pathAlteration = Randomizer::GetFloat(-13.5, 13.5);
	m_dt = dt;
	time = 0;
	m_lenght = (targPos - startPos).length();
	curveDepth = 40;
	speed = 500 + Randomizer::GetFloat(-100, 100);
	waveFreq = 10;
	m_angle = 0;
	sliding = 0.7;
	isOrientated = 0;
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

void Missile::Update(float dt)
{
	pathFunc();
	rotation();
	explodeCheck();
}

void Missile::explodeCheck()
{
}

void Missile::Draw()
{
	GameObject::Draw(uthEngine.GetWindow());
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
			transform.SetScale(-1);
		}
	}
}