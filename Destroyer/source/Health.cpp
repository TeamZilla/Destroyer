#include <Health.hpp>

using namespace uth;

Health::Health()
{
	auto healthTex = uthRS.LoadTexture("UI/life.png");
	healthTex->SetSmooth(true);
	AddComponent(new Sprite(healthTex));
	transform.SetOrigin(uth::Origin::TopLeft);

		
	m_Mhealth = 1;
	m_Chealth = m_Mhealth;
	m_damage = 0.99f;
	m_Chealth = m_Chealth - m_damage;


	if (m_Chealth == m_Mhealth)
	{
		GetComponent<Sprite>("Sprite")->SetColor(0, 1, 0, 1);
	}
	
	if (m_Chealth <= m_Mhealth)
	{
		n = m_Mhealth - m_Chealth;
		GetComponent<Sprite>("Sprite")->SetColor(0+n, 0.5f, 0, 1);

	}
	if(m_Chealth == 0)
	{
		m_damage = 0;
		GetComponent<Sprite>("Sprite")->SetColor(0, 0, 1, 1);

	}

}

void Health::Update(float dt)
{
	GameObject::Update(dt);
}

void Health::Draw()
{
	GameObject::Draw(uthEngine.GetWindow());
}
Health::~Health()
{
}
