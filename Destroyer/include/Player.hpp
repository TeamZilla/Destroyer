#pragma once
#ifndef Player_HPP
#define Player_HPP

#include <UtH/UtHEngine.hpp>

class Player : public uth::GameObject
{
private:

	float m_speed;
	bool m_isGoingRight;

public:
	Player();
	~Player();

	void Update(float);
	void Draw();

	float getSpeed();
	bool CheckIfGoingRight();
};

#endif //Player_HPP