#pragma once

#include <UtH/UtHEngine.hpp>
#include <Player.hpp>

class EnemyFactory
{
	static uth::Layer*			m_layer;
	static uth::PhysicsWorld*	m_physicsWorld;
	static Player*				m_player;
	static uth::Sound*			m_expSound;
	static uth::Sound*			m_hpSound;
	static uth::Sound*			m_starSound;

	static pmath::Vec2 SpawnPosition();

	static void m_tankSpawn(float dt);
	static void m_soldierSpawn(float dt);
	static void m_aeroplaneSpawn(float dt);
	static void m_heliSpawn(float dt);

	static float m_aeroplaneSpawnCooldown;
	static float m_aeroplaneSpawnTimer;
	static float m_tankSpawnCooldown;
	static float m_tankSpawnTimer;
	static float m_soldierSpawnCooldown;
	static float m_soldierSpawnTimer;
	static float m_heliSpawnCooldown;
	static float m_heliSpawnTimer;
	static float m_timeCounter;


public:

	static void Init(uth::Layer* layer, uth::PhysicsWorld* physWorld, Player* player)
	{
		m_layer = layer;
		m_physicsWorld = physWorld;
		m_player = player;
		m_expSound =  uthRS.LoadSound("Audio/Effects/Short_Explosion1.wav");
		m_hpSound =   uthRS.LoadSound("Audio/Effects/Heart_pickup.wav");
		m_starSound = uthRS.LoadSound("Audio/Effects/Star_pickup.wav");
		//m_expSound->SetVolume(50);
	}
	static void Update(float dt);

	static std::shared_ptr<uth::GameObject> CreateTank();
	static std::shared_ptr<uth::GameObject> CreateSoldier();
	static std::shared_ptr<uth::GameObject> CreateAeroplane();
	static std::shared_ptr<uth::GameObject> CreateHeli();
	static std::shared_ptr<uth::GameObject> CreateHP(pmath::Vec2 pos);
	static std::shared_ptr<uth::GameObject> CreateStar(pmath::Vec2 pos);
	static void CheckEnemies();

};