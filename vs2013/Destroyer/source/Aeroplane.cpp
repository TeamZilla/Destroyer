#include "Aeroplane.hpp"
using namespace uth;

Aeroplane::Aeroplane(float spawnX)
{
	auto aeroplaneTex = uthRS.LoadTexture("aeroplane.png");
	aeroplaneTex->SetSmooth(true);
	this->AddComponent(new Sprite(aeroplaneTex));
	m_time = 0;
	m_minY = 320;
	m_speed = 800;
	m_startX = spawnX;
	mainScale = 0.25;
	verticalScaler = 1;
	transform.SetScale(mainScale);
	accelerate = 0;


	if (m_startX < 0)
	{
		m_direction = 1;
		transform.SetScale(verticalScaler * pmath::Vec2f(-0.35, 0.35));
	}
	else
	{
		m_direction = -1;
	}

	pathFlatnes = 55;
	sliding = 1;
}


void Aeroplane::pathFunc()
{

	m_pos.x = m_direction * m_speed * m_time + m_startX;
	m_pos.y = -pow((m_pos.x) / pathFlatnes, 2) + m_minY;
	transform.SetPosition(m_pos);
	rotation();
	m_time += m_dt;
}


Aeroplane::~Aeroplane()
{
}

void Aeroplane::Update(float dt)
{
	verticalScaler = (abs(transform.GetPosition().y)+300)/450;
	transform.SetScale(verticalScaler * pmath::Vec2f(-m_direction * 0.35, 0.35));

	m_dt = dt;
	pathFunc();
	rotation();
	explodeCheck();
	prevPos = transform.GetPosition();
}

void Aeroplane::explodeCheck()
{
}

void Aeroplane::Draw()
{
	GameObject::Draw(uthEngine.GetWindow());
}

void Aeroplane::rotation()
{
	pmath::Vec2f angVec = transform.GetPosition() - prevPos;

	if (m_direction * transform.GetPosition().x > 0)
	{
		sliding = 1.8;
	}
	else
	{
		sliding = 1;
	}

	angle = sliding * atanf(angVec.y / angVec.x);
	transform.SetRotation(pmath::radiansToDegrees(angle));
}