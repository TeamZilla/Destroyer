#include "Aeroplane.hpp"
using namespace uth;

Aeroplane::Aeroplane()
{
	auto aeroplaneTex = uthRS.LoadTexture("aeroplane.png");
	aeroplaneTex->SetSmooth(true);
	this->AddComponent(new Sprite(aeroplaneTex));
	m_time = 0;
	m_minY = 320;
	m_speed = 40;
	m_startX = -1000;

	if (m_startX < 0)
	{
		m_direction = 1;
	}
	else
	{
		m_direction = -1;
	}


	pathFlatnes = 50;


}


void Aeroplane::pathFunc()
{
	m_pos.x = m_direction * m_speed * m_time;
	m_pos.y = -pow((m_pos.x) / pathFlatnes, 2) + m_minY;



	transform.SetPosition(m_pos);
	std::cout << m_pos.x << ", " << m_pos.y << std::endl;
	m_time += m_direction * m_dt;
}


Aeroplane::~Aeroplane()
{
}

void Aeroplane::Update(float dt)
{
	m_dt = dt;
	pathFunc();
	rotation();
	explodeCheck();
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

}