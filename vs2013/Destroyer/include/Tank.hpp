#pragma once
#ifndef Tank_HPP
#define Tank_HPP

#include <UtH/UtHEngine.hpp>

class Tank : public uth::GameObject
{
private:
	pmath::Vec2 spawnPos;
	float m_dt;
	float m_playerSpeed, m_tankSpeed;
	bool m_isTankOnRight;
	uth::Window* m_window;

public:
	Tank(pmath::Vec2 pos);
	~Tank();

	void Update(float);
	void Draw();
	void Movement();
	void WhichSideOfPlayer();

};

#endif //Tank_HPP