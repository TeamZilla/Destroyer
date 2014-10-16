#include <Road.hpp>
using namespace uth;

Road::Road(const int blocks)
{
	AddChild(m_spriteBatch = new SpriteBatch());
	m_spriteBatch->SetTexture(uthRS.LoadTexture("backgrounds/asphalt_block.png"));

	blockWidth = 16;
	leftMostX = -uthEngine.GetWindow().GetSize().x;

	AddTag("Road");

	for (int i = 0; i < blocks; i++)
	{
		m_blocks.push_back(new RoadBlock(m_spriteBatch));
		m_blocks[i]->SetPosition(
			pmath::Vec2(leftMostX + i * blockWidth + 0.5*blockWidth,
			uthEngine.GetWindow().GetSize().y - m_blocks[i]->GetSize().y));
		m_spriteBatch->AddSprite(m_blocks[i]);
	}
}


Road::~Road()
{
}

void Road::update(float dt)
{
}
