#pragma once

#include <UtH/UtHEngine.hpp>
#include <Player.hpp>
#include <Health.hpp>
#include <BackgroundManager.hpp>
//#include <EnemyManager.hpp>
#include <Heli.hpp>
//#include <Aeroplane.hpp>
#include <Road.hpp>
#include <ExpParAffector.hpp>

#include <Tank.hpp>

class GameScene : public uth::Scene
{
    // Just place everything else as private.
	uth::PhysicsWorld m_physWorld;
	uth::PhysicsContactListener contactListener;
	uth::GameObject m_gameFloor;

	enum class LayerId : char
	{
		Background,
		InGame,
		Foreground,
		Userinterface
	};

	std::map<const LayerId, uth::Layer*> m_layers;

	uth::Layer& getLayer(LayerId id);
	void colliderChecks();

	BackgroundManager m_bgManager;
	Health* m_health;
	Heli* m_heli;
	uth::Sound* m_music;
	uth::Sound* m_waveSound;
	Road* m_road;
	float m_shakeDelayTimer;


	float aeroplaneTimer;

public: // Every one of these public functions are required.
	GameScene();
	~GameScene();

	virtual bool Init();
	virtual bool DeInit();

	virtual void Update(float dt) override;

	bool ParticleInit();
	uth::ParticleSystem* ps;
	void ParticleEmit(pmath::Vec2 pos);

	Player* m_player;
	float aeroMinSpawnTime;
	float aeroMaxSpawnTime;
	float shootTime;

	bool isCool, isPaused;
	bool isInitedShake = false;
	int rand;
	int rand2;
};