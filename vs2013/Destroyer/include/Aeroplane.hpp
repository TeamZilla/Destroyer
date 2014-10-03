#pragma once
#ifndef Aeroplane_HPP
#define Aeroplane_HPP

#include <UtH/UtHEngine.hpp>

class Aeroplane: public uth::GameObject
{
public:
	Aeroplane();
	~Aeroplane();

	void Update(float);
	void Draw();
	void Init();



private:
	float pathFlatnes; // ++ for flatnes
	float m_speed;
	void rotation();
	float m_time;
	float m_minY;
	float m_startX;
	int m_direction; // uses values 1 and -1 only.
	pmath::Vec2f m_pos;
	void pathFunc();
	void explodeCheck();
	float m_dt;

};

#endif
