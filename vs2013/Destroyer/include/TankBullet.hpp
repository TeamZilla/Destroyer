#pragma once

#include <UtH/UtHEngine.hpp>
#include <Player.hpp>

class TankBullet : public uth::GameObject
{
	pmath::Vec2		m_startPos;
	pmath::Vec2		m_target;
	float			m_speed;
	pmath::Vec2		m_direction;
	Player*			m_player;
	void			hitCheck();
	float			m_dmg;

public:

	TankBullet(Player* player, pmath::Vec2 m_startPos);
	~TankBullet();
	void Init();
	void update(float m_dt);

};