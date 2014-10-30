#pragma once
#ifndef Road_HPP
#define Road_HPP
#include <vector>
#include <Player.hpp>
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

	// SHOCK
	float m_shockLenght;
	float m_shockSpeed;
	float m_shockTime;
	float m_shockStartX;
	float m_shockHeight;
	float m_roadY;
	float m_shockRange;
	float m_shockHeightMatcher;
	Player *m_player;
	float m_dt;
	int m_shockDir;
	bool isShock;
	float m_shockSupression;
	void m_shock();
	uth::GameObject* hitBox;



public:
	void Init(Player*, uth::PhysicsWorld* physworld);
	void update(float) override;
	void InitShock();
	//void Draw();

	Road(const int);
	~Road();
};

#endif //Tank_HPP