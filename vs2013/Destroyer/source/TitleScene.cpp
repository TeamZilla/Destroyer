#include <TitleScene.hpp>
#include <Scenes.hpp>
#include <GameStats.hpp>
#include <UtH/Platform/JavaFunctions.hpp>

using namespace uth;

uth::Layer& TitleScene::getLayer(LayerId id)
{
	return *m_layers[id];
}
TitleScene::TitleScene()
{
	javaFunc::ShowAdBanner("6300978111",Origin::BottomRight);
	Statistics.Load();

	uthEngine.GetWindow().GetCamera().SetSize(1280, 720);
	m_roar = uthRS.LoadSound("Audio/Effects/moz_howl.wav");
	m_BGM = uthRS.LoadSound("Audio/Music/menu_theme.wav");
	m_BGM->Play();
	m_BGM->Loop(true);

	auto& window = uthEngine.GetWindow();
	        
	Creditsu = false;
	options = false;
	isGameStarting = false;

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
	uth::Texture* CredTex = uthRS.LoadTexture("Title/creditsb.png");
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
	m_OptionsB->transform.SetPosition(window.GetCamera().GetPosition().x - window.GetCamera().GetSize().x / 2 + 10,
		window.GetCamera().GetPosition().y - window.GetCamera().GetSize().y / 2 + 10);
	button3 = new Button(m_OptionsB);
	m_OptionsB->SetActive(false);
	

	
	

	getLayer(LayerId::Buttons).AddChild(m_CBG = new GameObject());
	uth::Texture* CBGTex = uthRS.LoadTexture("UI/pause_BG.png");
	CBGTex->SetSmooth(true);
	m_CBG->AddComponent(new Sprite(CBGTex, "CBG"));
	m_CBG->transform.SetOrigin(uth::Origin::TopLeft);
	m_CBG->transform.SetPosition(window.GetCamera().GetPosition().x - window.GetCamera().GetSize().x / 2 + 775,
								 window.GetCamera().GetPosition().y - window.GetCamera().GetSize().y / 2 + 50);
	m_CBG->SetActive(false);
	
	getLayer(LayerId::Buttons).AddChild(m_EscB = new GameObject());
	uth::Texture* EscTex = uthRS.LoadTexture("UI/esc.png");
	OptionsTex->SetSmooth(true);
	m_EscB->AddComponent(new AnimatedSprite(EscTex, 2, 2, 1, 0));
	m_EscB->transform.SetOrigin(uth::Origin::TopLeft);
	m_EscB->transform.SetPosition(window.GetCamera().GetPosition().x - window.GetCamera().GetSize().x / 2 + 1175,
								  window.GetCamera().GetPosition().y - window.GetCamera().GetSize().y / 2 + 50);
	button4 = new Button(m_EscB);
	m_EscB->SetActive(false);

	getLayer(LayerId::Buttons).AddChild(m_credits = new GameObject());
	auto CreditsTex = uthRS.LoadTexture("credits.png");
	CreditsTex->SetSmooth(true);
	m_credits->AddComponent(new Sprite(CreditsTex, "hops"));
	
	m_credits->transform.SetOrigin(uth::Origin::TopLeft);
	m_credits->transform.SetScale(0.8f, 0.8f);
	m_credits->transform.SetPosition(window.GetCamera().GetPosition().x - window.GetCamera().GetSize().x / 2 + 625,
		window.GetCamera().GetPosition().y - window.GetCamera().GetSize().y / 2 + 15);
	m_credits->SetActive(false);

	getLayer(LayerId::Buttons).AddChild(m_blackOverlay = new GameObject());
	m_blackOverlay->AddComponent(new Sprite(pmath::Vec4(0, 0, 0, 0),pmath::Vec2(3500, 3500)));
	m_blackOverlay->transform.SetPosition(window.GetCamera().GetPosition().x / 2,
										  window.GetCamera().GetPosition().y / 2 - window.GetCamera().GetSize().y / 2);

	//credits texts
	




	

}
TitleScene::~TitleScene()
{}
void TitleScene::Update(float dt)
{
	
	if (!Creditsu && !options && !isGameStarting)
	{
		button->update(dt);
		button2->update(dt);
		button3->update(dt);

		m_CBG->SetActive(false);
		m_EscB->SetActive(false);
		m_credits->SetActive(false);



		if (button->IsPressedS() && !isGameStarting)
		{
			m_BGM->Stop();
			m_roar->Play();
			isGameStarting = true;
			//Remember to close ad before playing game
			javaFunc::CloseAd("6300978111");
		}

		if (button2->IsPressedS() && !isGameStarting)
		{
			Creditsu = true;
		}
		
	}
	else if (Creditsu)
	{
		m_credits->SetActive(true);

		button2->update(dt);

		if (button2->IsPressedS())
		{
			Creditsu = false;
			
		}

	}
	if (!options)
	{


		if (button3->IsPressedS())
		{
			options = true;

		}
	}
	else
	{
		m_CBG->SetActive(true);
		m_EscB->SetActive(true);
		button4->update(dt);
		button3->update(dt);
		
		if (button4->IsPressedS())
		{
			options = false;
		}
		if (button3->IsPressedS())
		{
			options = false;
		}
	}


	if (isGameStarting)
	{
		m_blackOverlay->GetComponent<Sprite>()->SetColor(pmath::Vec4(0, 0, 0, m_blackOverlay->GetComponent<Sprite>()->GetColor().a + 0.5f*dt));
		if (m_blackOverlay->GetComponent<Sprite>()->GetColor().a > 1)
			uthSceneM.GoToScene(GAME);
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

