#pragma once

#include <UtH/UtHEngine.hpp>

class Button : public uth::GameObject
{


	bool m_isPressed = false;
	uth::Transform* m_butTransform;
	uth::AnimatedSprite* m_butAnim;
	uth::Sound* m_buttonSound;
	

public:

	Button(uth::GameObject*);
	~Button();

	void update(float dt);
	bool IsPressedS();



};
