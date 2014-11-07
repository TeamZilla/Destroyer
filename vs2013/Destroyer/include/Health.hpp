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
	float m;
	uth::GameObject* m_Green;
	uth::GameObject* m_Red;
	

public:
	
	

	Health();
	~Health();

	void update(float) override;
	//void Draw();
	//damage calculation
	void TakeDamage(float amount);


};
#endif //Health_HPP