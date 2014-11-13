#pragma once

#include <UtH/UtHEngine.hpp>

class Missile : public uth::GameObject
{
	void pathFunc();
	void explodeCheck();
	void outOfBoundsCheck();
	bool isOrientated;
	bool m_isDestroyed;
	float time,
		m_lenght,
		speed,
		waveFreq,
		pathAlteration,
		curveDepth,
		m_dt,
		m_scale,
		m_angle,
		sliding; // sliding modifier (use 1 +- "small value")
	pmath::Vec2f startPos;
	pmath::Vec2f targPos;
	pmath::Vec2f m_pos;
	pmath::Vec2f mainDir;
	pmath::Vec2f altDir;
	pmath::Vec2f prevPos;

	void rotation();

public:
	Missile();
	Missile(pmath::Vec2f, pmath::Vec2f, float dt);
	~Missile();

	void update(float) override;
	//void Draw();
	void Init();
	bool isOutOfBounds();
};
