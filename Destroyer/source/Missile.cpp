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
	pathAlteration = Randomizer::GetFloat(-2, 2);
	m_dt = dt;
	time = 0;
	m_lenght = (targPos - startPos).length();
	curveDepth = 4;
	speed = 300;

}


void Missile::pathFunc()
{

	auto calc = pmath::Vec2f(
		
	startPos + 

	time * speed / m_lenght * mainDir +

	altDir * (sin(time + pathAlteration) + sin(time/ 2 + pathAlteration) + sin(time / 3 + pathAlteration) * curveDepth));

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
	explodeCheck();
}

void Missile::explodeCheck()
{
}

void Missile::Draw()
{
	GameObject::Draw(uthEngine.GetWindow());
}