#pragma once

#include <vector>
#include <Player.hpp>
#include <RoadBlock.hpp>
#include <UtH/UtHEngine.hpp>

class Road : public uth::GameObject
{
	int m_blockNum;
	uth::SpriteBatch* m_spriteBatch;
	std::vector < RoadBlock*> m_blocks;
	float blockWidth;
	float leftMostX;

	// SHOCK
		float m_delayTimer,
		m_dt,
		m_shockLenght,
		m_shockSpeed,
		m_shockStartSpeed,
		m_shockMinSpeed,
		m_shockFriction,
		m_shockStartX,
		m_shockHeight,
		m_roadY,
		m_shockRange,
		m_shockHeightMatcher,
		m_shockLenghtMatcher,
		m_shock_x;
		
	Player *m_player;
	int m_shockDir;
	bool isShock;
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