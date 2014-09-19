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

	void Update(float);
	void Draw();
	void Hover();						// the function that makes random-like movement
	void Pilot();						// is the fuction that's called in each update loop.
	

private:

	// Hovering
	float m_hoverm_linearSpeed;
	float m_hoverTime;					// howerDisplacement is a function of m_hoverTime
	float m_hoverScale_x;				// separated scaling for x 
	float m_hoverScale_y;				// separated scaling for y 
	float m_hoverScale;					// combined scaling
	pmath::Vec2f m_hoverDisplacement;		// the difference of curPos and exact position
	
	
	//linear move
	void m_navigate(pmath::Vec2f targ);	// called when there's a new place to go to.
	float m_acceleration;				// is a scalar that's manipulated in pilot()
	float m_linearSpeed;				// m_linearSpeed in linear movement
	float m_pathLenght;					// lenght of path. Changed only in m_navigate()
	void m_linearMove();					// calkulates linear progression between each update
	pmath::Vec2f moveDir;				// direction for linear move
	pmath::Vec2f curPos;				// the current hovering origin. NOT SAME AS this->transfor.GetPos()
	pmath::Vec2f nextPos;				// is the given target destination in m_navigate()
	pmath::Vec2f prevPos;				//the position at the moment new destination is given.
	float m_dt;
	//shooting
	bool isRight;
	bool isShooting;
	pmath::Vec2f shootingTarget;


};

#endif
