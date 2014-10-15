#include <Road.hpp>
using namespace uth;

Road::Road(const int blocks)
{
	m_spriteBatch = AddChild<SpriteBatch>().get();

	blockWidth = 16;
	leftMostX = -uthEngine.GetWindow().GetSize().x;

	//roadBlocks.reserve(blocks);
	for (int i = 0; i < blocks; i++)
	{
		//auto temp = new GameObject()
		m_blocks.push_back(new RoadBlock(m_spriteBatch));
		//m_blocks[i]->transform.SetOrigin(2);
		m_blocks[i]->transform.SetPosition(
			pmath::Vec2(leftMostX + i * blockWidth + 0.5*blockWidth,
			uthEngine.GetWindow().GetSize().y - m_blocks[i]->transform.GetSize().y));
		m_spriteBatch->AddSprite(&m_blocks[i]->transform);
	}
}


Road::~Road()
{
}

void Road::update(float dt)
{
}

//
//void Road::Draw()
//{
//	//GameObject::Draw(uthEngine.GetWindow());
//}