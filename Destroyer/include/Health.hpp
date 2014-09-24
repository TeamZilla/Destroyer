#pragma once
#ifndef Health_HPP
#define Health_HPP

#include <UtH/UtHEngine.hpp>

class Health : public uth::GameObject
{
private:
	//max HP
	float m_Mhealth=0;
	//current HP
	float m_Chealth=0;
	
	float n;

public:
	
	

	Health();
	~Health();

	void Update(float);
	void Draw();
	//damage calculation
	void TakeDamage(float amount);


};
#endif //Health_HPP