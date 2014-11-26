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
	m_TitleBG->AddComponent(new Sprite(TitleBgTex, "titleBG"));
	m_TitleBG->transform.SetOrigin(uth::Origin::TopLeft);
	m_TitleBG->transform.SetPosition(uthEngine.GetWindow().GetCamera().GetPosition().x - uthEngine.GetWindow().GetSize().x / 2,
		uthEngine.GetWindow().GetCamera().GetPosition().y - uthEngine.GetWindow().GetSize().y / 2);



	auto BackGround = AddChild<GameObject>(m_TitleBG);
	
}
TitleScene::~TitleScene()
{}
void TitleScene::Update(float dt)
{}
bool TitleScene::Init()
{
	return true;
}
bool TitleScene::DeInit()
{
	return true;
}

