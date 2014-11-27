#pragma once

#include <UtH/UtHEngine.hpp>

class Button : public uth::GameObject
{


	bool m_isPressed();
	uth::Transform* m_butTransform;
	uth::AnimatedSprite* m_butAnim;

public:

	Button(uth::Transform*, uth::AnimatedSprite*);
	~Button();

	void update(float dt);
	bool IsPressedS();


};
