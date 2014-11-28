#pragma once

#include <UtH/UtHEngine.hpp>

class Health : public uth::GameObject
{

	float m_Mhealth=0;	//max HP
	float m_Chealth=0;  //cur HP
	float n;
	float m;

	uth::GameObject* m_bottom;
	uth::GameObject* m_Green;
	uth::GameObject* m_Red;
	uth::GameObject* m_cover;
	

public:

	Health();
	~Health();

	void update(float) override;
	void TakeDamage(float amount);


};