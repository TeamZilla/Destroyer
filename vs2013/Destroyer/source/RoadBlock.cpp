#include <RoadBlock.hpp>
using namespace uth;

RoadBlock::RoadBlock(uth::SpriteBatch* batch)
{
	m_spriteBatch = batch;
	m_spriteBatch->SetTexture(uthRS.LoadTexture("backgrounds/asphalt_block.png"));
}


RoadBlock::~RoadBlock()
{
}

void RoadBlock::Update(float dt)
{
}


void RoadBlock::Draw()
{
}