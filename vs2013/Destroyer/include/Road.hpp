#pragma once
#ifndef Road_HPP
#define Road_HPP
#include <vector>
#include <RoadBlock.hpp>
#include <UtH/UtHEngine.hpp>

class Road : public uth::GameObject
{
private:
	int m_blockNum;
	uth::SpriteBatch* m_spriteBatch;
	std::vector < RoadBlock*> m_blocks;
	float blockWidth;
	float leftMostX;



public:
	void Update(float);
	void Draw();

	Road(const int, uth::SpriteBatch*);
	~Road();
};

#endif //Tank_HPP