

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
#include <Button.hpp>


class GameScene : public uth::Scene
{
    // Just place everything else as private.
	uth::PhysicsWorld m_physWorld;
	uth::PhysicsContactListener contactListener;
	uth::GameObject m_gameFloor;
	Button* m_pauseB;
	Button* m_menuB;
	Button* m_restartB;
	Button* m_ExitB;
	uth::GameObject* m_PauseButton;
	uth::GameObject* m_MenuButton;
	uth::GameObject* m_RestartButton;
	uth::GameObject*  m_gameOverScreenPicture;
	uth::GameObject* m_ExitButton;
	uth::GameObject* m_pauseMenu;
	uth::GameObject* m_blackOverlay;
	


	enum class LayerId : char
	{
		Background,
		InGame,
		Foreground,
		Userinterface
	};

	std::map<const LayerId, uth::Layer*> m_layers;

	uth::Layer& getLayer(LayerId id);



	void ControlFunctions();
	void Control_up();
	void Control_down();
	void Control_left();
	void Control_right();

	void colliderChecks();

	BackgroundManager m_bgManager;
	Health* m_health;
	Heli* m_heli;
	uth::Sound* m_music;
	uth::Sound* m_waveSound;
	uth::Sound* m_gameOverMusic;
	uth::Sound* m_afterMathMusic;
	Road* m_road;
	float m_shakeDelayTimer;
	float aeroplaneTimer;
	float m_soundSlowerTimer;
	bool isPlayerDead;

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