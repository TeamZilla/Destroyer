#include <Road.hpp>
#include <UtH/Platform/JavaFunctions.hpp>
using namespace uth;

Road::Road(const int blocks)
{
	blockWidth = 8;
	AddChild(m_spriteBatch = new SpriteBatch());
	m_spriteBatch->SetTexture(uthRS.LoadTexture("backgrounds/asphalt_block.png"));
	leftMostX = -0.5*blocks*blockWidth;

	AddTag("Road");

	for (int i = 0; i < blocks; i++)
	{
		m_blocks.push_back(new RoadBlock(m_spriteBatch));
		m_blocks[i]->SetPosition(
			pmath::Vec2(leftMostX + i * blockWidth + 0.5*blockWidth,
			m_roadY));
		m_spriteBatch->AddSprite(m_blocks[i]);
	}

	m_shockLenght = 128;
	m_shockSpeed = 200;
	m_shockStartX = 40;
	m_shockHeight = 100;
	m_roadY = uthEngine.GetWindow().GetCamera().GetSize().y - 95;
	m_shockRange = 1600;
	isShock = false;
	m_shockHeightMatcher = 250;
	m_shockFriction = 0.5;
	m_shockStartSpeed = 1100;
	m_shockMinSpeed = 150;
	m_shock_x = 0;
	m_heightMod = 2.6;
	m_intensityScaler = 15;
	m_afterShakeTime = 0;
	m_delayCounter = 0;
	m_delay = 0.03;
}

void Road::Init(Player* asd, uth::PhysicsWorld* physworld)
{
	m_player = asd;
	hitBox = new GameObject();
	hitBox->AddComponent(new Sprite(pmath::Vec4(1, 0, 0, 0), pmath::Vec2(100, 100)));
	hitBox->transform.SetPosition(450, m_roadY + 250);
	hitBox->transform.SetScale(pmath::Vec2(2.2, 2.2));
	hitBox->AddComponent(new Rigidbody(*physworld));
	hitBox->GetComponent<Rigidbody>("Rigidbody")->SetAngle(45);
	hitBox->GetComponent<Rigidbody>("Rigidbody")->SetKinematic(true);
	hitBox->GetComponent<Rigidbody>("Rigidbody")->SetPhysicsGroup(-2);
	hitBox->AddTag("RoadCollider");
	AddChild(hitBox);

	for (int i = 0; i < m_blocks.size(); i++)
	{
		m_blocks[i]->SetPosition(leftMostX + i * blockWidth + 0.5*blockWidth, m_roadY);
	}


}


Road::~Road()
{
}

void Road::update(float dt)
{
	m_dt = dt;
	m_shock();

	if (isShock)
		hitBox->GetComponent<Rigidbody>("Rigidbody")->SetPhysicsGroup(-2);
	else
	{
		hitBox->GetComponent<Rigidbody>("Rigidbody")->SetPhysicsGroup(-3);
		hitBox->GetComponent<Rigidbody>("Rigidbody")->SetPosition(pmath::Vec2(m_shock_x, m_roadY + 500));
	}
}


void Road::InitShock()
{
	if (!isShock)
	{
		if (m_player->CheckIfGoingRight() == true)
		{
			m_shockDir = 1;
			m_shockSpeed = m_shockStartSpeed;
		}
		else
		{
			m_shockDir = -1;
			m_shockSpeed = m_shockStartSpeed;
		}

#ifdef UTH_SYSTEM_ANDROID
		javaFunc::Vibrate(1000);
#endif
	}


	isShock = true;
	m_shock();
}

void Road::m_shock()
{


	if (isShock)
	{

		m_randomFactor1 = Randomizer::GetFloat(2, 50);
		m_randomFactor2 = Randomizer::GetFloat(2, 50);
		m_randomFactor3 = Randomizer::GetFloat(2, 50);
		m_randomFactor4 = Randomizer::GetFloat(2, 50);

		m_intensityScaler2[0] = Randomizer::GetFloat(40, 50);
		m_intensityScaler2[1] = Randomizer::GetFloat(10, 20);
		m_intensityScaler2[2] = Randomizer::GetFloat(25, 40);
		m_intensityScaler2[3] = Randomizer::GetFloat(40, 65);



		if (m_shockMinSpeed < m_shockSpeed)
		{

			m_shockSpeed = m_shockStartSpeed - m_shockFriction * abs(m_shock_x);
		}

		else
		{
			m_shockSpeed = m_shockMinSpeed;
		}

		m_shock_x += m_shockDir * m_shockSpeed * m_dt;
		m_shockLenghtMatcher = 130000 / m_shock_x;
		m_shockHeightMatcher = std::abs(m_shock_x) / 8;


		for (int i = 0; i < m_blocks.size(); i++)
		{

			m_modulator = 0;
			for (int j = 0; j < 4; j++)
			{
				m_modulator += sin((m_blocks[i]->GetPosition().x) / m_intensityScaler2[j]);
			}

			if (m_shockLenght < std::abs(m_shock_x - m_blocks[i]->GetPosition().x))
			{
				for (int j = 0; j < 4; j++)
				{
					m_modulator += sin((m_blocks[i]->GetPosition().x) / m_intensityScaler2[j]);
					if (j == 1)
					{
						m_modulator *= m_heightMod;
					}
				}
			m_blocks[i]->SetPosition(m_blocks[i]->GetPosition().x, m_roadY + m_modulator);
			}
			else
			{
				for (int j = 0; j < 4; j++)
				{
					m_modulator += sin((m_blocks[i]->GetPosition().x) / m_intensityScaler2[j]);
					if (j == 1)
					{
						m_modulator *= m_heightMod;
					}
				}
				m_modulator *= m_heightMod;
				m_blocks[i]->SetPosition(
					m_blocks[i]->GetPosition().x,
					m_roadY +
					std::pow(m_shock_x - m_blocks[i]->GetPosition().x, 2) / abs(m_shockLenghtMatcher) -
					m_shockHeightMatcher + 0.5 * m_modulator
					);
			}
		}

	}

	hitBox->GetComponent<Rigidbody>("Rigidbody")->SetPosition(pmath::Vec2(m_shock_x, m_roadY + 50));

	if (abs(m_shock_x) >= m_shockRange)
	{
		// stop shockwave
		isShock = false;
		m_shockSpeed = m_shockStartSpeed;
		m_shock_x = m_shockStartX;
		m_player->m_allowShock = true;

		float smooth0 = (m_blocks[0]->GetPosition().y - m_roadY) / 1.5;
		float smooth1 = (m_blocks[1]->GetPosition().y - m_roadY) / 3;
		float smooth2 = (m_blocks[2]->GetPosition().y - m_roadY) / 4;
					    
		float smooth279 = (m_blocks[279]->GetPosition().y - m_roadY) / 4;
		float smooth280 = (m_blocks[280]->GetPosition().y - m_roadY) / 3;
		float smooth281 = (m_blocks[281]->GetPosition().y - m_roadY) / 1.5;

		m_blocks[0]->SetPosition(m_blocks[0]->GetPosition().x, m_blocks[0]->GetPosition().y - smooth0);
		m_blocks[1]->SetPosition(m_blocks[1]->GetPosition().x, m_blocks[1]->GetPosition().y - smooth1);
		m_blocks[2]->SetPosition(m_blocks[2]->GetPosition().x, m_blocks[2]->GetPosition().y - smooth2);

		m_blocks[0]->SetPosition(m_blocks[279]->GetPosition().x, m_blocks[279]->GetPosition().y - smooth279);
		m_blocks[1]->SetPosition(m_blocks[280]->GetPosition().x, m_blocks[280]->GetPosition().y - smooth280);
		m_blocks[2]->SetPosition(m_blocks[281]->GetPosition().x, m_blocks[281]->GetPosition().y - smooth281);

	}

	if (m_player->isGoingRight == true && isShock == false)
	{
		if (m_delay < m_delayCounter)
		{
			float temp = m_blocks[0]->GetPosition().y;

			for (int i = 1 /* 0 */; i < m_blocks.size(); i++) // use 0 if you dont want non-broken asphalt when walking forward else 1
			{
				m_blocks[i]->SetPosition(m_blocks[i]->GetPosition().x, m_blocks[(i + 1) % m_blocks.size()]->GetPosition().y);
				m_blocks[281]->SetPosition(m_blocks[i]->GetPosition().x, temp);
			}

			m_delayCounter = 0;

		}
	}
	if (m_player->isGoingRight == false && isShock == false)
	{
		if (m_delay < m_delayCounter)
		{
			float temp = m_blocks[281]->GetPosition().y;

			for (int j = 281; j > 1 /* 0 */ ; j--) // use 0 if you dont want non-broken asphalt when walking forward else 1
			{
				m_blocks[j]->SetPosition(m_blocks[j]->GetPosition().x, m_blocks[(j - 1)]->GetPosition().y);
			}
			m_blocks[0]->SetPosition(m_blocks[281]->GetPosition().x, temp);
			m_delayCounter = 0;

		}
	}

	m_delayCounter += m_dt;
}


