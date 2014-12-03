#include <TitleScene.hpp>
#include <Scenes.hpp>

using namespace uth;

uth::Layer& TitleScene::getLayer(LayerId id)
{
	return *m_layers[id];
}
TitleScene::TitleScene()
{
	uthEngine.GetWindow().GetCamera().SetSize(1280, 720);
	m_BGM = uthRS.LoadSound("Audio/Music/menu_theme.wav");
	m_BGM->Play();
	m_BGM->Loop(true);

	auto& window = uthEngine.GetWindow();

	Creditsu = false;

	getLayer(LayerId::TitleBackground);
	getLayer(LayerId::Buttons);

	for (auto& e : m_layers)
	{
		AddChild(e.second = new Layer());
	}

	auto TitleBgTex = uthRS.LoadTexture("Title/menu_bg.png");
	TitleBgTex->SetSmooth(true);
	getLayer(LayerId::TitleBackground).AddChild(m_TitleBG = new GameObject());
	m_TitleBG->AddComponent(new Sprite(TitleBgTex,"TitleBG"));
	m_TitleBG->transform.SetOrigin(uth::Origin::TopLeft);
	m_TitleBG->transform.SetPosition(window.GetCamera().GetPosition().x - window.GetCamera().GetSize().x / 2,
		window.GetCamera().GetPosition().y - window.GetCamera().GetSize().y / 2);
	

	//play-button
	
	uth::Texture* PlayTex = uthRS.LoadTexture("Title/Play.png");
	PlayTex->SetSmooth(true);
	getLayer(LayerId::Buttons).AddChild(m_PlayB = new GameObject());
	m_PlayB->AddComponent(new AnimatedSprite(PlayTex,2,2,1,0));
	m_PlayB->transform.SetOrigin(uth::Origin::TopLeft);
	m_PlayB->transform.SetPosition(window.GetCamera().GetPosition().x - window.GetCamera().GetSize().x / 2 + 150,
		window.GetCamera().GetPosition().y - window.GetCamera().GetSize().y / 2 + 400);
	button = new Button(m_PlayB);
	
	//credits
	getLayer(LayerId::Buttons).AddChild(m_CreditsB = new GameObject());
	uth::Texture* CredTex = uthRS.LoadTexture("Title/credits.png");
	CredTex->SetSmooth(true);
	m_CreditsB->AddComponent(new AnimatedSprite(CredTex, 2, 2, 1, 0));
	m_CreditsB->transform.SetOrigin(uth::Origin::TopLeft);
	m_CreditsB->transform.SetPosition(window.GetCamera().GetPosition().x - window.GetCamera().GetSize().x / 2 + 175,
		window.GetCamera().GetPosition().y - window.GetCamera().GetSize().y / 2 + 550);
	button2 = new Button(m_CreditsB);
	



	//options (ball)
	getLayer(LayerId::Buttons).AddChild(m_OptionsB = new GameObject());
	uth::Texture* OptionsTex = uthRS.LoadTexture("Title/options.png");
	OptionsTex->SetSmooth(true);
	m_OptionsB->AddComponent(new AnimatedSprite(OptionsTex, 2, 2, 1, 0));
	m_OptionsB->transform.SetOrigin(uth::Origin::TopLeft);
	m_OptionsB->transform.SetPosition(window.GetCamera().GetPosition().x - window.GetCamera().GetSize().x / 2 + 630,
		window.GetCamera().GetPosition().y - window.GetCamera().GetSize().y / 2 + 600);
	button3 = new Button(m_OptionsB);
	

	
	

	getLayer(LayerId::Buttons).AddChild(m_CBG = new GameObject());
	uth::Texture* CBGTex = uthRS.LoadTexture("UI/pause_BG.png");
	CBGTex->SetSmooth(true);
	m_CBG->AddComponent(new Sprite(CBGTex, "CBG"));
	m_CBG->transform.SetOrigin(uth::Origin::TopLeft);
	m_CBG->transform.SetPosition(uthEngine.GetWindow().GetCamera().GetPosition().x - uthEngine.GetWindow().GetCamera().GetSize().x / 2 + 780,
		uthEngine.GetWindow().GetCamera().GetPosition().y - uthEngine.GetWindow().GetCamera().GetSize().y / 2 + 50);
	m_CBG->SetActive(false);
	
	getLayer(LayerId::Buttons).AddChild(m_EscB = new GameObject());
	uth::Texture* EscTex = uthRS.LoadTexture("UI/esc.png");
	OptionsTex->SetSmooth(true);
	m_EscB->AddComponent(new AnimatedSprite(EscTex, 2, 2, 1, 0));
	m_EscB->transform.SetOrigin(uth::Origin::TopLeft);
	m_EscB->transform.SetPosition(uthEngine.GetWindow().GetCamera().GetPosition().x - uthEngine.GetWindow().GetCamera().GetSize().x / 2 + 1150,
		uthEngine.GetWindow().GetCamera().GetPosition().y - uthEngine.GetWindow().GetCamera().GetSize().y / 2 + 75);
	button4 = new Button(m_EscB);
	
	m_EscB->SetActive(false);

}
TitleScene::~TitleScene()
{}
void TitleScene::Update(float dt)
{
	
	if (!Creditsu)
	{
		button->update(dt);
		button2->update(dt);
		button3->update(dt);

		m_CBG->SetActive(false);
		m_EscB->SetActive(false);

		if (button->IsPressedS() )
		{
			uthSceneM.GoToScene(GAME);
			m_BGM->Stop();
		}

		if (button2->IsPressedS() )
		{
			Creditsu = true;
		}
		
	}
	else
	{
		m_CBG->SetActive(true);
		m_EscB->SetActive(true);

		button4->update(dt);

		if (button4->IsPressedS())
		{
			Creditsu = false;
		}

	}
}


bool TitleScene::Init()
{
	return true;
}
bool TitleScene::DeInit()
{
	m_BGM = nullptr;
	return true;
}

