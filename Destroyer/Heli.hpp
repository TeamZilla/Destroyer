#pragma once
#ifndef Player_HPP
#define Player_HPP

#include <UtH/UtHEngine.hpp>

class Heli : public uth::GameObject
{
public:
	Heli();
	Heli(pmath::Vec2f givenPos);
	Heli(float);
	~Heli();
	void hover();

	void navigate(pmath::Vec2f targ); // called when there's a new place to go to.
	

private:

	// Hovering
	float hoverSpeed;
	float speed;
	float hoverTime;
	float hoverScale_x; // separated scaling for x 
	float hoverScale_y; // separated scaling for y 
	float hoverScale;   // combined scaling
	pmath::Vec2f hoverDisplacement;
	
	
	//linear move
	void pilot(); // is the fuction that's called in each update loop.
	float acceleration;
	float pathLenght;
	void linearMove();
	pmath::Vec2f moveDir; // direction for linear move
	pmath::Vec2f curPos; // the current hovering origin. NOT SAME AS this->transfor.GetPos()
	pmath::Vec2f nextPos;
	pmath::Vec2f prevPos;

	//shooting
	bool isRight;
	bool isShooting;
	pmath::Vec2f shootingTarget;


};

#endif
