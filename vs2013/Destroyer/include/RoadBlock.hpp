#pragma once
#include <UtH/UtHEngine.hpp>

class RoadBlock : public uth::Transform
{
private:
	//uth::SpriteBatch* m_spriteBatch;
	float blockWidth;
	float leftMostX;

public:

	RoadBlock(uth::SpriteBatch*);
	~RoadBlock();
};