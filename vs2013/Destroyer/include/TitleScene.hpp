#pragma once

#include <UtH/UtHEngine.hpp>

#include <Button.hpp>

class TitleScene : public uth::Scene
{
	

	enum class LayerId : char
	{
		TittleBackground,
		Buttons
	};

	std::map<const LayerId, uth::Layer*> m_layers;

	uth::Layer& getLayer(LayerId id);
	uth::GameObject* m_TitleBG;

public: // Every one of these public functions are required.
	TitleScene();
	~TitleScene();

	virtual bool Init();
	virtual bool DeInit();

	virtual void Update(float dt) override;

	
};