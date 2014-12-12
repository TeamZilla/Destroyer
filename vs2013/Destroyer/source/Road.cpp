#include <Road.hpp>
#include <UtH/Platform/JavaFunctions.hpp>
using namespace uth;

Road::Road(const int blocks)
{
	blockWidth = 10;
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

		m_shockLenght = 128;
		m_shockSpeed = 200;
		m_shockStartX = 40;
		m_shockHeight = 100;
		m_roadY = uthEngine.GetWindow().GetCamera().GetSize().y - 95;
		m_shockRange = 1600;
		isShock = false;
		m_shockHeightMatcher = 250;
		m_shockFriction = 0.5;
		m_shockStartSpeed = 1200;
		m_shockMinSpeed = 150;
		m_shock_x = 0;
	}
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
				if (m_shockLenght < std::abs(m_shock_x - m_blocks[i]->GetPosition().x))
				{
					m_blocks[i]->SetPosition(m_blocks[i]->GetPosition().x, m_roadY);
				}
				else
				{

					m_blocks[i]->SetPosition(

						m_blocks[i]->GetPosition().x,
						m_roadY +
						std::pow(m_shock_x - m_blocks[i]->GetPosition().x, 2) / abs(m_shockLenghtMatcher) -
						m_shockHeightMatcher
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
		}
	}


