#pragma once

#include <UtH/UtHEngine.hpp>

#include <Button.hpp>


class TitleScene : public uth::Scene
{
	uth::Sound* m_BGM;
	uth::Sound* m_roar;

	enum class LayerId : char
	{
		TitleBackground,
		Buttons
	};

	std::map<const LayerId, uth::Layer*> m_layers;


	uth::Layer& getLayer(LayerId id);
	uth::GameObject* m_TitleBG;
	Button* button;
	Button* button2;
	Button* button3;
	Button* button4;
	Button* button5;
	

public: // Every one of these public functions are required.
	TitleScene();
	~TitleScene();
	uth::GameObject* m_PlayB;
	uth::GameObject* m_CreditsB;
	uth::GameObject* m_OptionsB;
	uth::GameObject* m_EscB;
	uth::GameObject* m_CBG;
	uth::GameObject* m_blackOverlay;

	bool Creditsu, isGameStarting;
	virtual bool Init();
	virtual bool DeInit();

	virtual void Update(float dt) override;

	
};