#pragma once

#include <UtH/UtHEngine.hpp>

class Button : public uth::GameObject
{


	bool m_isPressed();

public:

	Button(uth::Texture, uth::AnimatedSprite);
	~Button();

	bool IsPressed();


};
