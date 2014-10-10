#pragma once
#ifndef Tank_HPP
#define Tank_HPP

#include <UtH/UtHEngine.hpp>

class Tank : public uth::GameObject
{
private:
	pmath::Vec2 spawnPos;	  // Where tank is spawned
	pmath::Vec2 m_playerPos;  // Where player is located
	float m_dt;               // Deltatime
	float m_playerSpeed,      // Variable to determine how fast player goes
		  m_tankSpeed,	      // How fast tank will move
		  m_tankScale,	      // What are tank's scale
		  m_minRange,	      // How close will tank go to player at minimum
		  m_maxRange,         // How close will tank go to player at maximum
		  m_range;	          // How close will tank go to player for real
	bool m_isSideChecked;     // Check if side has been checked
	bool m_isTankOnRight;     // Where tank spawns, changes move direction
	uth::Window* m_window;    // Get reference of window

public:
	Tank(pmath::Vec2 pos);    // Constructor for spawning tank
	~Tank();

	void Update(float);
	void Draw();
	void Movement(float);     // Move tank left or right
	void WhichSideOfPlayer(); // Check which side of player tank is

};

#endif //Tank_HPP