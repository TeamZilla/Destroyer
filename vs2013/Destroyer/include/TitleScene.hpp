#pragma once

#include <UtH/UtHEngine.hpp>

#include <Button.hpp>


class TitleScene : public uth::Scene
{
	

	enum class LayerId : char
	{
		TitleBackground,
		Buttons
	};

	std::map<const LayerId, uth::Layer*> m_layers;

	uth::Layer& getLayer(LayerId id);
	uth::GameObject* m_TitleBG;
	Button* button;

public: // Every one of these public functions are required.
	TitleScene();
	~TitleScene();
	uth::GameObject* m_PlayB;

	virtual bool Init();
	virtual bool DeInit();

	virtual void Update(float dt) override;

	
};