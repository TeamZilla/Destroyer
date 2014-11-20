#pragma once

#include <UtH/UtHEngine.hpp>
#include <Player.hpp>

class TankBullet : public uth::GameObject
{
	pmath::Vec2		m_target;
	pmath::Vec2		m_speed;
	pmath::Vec2		m_direction;
	Player*			m_player;

public:

	TankBullet(Player* player);
	~TankBullet();
	void Init();
	void Update();

};