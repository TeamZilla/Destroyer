#pragma once

#include <UtH/UtHEngine.hpp>

class Soldier : public uth::GameObject
{
	pmath::Vec2 spawnPos;	  // Where Soldier is spawned
	pmath::Vec2 m_playerPos;  // Where player is located
	float m_dt;               // Deltatime
	float m_playerSpeed,      // Variable to determine how fast player goes
		  m_soldierSpeed,	  // How fast Soldier will move
		  m_soldierScale,	  // What are Soldier's scale
		  m_minRange,         // How close will Soldier go to player at minimum
		  m_maxRange,         // How close will Soldier go to player at maximum
		  m_range,            // How close will Soldier go to player for real
	      m_soldierTime;
	bool m_isSideChecked;     // Check if side has been checked
	bool m_isSoldierOnRight;     // Where Soldier spawns, changes move direction
	bool m_isSoldierDestroyed;   // Is Soldier destroyed
	bool m_isSoldierHit;         // Is Soldier been hit
	uth::Window* m_window;    // Get reference of window
	uth::PhysicsWorld* m_physWorld; // Make this for getting physics
	uth::Rigidbody* m_rigidBody;

public:
	Soldier(pmath::Vec2 pos, uth::PhysicsWorld*);    // Constructor for spawning tank
	~Soldier();

	void update(float) override;
	void Movement(float);     // Move Soldier left or right
	void Fly(float);
	bool isDestroyed();       // Check if Soldier is destroyed
	void Hit();
	void setPhysGroup();
	void WhichSideOfPlayer(); // Check which side of player Soldier is

};