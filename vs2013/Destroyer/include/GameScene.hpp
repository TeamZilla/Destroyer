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
#include <Road.hpp>

#include <Tank.hpp>

class GameScene : public uth::Scene
{
private: // Just place everything else as private.
	//uth::GameObject* m_startButton;
	uth::PhysicsWorld m_physWorld;
	uth::GameObject m_gameFloor;

	uth::Layer *BgLayer, *GameLayer, *FgLayer, *UILayer;

	BackgroundManager m_bgManager;
	EnemyManager m_enemyManager;
	void m_enemyManger(float dt);
	Player* m_player;
	Health* m_health;
	Heli* m_heli;
	std::vector <Aeroplane*> m_aeroplane;
	//Tank* m_tank;
	uth::Sound* m_music;
	//uth::SpriteBatch* m_spriteBatch;
	Road* m_road;


	float aeroplaneTimer;

public: // Every one of these public functions are required.
	GameScene();
	~GameScene();

	virtual bool Init();
	virtual bool DeInit();

	virtual void Update(float dt) override;
	//virtual void Draw(uth::RenderTarget& target, uth::RenderAttributes attributes = uth::RenderAttributes()) override;

	float aeroMinSpawnTime;
	float aeroMaxSpawnTime;
	float shootTime;

	bool isCool;
	int rand;
	int rand2;
};

#endif //GameScene_HPP