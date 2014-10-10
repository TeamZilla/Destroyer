#pragma once
#ifndef Missile_HPP
#define Missile_HPP

#include <UtH/UtHEngine.hpp>

class Missile : public uth::GameObject
{
public:
	Missile();
	Missile(pmath::Vec2f, pmath::Vec2f, float dt);
	~Missile();

	void Update(float);
	void Draw();
	void Init();



private:
	void pathFunc();
	void explodeCheck();
	float time;
	float m_lenght;
	float speed;
	pmath::Vec2f startPos;
	pmath::Vec2f targPos;
	pmath::Vec2f m_pos;
	pmath::Vec2f mainDir;
	pmath::Vec2f altDir;
	float waveFreq;
	float pathAlteration;
	float curveDepth;
	float m_dt;
	float m_scale;

	void rotation();
	pmath::Vec2f prevPos;
	float m_angle;
	float sliding; // sliding modifier (use 1 +- "small value")
	bool isOrientated;

};

#endif
