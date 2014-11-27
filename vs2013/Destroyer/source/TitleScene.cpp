#include <TitleScene.hpp>

using namespace uth;

uth::Layer& TitleScene::getLayer(LayerId id)
{
	return *m_layers[id];
}
TitleScene::TitleScene()
{
	auto TitleBgTex = uthRS.LoadTexture("Title/menu_bg.png");
	TitleBgTex->SetSmooth(true);
	m_TitleBG = new GameObject();
	m_TitleBG->AddComponent(new Sprite(TitleBgTex,"TitleBG"));
	m_TitleBG->transform.SetOrigin(uth::Origin::TopLeft);
	m_TitleBG->transform.SetPosition(uthEngine.GetWindow().GetCamera().GetPosition().x - uthEngine.GetWindow().GetSize().x / 2,
		uthEngine.GetWindow().GetCamera().GetPosition().y - uthEngine.GetWindow().GetSize().y / 2);
	AddChild<GameObject>(m_TitleBG);




	m_PlayB = new GameObject();
	uth::Texture* PlayTex = uthRS.LoadTexture("Title/Play.png");
	PlayTex->SetSmooth(true);
	m_PlayB->AddComponent(new AnimatedSprite(PlayTex,2,2,1,0));
	m_PlayB->transform.SetOrigin(uth::Origin::Center);m_PlayB->transform.SetPosition(m_TitleBG->transform.GetPosition());
	button = new Button(&m_PlayB->transform, m_PlayB->GetComponent<AnimatedSprite>());
	
	AddChild<GameObject>(m_PlayB);

	
}
TitleScene::~TitleScene()
{}
void TitleScene::Update(float dt)
{
	button->update(dt);
}
bool TitleScene::Init()
{
	return true;
}
bool TitleScene::DeInit()
{
	return true;
}

