#include<Button.hpp>
using namespace uth;

bool Button::m_isPressed()
{
	
	return true;
}

Button::Button(uth::GameObject* gameObj)
{
	m_butTransform = &gameObj->transform;
	m_butAnim = gameObj->GetComponent<AnimatedSprite>();
	auto lol =  m_butTransform;
	auto rofl = m_butTransform->GetLocalBounds().position;
}

Button::~Button()
{

}

void Button::update(float dt)
{
	auto bounds = m_butTransform->GetGlobalBounds();
	auto touchBoundSize = pmath::Vec2(1, 1);
	auto calculateMiss = pmath::Vec2(uthInput.Common.Position().x - uthEngine.GetWindow().GetSize().x/2,
		uthInput.Common.Position().y - uthEngine.GetWindow().GetSize().y/2);
	auto touchBounds = pmath::Rectf::Rectangle(calculateMiss, touchBoundSize);

	if (uthInput.Common.Event() == uth::InputEvent::TAP &&	bounds.intersects(touchBounds))
	{
		WriteLog("Hit button");
		m_butAnim->ChangeAnimation(1, 1, 1, 0, false);

	}
	else if (uthInput.Common.Event() == uth::InputEvent::TAP)
	{
		WriteLog("%f     %f", touchBounds.position.x, touchBounds.position.y);
		WriteLog("%f     %f", bounds.position.x, bounds.position.y);
		WriteLog("%f     %f", m_butTransform->GetPosition().x, m_butTransform->GetPosition().y);
	}
	else
	{
		m_butAnim->ChangeAnimation(0,1,0,0,false);
	}
}

bool Button::IsPressedS()
{
	return true;

}