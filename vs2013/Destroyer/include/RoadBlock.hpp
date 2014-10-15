#pragma once
#ifndef RoadBlock_HPP
#define RoadBlock_HPP
#include <UtH/UtHEngine.hpp>

class RoadBlock : public uth::GameObject
{
private:
	uth::SpriteBatch* m_spriteBatch;
	float blockWidth;
	float leftMostX;



public:
	void Update(float);
	void Draw();

	RoadBlock(uth::SpriteBatch*);
	~RoadBlock();
};

#endif //Tank_HPP