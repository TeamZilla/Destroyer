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



}

void Health::TakeDamage(float amount)
{
	m_Chealth -= amount/100;
}

void Health::Update(float dt)
{
	GameObject::Update(dt);
	transform.SetPosition(uthEngine.GetWindow().GetCamera().GetPosition().x - uthEngine.GetWindow().GetSize().x/2,
		uthEngine.GetWindow().GetCamera().GetPosition().y - uthEngine.GetWindow().GetSize().y / 2);
	if (m_Chealth == m_Mhealth)
	{
		GetComponent<Sprite>("Sprite")->SetColor(0, 1, 0, 1);
	}
	
	if (m_Chealth <= m_Mhealth)
	{
		n = m_Mhealth - m_Chealth;
		GetComponent<Sprite>("Sprite")->SetColor(0+n, 1-n, 0, 1);
		transform.SetScale(m_Chealth, 1);

	}
	if(m_Chealth == 0)
	{
		GetComponent<Sprite>("Sprite")->SetColor(0, 0, 1, 1);
	}
}

void Health::Draw()
{
	GameObject::Draw(uthEngine.GetWindow());
}
Health::~Health()
{
}
