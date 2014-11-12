#pragma once
#ifndef EnemyFactory_HPP
#define EnemyFactory_HPP
#include <UtH/UtHEngine.hpp>
#include <Player.hpp>

class EnemyFactory
{
	static uth::Layer*			m_layer;
	static uth::PhysicsWorld*	m_physicsWorld;
	static Player*				m_player;

	static pmath::Vec2 SpawnPosition();

public:

	static void Init(uth::Layer* layer, uth::PhysicsWorld* physWorld, Player* player)
	{
		m_layer = layer;
		m_physicsWorld = physWorld;
		m_player = player;
	}

	static std::shared_ptr<uth::GameObject> CreateTank();
	static std::shared_ptr<uth::GameObject> CreateSoldier();
	static void CheckEnemies();

};

#endif