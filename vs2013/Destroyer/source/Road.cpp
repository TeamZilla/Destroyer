#include <Road.hpp>
using namespace uth;

Road::Road(const int blocks)
{
	AddChild(m_spriteBatch = new SpriteBatch());
	m_spriteBatch->SetTexture(uthRS.LoadTexture("backgrounds/asphalt_block.png"));

	blockWidth = 16;
	leftMostX = -0.5*blocks*blockWidth;

	AddTag("Road");

	for (int i = 0; i < blocks; i++)
	{
		m_blocks.push_back(new RoadBlock(m_spriteBatch));
		m_blocks[i]->SetPosition(
			pmath::Vec2(leftMostX + i * blockWidth + 0.5*blockWidth,
			uthEngine.GetWindow().GetSize().y - m_blocks[i]->GetSize().y));
		m_spriteBatch->AddSprite(m_blocks[i]);


		m_shockLenght = 128;
		m_shockSpeed = 200;
		m_shockTime = 0;
		m_shockStartX = 0;
		m_shockHeight = 100;
		m_roadY = m_blocks[0]->transform.GetPosition().y;
		m_shockRange = 1200;
		isShock = false;
		m_shockHeightMatcher = 250;
		m_shockSupression = 1;

	}
}

void Road::Init(Player* asd)
{
	m_player = asd;
}


Road::~Road()
{
}

void Road::update(float dt)
{
	m_dt = dt;
}


void Road::Shock()
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

	m_shockHeightMatcher = 62 * abs(m_shockTime) - 100;
	m_shockSpeed = abs(300 + 100 * m_shockTime);

	std::cout << m_shockHeightMatcher << std::endl;

	//	std::cout << "shock" << std::endl;
	for (int i = 0; i < m_blocks.size(); i++)
	{


		if (m_shockLenght < std::abs(m_shockSpeed*m_shockTime - m_shockStartX - m_blocks[i]->transform.GetPosition().x))
		{
			m_blocks[i]->transform.SetPosition(m_blocks[i]->transform.GetPosition().x, m_roadY);
		}
		else
		{

				m_blocks[i]->transform.SetPosition(
					
				m_blocks[i]->transform.GetPosition().x, 
				
				m_roadY -
				m_shockHeight + std::pow((m_shockSpeed * m_shockTime - m_shockStartX) - m_blocks[i]->transform.GetPosition().x, 2) / 300 *m_shockDir * m_shockTime - m_shockHeightMatcher
				
				);
		}
	}

	m_shockTime += m_shockDir * m_dt;

	if (m_shockTime*m_shockSpeed >= m_shockRange)
	{
		// stop shockwave
		m_shockTime = 0;
		isShock = false;
		m_shockSupression = 1;
		m_shockSpeed= 300;
	}
}
