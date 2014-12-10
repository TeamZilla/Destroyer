#include <Health.hpp>
#include <GameStats.hpp>

using namespace uth;

Health::Health()
{
	auto healthTex = uthRS.LoadTexture("UI/bar_bg.png");
	healthTex->SetSmooth(true);
	
	auto barTex = uthRS.LoadTexture("UI/bar.png");
	barTex->SetSmooth(true);
	
	m_bottom = new GameObject();
	m_bottom->AddComponent(new Sprite(healthTex, "bottom"));
	m_bottom->transform.SetOrigin(uth::Origin::TopLeft);
	AddChild(m_bottom);

	m_Red = new GameObject();
	m_Red->AddComponent(new Sprite(barTex,"Red"));
	m_Red->transform.SetOrigin(uth::Origin::TopLeft);
	AddChild(m_Red);
	

	m_Green = new GameObject();
	m_Green->AddComponent(new Sprite(barTex,"Green"));
	m_Green->transform.SetOrigin(uth::Origin::TopLeft);
	AddChild(m_Green);

	//cover for healthbar
	auto CoverTex = uthRS.LoadTexture("UI/life_bar.png");
	CoverTex->SetSmooth(true);

	m_cover = new GameObject();
	m_cover->AddComponent(new Sprite(CoverTex, "cover"));
	m_cover->transform.SetOrigin(uth::Origin::TopLeft);
	AddChild(m_cover);

	Statistics.player.hp = Statistics.player.maxHp;
	m_Mhealth = Statistics.player.maxHp;
	m_Chealth = Statistics.player.maxHp;

	AddTag("Health");

}

void Health::TakeDamage(float amount)
{
	Statistics.player.hp -= amount/100;
}

void Health::update(float dt)
{
	m_Chealth = Statistics.player.hp;

	auto& camera = uthEngine.GetWindow().GetCamera();

	 m_Green->transform.SetPosition(camera.GetPosition().x - camera.GetSize().x / 2 + 115,
		camera.GetPosition().y - camera.GetSize().y / 2 + 20) ;
	   m_Red->transform.SetPosition(camera.GetPosition().x - camera.GetSize().x / 2 + 115,
		camera.GetPosition().y - camera.GetSize().y / 2 + 20);
	m_bottom->transform.SetPosition(camera.GetPosition().x - camera.GetSize().x / 2 + 75,
		camera.GetPosition().y - camera.GetSize().y / 2 + 20);
	
	m_cover->transform.SetPosition(camera.GetPosition().x - camera.GetSize().x / 2 + 17,
		camera.GetPosition().y - camera.GetSize().y / 2 + 15);
	
	 m_Green->transform.SetRotation(camera.GetRotation());
	   m_Red->transform.SetRotation(camera.GetRotation());
	m_bottom->transform.SetRotation(camera.GetRotation());
	 m_cover->transform.SetRotation(camera.GetRotation());

	if (m_Chealth == m_Mhealth)
	{
		m_Red->GetComponent<Sprite>("Red")->SetColor(0.6f, 0, 0, 1);
		
		m = m_Mhealth;

	}
	
	if (m_Chealth <= m_Mhealth)
	{
		if (m >= m_Chealth && m > 0)
		{
			m_Red->transform.SetScale(m, 1);
			m = m - 0.002f;
		}

		n = (m_Mhealth - m_Chealth)/2;
		
		
		if (m_Chealth > 0)
		{
			m_Green->transform.SetScale(m_Chealth, 1);
		}
	}

	if(m_Chealth == 0)
	{
		
	}

}

Health::~Health()
{
}
