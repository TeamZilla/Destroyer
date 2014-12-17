#include<Button.hpp>
#include<TitleScene.hpp>
using namespace uth;


Button::Button(uth::GameObject* gameObj)
{
	m_butTransform = &gameObj->transform;
	m_butAnim = gameObj->GetComponent<AnimatedSprite>();
	auto lol =  m_butTransform;
	auto rofl = m_butTransform->GetLocalBounds().position;
	m_buttonSound = uthRS.LoadSound("Audio/Effects/Button.wav");
}

Button::~Button()
{

}

void Button::update(float dt)
{
	auto bounds = m_butTransform->GetGlobalBounds();
	auto touchpos = uthEngine.GetWindow().PixelToCoords(uthInput.Common.Position());

	if (uthInput.Common.Event() == uth::InputEvent::TAP && m_butTransform->GetGlobalBounds().contains(touchpos))//	bounds.intersects(touchBounds))
	{
		m_butAnim->ChangeAnimation(1, 1, 1, 0, false);
		m_isPressed = true;
		m_buttonSound->Play();

	}
	else
	{
		m_butAnim->ChangeAnimation(0,1,0,0,false);
		
		m_isPressed = false;
	}
	
	
}

bool Button::IsPressedS()
{

	return m_isPressed;

}