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
    static uth::Sound*			m_expSound;

	static pmath::Vec2 SpawnPosition();

public:

	static void Init(uth::Layer* layer, uth::PhysicsWorld* physWorld, Player* player)
	{
		m_layer = layer;
		m_physicsWorld = physWorld;
		m_player = player;
		m_expSound = uthRS.LoadSound("Audio/Effects/Short_Explosion1.wav");
		m_expSound->SetVolume(10);
	}

	static std::shared_ptr<uth::GameObject> CreateTank();
	static std::shared_ptr<uth::GameObject> CreateSoldier();
	static std::shared_ptr<uth::GameObject> CreateAeroplane();
	static void CheckEnemies();

};

#endif