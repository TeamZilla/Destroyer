#pragma once
#include <UtH/UtHEngine.hpp>

class FireBreath : public uth::GameObject
{
private:
	pmath::Vec2 m_targetPos;
	pmath::Vec2 m_fromPos;
	pmath::Vec2 m_dirVec;
	float m_sizeModifier;
	float m_speed;
	float m_time;

	pmath::Vec2 m_pathFunc();
	float m_sizeFunc();

public:
	FireBreath(pmath::Vec2, pmath::Vec2);
	void Init(uth::Layer*);
	void DeInit();
	void update(float dt) override;
};