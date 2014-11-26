#pragma once

#include <UtH/UtHEngine.hpp>

class Button : public uth::GameObject
{


	bool m_isPressed();

public:

	Button(uth::Texture,uth::AnimatedSprite);
	~Button();

	bool IsPressed();


};

class TitleScene : public uth::Scene
{
	

	enum class LayerId : char
	{
		TittleBackground,
		Buttons
	};

	std::map<const LayerId, uth::Layer*> m_layers;

	uth::Layer& getLayer(LayerId id);
	

public: // Every one of these public functions are required.
	TitleScene();
	~TitleScene();

	virtual bool Init();
	virtual bool DeInit();

	virtual void Update(float dt) override;

	
};