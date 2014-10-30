#pragma once
#ifndef RoadBlock_HPP
#define RoadBlock_HPP
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

#endif //Tank_HPP