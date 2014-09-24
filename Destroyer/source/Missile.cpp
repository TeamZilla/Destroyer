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
	altDir.x = targPos.y;
	altDir.y = -targPos.x;
	pathAlteration = Randomizer::GetFloat(-2, 2);
	m_dt = dt;
	m_lenght = (targPos - startPos).length();
	curveDepth = 5;
}


void Missile::pathFunc()
{
	transform.SetPosition(startPos + m_dt / m_lenght * mainDir + altDir * (sin(m_dt + pathAlteration) + sin(m_dt / 2 + pathAlteration) + sin(m_dt/3 +pathAlteration) * curveDepth));
	std::cout << "Pos: " << transform.GetPosition().x << std::endl;
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
	Draw();
}

void Missile::explodeCheck()
{
}

void Missile::Draw()
{
	GameObject::Draw(uthEngine.GetWindow());
}