#pragma once

#include <UtH/UtHEngine.hpp>

class Aeroplane: public uth::GameObject
{
public:
	Aeroplane(float);
	~Aeroplane();

	void update(float) override;
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
	pmath::Vec2f prevPos;
	float accelerate;
	float angle;
	float sliding;
	float verticalScaler;
	float mainScale;
};