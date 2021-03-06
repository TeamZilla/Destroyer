#pragma once

#include <UtH/UtHEngine.hpp>
#include <Player.hpp>

class Missile : public uth::GameObject
{
	void pathFunc();
	void explodeCheck();
	void outOfBoundsCheck();
	bool isOrientated;
	bool m_isDestroyed;
	float time,
		m_dmg,
		m_lenght,
		speed,
		waveFreq,
		pathAlteration,
		curveDepth,
		m_dt,
		m_scale,
		m_angle,
		sliding; // sliding modifier (use 1 +- "small value")
	pmath::Vec2 startPos;
	pmath::Vec2 targPos;
	pmath::Vec2 mainDir;
	pmath::Vec2 altDir;
	pmath::Vec2 prevPos;
	Player* m_player;

	void rotation();

public:
	Missile();
	Missile(pmath::Vec2f,Player* player);
	~Missile();

	void update(float) override;
	//void Draw();
	void Init();
	bool isOutOfBounds();
};
