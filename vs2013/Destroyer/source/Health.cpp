#include <Health.hpp>

using namespace uth;

Health::Health()
{
	auto healthTex = uthRS.LoadTexture("UI/life.png");
	healthTex->SetSmooth(true);

	m_Red = new GameObject();
	m_Red->AddComponent(new Sprite(healthTex,"Red"));
	m_Red->transform.SetOrigin(uth::Origin::TopLeft);
	AddChild(m_Red);
	/*
	AddChild(new Sprite(healthTex,"RedHP"));
	GetComponent<Sprite>("RedHP");*/

	m_Green = new GameObject();
	m_Green->AddComponent(new Sprite(healthTex,"Green"));
	m_Green->transform.SetOrigin(uth::Origin::TopLeft);
	AddChild(m_Green);

	m_Mhealth = 1;
	m_Chealth = m_Mhealth;



}

void Health::TakeDamage(float amount)
{
	m_Chealth -= amount/100;
}

void Health::update(float dt)
{
	transform.SetPosition(uthEngine.GetWindow().GetCamera().GetPosition().x - uthEngine.GetWindow().GetSize().x / 2,
		uthEngine.GetWindow().GetCamera().GetPosition().y - uthEngine.GetWindow().GetSize().y / 2);
	
	if (m_Chealth == m_Mhealth)
	{
		m_Red->GetComponent<Sprite>("Red")->SetColor(1, 0, 0, 1);
		m_Green->GetComponent<Sprite>("Green")->SetColor(0, 1, 0, 1);
		m = m_Mhealth;

	}
	
	if (m_Chealth <= m_Mhealth)
	{
		if (m >= m_Chealth)
		{
			m_Red->transform.SetScale(m, 1);
			m = m - 0.001f;
		}

		n = m_Mhealth - m_Chealth;
		m_Green->GetComponent<Sprite>("Green")->SetColor(0+n, 1-n, 0, 1);
		m_Green->transform.SetScale(m_Chealth, 1);
	}

	if(m_Chealth == 0)
	{
		m_Green->GetComponent<Sprite>("Green")->SetColor(0, 0, 1, 1);
	}
}

//void Health::Draw()
//{
//	GameObject::Draw(uthEngine.GetWindow());
//}
Health::~Health()
{
}
