#include <Road.hpp>
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
		m_shockTime = 0;
		m_shockStartX = 0;
		m_shockHeight = 100;
		m_roadY = uthEngine.GetWindow().GetSize().y - 95;
		m_shockRange = 1200;
		isShock = false;
		m_shockHeightMatcher = 250;
		m_shockSupression = 1;
		m_shockFriction = 220;
		m_shockStartSpeed = 1100;

	}
}

void Road::Init(Player* asd, uth::PhysicsWorld* physworld)
{
	m_player = asd;
	hitBox = new GameObject();
	hitBox->AddComponent(new Sprite(pmath::Vec4(1, 0, 0, 0), pmath::Vec2(100, 100)));
	hitBox->transform.SetPosition(450, m_roadY + 250);
	hitBox->transform.SetScale(pmath::Vec2(2.2,2.2));
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
}


void Road::InitShock()
{
	if (!isShock)
	{
		if (m_player->CheckIfGoingRight() == true)
		{
			m_shockDir = 1;
		}
		else
		{
			m_shockDir = -1;
		}
	}

	isShock = true;
	m_shock();
}

void Road::m_shock()
{
	m_shockHeightMatcher = 62 * abs(m_shockTime) - 100;

	if (m_shockStartSpeed > m_shockFriction * m_shockTime)
	{
		m_shockSpeed = m_shockStartSpeed - m_shockFriction * abs(m_shockTime);
	}

	else
	{
		m_shockSpeed = 0;
	}
		
	if (isShock)
	{
		for (int i = 0; i < m_blocks.size(); i++)
		{


			if (m_shockLenght < std::abs(m_shockSpeed*m_shockTime - m_shockStartX - m_blocks[i]->GetPosition().x))
			{
				m_blocks[i]->SetPosition(m_blocks[i]->GetPosition().x, m_roadY);
			}
			else
			{

				m_blocks[i]->SetPosition(

					m_blocks[i]->GetPosition().x,

					m_roadY -
					m_shockHeight +
					std::pow((m_shockSpeed * m_shockTime - m_shockStartX) -
					m_blocks[i]->GetPosition().x, 2) / 300 * m_shockDir * m_shockTime -
					m_shockHeightMatcher

					);
			}
		}
		m_shockTime += m_shockDir * m_dt;
	}

	hitBox->GetComponent<Rigidbody>("Rigidbody")->SetPosition(pmath::Vec2(m_shockTime*m_shockSpeed, m_roadY+50));

	if (abs(m_shockTime*m_shockSpeed) >= m_shockRange)
	{
		// stop shockwave
		m_shockTime = 0;
		isShock = false;
		m_shockSupression = 1;
		m_shockSpeed= 300;
		m_shockTime = 0;
	}
}
