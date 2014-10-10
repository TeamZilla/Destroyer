#pragma once
#ifndef GameScene_HPP
#define GameScene_HPP

#include <UtH/UtHEngine.hpp>
#include <Player.hpp>
#include <Health.hpp>
#include <BackgroundManager.hpp>
#include <EnemyManager.hpp>
#include <Heli.hpp>
#include <Aeroplane.hpp>

#include <Tank.hpp>

class GameScene : public uth::Scene
{
private: // Just place everything else as private.
	uth::Shader m_shader;
	uth::GameObject* m_startButton;
	uth::PhysicsWorld m_physWorld;
	uth::GameObject m_gameFloor;

	BackgroundManager m_bgManager;
	EnemyManager m_enemyManager;
	void m_enemyManger(float dt);
	Player m_player;
	Health m_health;
	Heli* m_heli;
	std::vector <Aeroplane*> m_aeroplane;
	Tank* m_tank;
	uth::Sound* m_music;

	float aeroplaneTimer;

public: // Every one of these public functions are required.
	GameScene();
	~GameScene();

	virtual bool Init();
	virtual bool DeInit();

	virtual bool Update(float dt);
	virtual bool Draw();

	float aeroMinSpawnTime;
	float aeroMaxSpawnTime;
	float shootTime;

	bool isCool;
	int rand;
	int rand2;
};

#endif //GameScene_HPP