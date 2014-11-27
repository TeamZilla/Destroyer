#include<Button.hpp>
using namespace uth;

bool Button::m_isPressed()
{
	
	return true;
}

Button::Button(uth::Transform* transform, uth::AnimatedSprite* sprite)	:
m_butTransform(transform),
m_butAnim(sprite)
{/*
	auto lol = m_butTransform;
	auto rofl = m_butTransform->GetGlobalBounds().position;
	auto lols = m_butAnim;*/
}

Button::~Button()
{

}

void Button::update(float dt)
{
	auto bounds = m_butTransform->GetGlobalBounds();
	auto touchBoundSize = pmath::Vec2(1, 1);
	auto touchBounds = pmath::Rectf::Rectangle(uthInput.Common.Position(), touchBoundSize);

	if (uthInput.Common.Event() == uth::InputEvent::TAP &&	bounds.intersects(touchBounds))
	{
		WriteLog("Hit button");
	}
	else if (uthInput.Common.Event() == uth::InputEvent::TAP)
	{
		WriteLog("%f     %f", touchBounds.position.x, touchBounds.position.y);
		WriteLog("%f     %f", bounds.position.x, bounds.position.y);
	}
}

bool Button::IsPressedS()
{
	return true;

}