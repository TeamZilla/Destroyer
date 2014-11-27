#include <TitleScene.hpp>

using namespace uth;

uth::Layer& TitleScene::getLayer(LayerId id)
{
	return *m_layers[id];
}
TitleScene::TitleScene()
{
	auto& window = uthEngine.GetWindow();


	getLayer(LayerId::TitleBackground);

	for (auto& e : m_layers)
	{
		AddChild(e.second = new Layer());
	}

	auto TitleBgTex = uthRS.LoadTexture("Title/menu_bg.png");
	TitleBgTex->SetSmooth(true);
	getLayer(LayerId::TitleBackground).AddChild(m_TitleBG = new GameObject());
	m_TitleBG->AddComponent(new Sprite(TitleBgTex,"TitleBG"));
	m_TitleBG->transform.SetOrigin(uth::Origin::TopLeft);
	m_TitleBG->transform.SetPosition(window.GetCamera().GetPosition().x - window.GetSize().x / 2,
	window.GetCamera().GetPosition().y - window.GetSize().y / 2);
	
	//play-button
	getLayer(LayerId::TitleBackground).AddChild(m_PlayB = new GameObject());
	uth::Texture* PlayTex = uthRS.LoadTexture("Title/Play.png");
	PlayTex->SetSmooth(true);
	m_PlayB->AddComponent(new AnimatedSprite(PlayTex,2,2,1,0));
	m_PlayB->transform.SetOrigin(uth::Origin::TopLeft);
	m_PlayB->transform.SetPosition(window.GetCamera().GetPosition().x - window.GetSize().x / 2 + 200,
		window.GetCamera().GetPosition().y - window.GetSize().y / 2 + 400);
	button = new Button(m_PlayB);
	
	
	//credits
	getLayer(LayerId::TitleBackground).AddChild(m_CreditsB = new GameObject());
	uth::Texture* CredTex = uthRS.LoadTexture("Title/credits.png");
	CredTex->SetSmooth(true);
	m_CreditsB->AddComponent(new AnimatedSprite(CredTex, 2, 2, 1, 0));
	m_CreditsB->transform.SetOrigin(uth::Origin::TopLeft);
	m_CreditsB->transform.SetPosition(window.GetCamera().GetPosition().x - window.GetSize().x / 2 + 200,
		window.GetCamera().GetPosition().y - window.GetSize().y / 2 + 550);
	button2 = new Button(m_CreditsB);
	

	
}
TitleScene::~TitleScene()
{}
void TitleScene::Update(float dt)
{
	button->update(dt);
	button2->update(dt);
}
bool TitleScene::Init()
{
	return true;
}
bool TitleScene::DeInit()
{
	return true;
}

