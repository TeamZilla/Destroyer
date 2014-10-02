#pragma once
#ifndef GameScene_HPP
#define GameScene_HPP

#include <UtH/UtHEngine.hpp>
#include <Player.hpp>
#include <Health.hpp>
#include <BackgroundManager.hpp>
#include <Heli.hpp>

class GameScene : public uth::Scene
{
private: // Just place everything else as private.
	uth::Shader m_shader;
	uth::GameObject* m_startButton;

	BackgroundManager m_bgManager;
	Player m_player;
	Health m_health;
	Heli* m_heli;
	uth::Sound* m_music;

public: // Every one of these public functions are required.
	GameScene();
	~GameScene();

	virtual bool Init();
	virtual bool DeInit();

	virtual bool Update(float dt);
	virtual bool Draw();
};

#endif //GameScene_HPP