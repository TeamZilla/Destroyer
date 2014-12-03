#include <GameScene.hpp>
#include <ExplosionEmitter.hpp>
#include <FlameEmitter.hpp>

#include <EnemyFactory.hpp>
#include <TankBehavior.hpp>
#include <SoldierBehavior.hpp>
#include <AeroplaneBehavior.hpp>
#include <FireBreath.hpp>

#include <Scenes.hpp>
#include <Statistics.hpp>

using namespace uth;

uth::Layer& GameScene::getLayer(LayerId id)
{
	return *m_layers[id];
}

// Main initialisation.
// Automatically called inside SceneManager.
bool GameScene::Init()
{
	m_shakeDelayTimer = 0;
	Randomizer::SetSeed();
	uthEngine.GetWindow().GetCamera().SetSize(1280, 720);
	auto& camera = uthEngine.GetWindow().GetCamera();
	
	m_gameFloor.AddComponent(new Sprite(pmath::Vec4(1, 0, 0, 1), pmath::Vec2(3000, 100)));
	m_gameFloor.AddTag("Floor");
	m_gameFloor.transform.SetPosition(0, camera.GetSize().y);
	m_gameFloor.AddComponent(new Rigidbody(m_physWorld));
	m_gameFloor.GetComponent<Rigidbody>()->SetKinematic(true);

	m_bgManager.Init(getLayer(LayerId::Background), getLayer(LayerId::Foreground));

	//m_heli = new Heli(pmath::Vec2f(0, 0));
	//getLayer(LayerId::InGame).AddChild(&m_gameFloor);
	getLayer(LayerId::InGame).AddChild(m_road = new Road(225));
	getLayer(LayerId::InGame).AddChild(m_player = new Player(&m_physWorld));
	getLayer(LayerId::Userinterface).AddChild(m_health = new Health);
	m_player->init(&m_physWorld, m_health);
	//getLayer(LayerId::InGame).AddChild(m_heli = new Heli(pmath::Vec2f(0, 0),m_player));


	m_road->Init(m_player,&m_physWorld);
	
	m_bgManager.SetCameraStartPos(pmath::Vec2f(0, camera.GetSize().y / 2));
	

	m_music = uthRS.LoadSound("Audio/Music/city_theme3.wav");
	m_music->Play();
	m_music->Loop(true);

	m_waveSound = uthRS.LoadSound("Audio/Effects/Explosion1.wav");

	ExplosionEmitter::Init(&getLayer(LayerId::Foreground));
	FlameEmitter::Init(&getLayer(LayerId::Foreground));

	EnemyFactory::Init(&getLayer(LayerId::InGame),&m_physWorld,m_player);
	//EnemyFactory::CreateTank();

	colliderChecks();
	isPaused = false;
	isPlayerDead = false;
	m_soundSlowerTimer = 0;

	auto playTex =		uthRS.LoadTexture("UI/pause.png");
	auto gotext  =		uthRS.LoadTexture("UI/go_pholder.png");
	auto restarttext =	uthRS.LoadTexture("UI/restart.png");
	auto menutext =		uthRS.LoadTexture("UI/menu.png");
	auto pauseBG =		uthRS.LoadTexture("UI/pause_BG.png");
	auto ExitText =		uthRS.LoadTexture("UI/esc.png");
	
	playTex->SetSmooth(true);
	//UI
	getLayer(LayerId::Userinterface).AddChild(m_pauseMenu = new GameObject());
	m_pauseMenu->AddComponent(new Sprite(pauseBG, "pauseBGsprite"));
	m_pauseMenu->transform.SetOrigin(uth::Origin::TopLeft);
	m_pauseMenu->SetActive(false);


	getLayer(LayerId::Userinterface).AddChild(m_gameOverScreenPicture = new GameObject());
	m_gameOverScreenPicture->AddComponent(new Sprite(gotext));
	m_gameOverScreenPicture->transform.SetOrigin(uth::Origin::TopLeft);
	m_gameOverScreenPicture->transform.SetScale(0.90f, 0.90f);
	m_gameOverScreenPicture->SetActive(false);

	getLayer(LayerId::Userinterface).AddChild(m_PauseButton = new GameObject());
	m_PauseButton->AddComponent(new AnimatedSprite(playTex, 2, 2, 1, 0));
	m_PauseButton->transform.SetOrigin(uth::Origin::TopLeft);
	
	m_pauseB = new Button(m_PauseButton);

	getLayer(LayerId::Userinterface).AddChild(m_MenuButton = new GameObject());
	m_MenuButton->AddComponent(new AnimatedSprite(menutext, 2, 2, 1, 0));
	m_MenuButton->transform.SetOrigin(uth::Origin::TopLeft);
	m_menuB = new Button(m_MenuButton);
	m_MenuButton->SetActive(false);

	getLayer(LayerId::Userinterface).AddChild(m_RestartButton = new GameObject());
	m_RestartButton->AddComponent(new AnimatedSprite(restarttext, 2, 2, 1, 0));
	m_RestartButton->transform.SetOrigin(uth::Origin::TopLeft);
	m_restartB = new Button(m_RestartButton);
	m_RestartButton->SetActive(false);

	getLayer(LayerId::Userinterface).AddChild(m_ExitButton = new GameObject());
	m_ExitButton->AddComponent(new AnimatedSprite(ExitText, 2, 2, 1, 0));
	m_ExitButton->transform.SetOrigin(uth::Origin::TopLeft);
	m_ExitB = new Button(m_ExitButton);
	m_ExitButton->SetActive(false);

	return true;
}


// Update loop. Gone trought once per frame.
void GameScene::Update(float dt)
{
	auto& camera = uthEngine.GetWindow().GetCamera();

	if (!isPaused && !isPlayerDead)
	{	
		m_PauseButton->transform.SetPosition(camera.GetPosition().x - camera.GetSize().x / 2 + 1150,
											 camera.GetPosition().y - camera.GetSize().y / 2 + 20);
		m_PauseButton->transform.SetRotation(camera.GetRotation());
		
		static int count;
		static float time = 0;
		time += dt;
		count++;
		if (time > 6)
		{
			time -= 6;
			count = 0;
		}

		m_physWorld.Update(dt);
		m_bgManager.Update(dt);

		if (isInitedShake)
		{
			m_shakeDelayTimer += dt;

			if (m_shakeDelayTimer >= 0.6)
			{
				m_bgManager.Shake(3, 2.0f);
				m_road->InitShock();
				m_waveSound->Play();
				isInitedShake = false;
				m_shakeDelayTimer = 0;
			}
		}

		EnemyFactory::Update(dt);
		Scene::Update(dt);
		m_pauseB->update(dt);
		ControlFunctions();
		if (Statistics::player_hp <= 0)
			isPlayerDead = true;

		if (m_pauseB->IsPressedS())
		{
			isPaused = true;
			m_pauseMenu->SetActive(true);
			m_MenuButton->SetActive(true);
			m_RestartButton->SetActive(true);
			m_ExitButton->SetActive(true);


			
		}

		//Music gets normal
		if (m_soundSlowerTimer > 0)
		{
			m_soundSlowerTimer -= dt * 90;
			m_music->SetPitch(100-m_soundSlowerTimer);
		}
	}
	//If Paused
	else if (isPaused && !isPlayerDead) //TODO:: Pause menu stuff here
	{
		//Music gets slower
		if (m_soundSlowerTimer < 100)
		{
			m_soundSlowerTimer += dt * 90;
			m_music->SetPitch(100-m_soundSlowerTimer);
		}

	#ifdef UTH_SYSTEM_ANDROID
		//TODO: Android only pause functions here

	#else
		//PC only code here

	#endif
		//If user press m_pause button game resumes
		m_pauseB->update(dt);
		if (m_pauseB->IsPressedS())
		{
			isPaused = false;
		}
	}
	else if (!isPaused && isPlayerDead) //Game over functions here
	{
		m_gameOverScreenPicture->SetActive(true);
		m_MenuButton->SetActive(true);
		m_RestartButton->SetActive(true);

		m_menuB->update(dt);
		m_restartB->update(dt);

		auto& camera = uthEngine.GetWindow().GetCamera();

		m_gameOverScreenPicture->transform.SetPosition(camera.GetPosition().x - camera.GetSize().x / 3 + 50, camera.GetPosition().y - camera.GetSize().y / 2);
		m_MenuButton->transform.SetPosition(camera.GetPosition().x - camera.GetSize().x / 3 + 200, camera.GetPosition().y - camera.GetSize().y /2 + 630);
		m_RestartButton->transform.SetPosition(camera.GetPosition().x - camera.GetSize().x / 3 + 500, camera.GetPosition().y - camera.GetSize().y /2 + 630);

		if (m_restartB->IsPressedS())
			uthSceneM.GoToScene(GAME);
		if (m_menuB->IsPressedS())
			uthSceneM.GoToScene(TITLE);
	}
} //Update end


void GameScene::ControlFunctions()
{

#ifdef UTH_SYSTEM_ANDROID

	const auto& wnd = uthEngine.GetWindow();
	const pmath::Vec2& touchStart = wnd.PixelToCoords(uthInput.Touch[0].GetStartPosition());
	const pmath::Vec2& touchEnd = wnd.PixelToCoords(uthInput.Touch[0].GetEndPosition());

	if (uthInput.Touch.Motion() == TouchMotion::DRAG)
	{	//Swipe up
		if (touchStart.y > touchEnd.y + 160)
		{
			Control_up();
		}
		//Swipe down
		else if (touchStart.y < touchEnd.y - 160)
		{
			Control_down();
		}
		//Swipe left
		else if (touchStart.x > touchEnd.x + 180)
		{
			Control_left();
		}
		//Swipe right
		else if (touchStart.x < touchEnd.x - 180)
		{
			Control_right();
		}
	}
#else
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Up))
	{
		Control_up();
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Down))
	{
		Control_down();
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Left) &&
		!uthInput.Keyboard.IsKeyDown(Keyboard::Right))
	{
		Control_left();
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Right) &&
		!uthInput.Keyboard.IsKeyDown(Keyboard::Left))
	{
		Control_right();
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::P))
	{
		isPaused = true;
	}

		if (uthInput.Keyboard.IsKeyDown(Keyboard::F))
		{
		}

#endif
}

void GameScene::Control_up()
{
	if (!m_player->m_isCrouching && !m_player->m_isJumping)
		m_player->Jump();
}
void GameScene::Control_down()
{
	if (!m_player->m_isJumping && !m_player->m_isCrouching && !m_player->m_isTurning)
	{
		m_player->Crouch();
		isInitedShake = true;
	}
}
void GameScene::Control_left()
{
	if (m_player->CheckIfGoingRight())
	{
		m_player->ChangeDirection();
	}
}
void GameScene::Control_right()
{
	if (!m_player->CheckIfGoingRight())
	{
		m_player->ChangeDirection();
	}
}
void GameScene::colliderChecks()
{
	contactListener.onBeginContact = [](b2Contact* contact, GameObject* A, GameObject* B)
	{
		
		//Enemies hit road collider
		if (B->HasTag("Enemy") && A->HasTag("RoadCollider"))
		{
			//Put Tag for every enemytype here
			if (B->HasTag("Tank"))
			{
				B->GetComponent<TankBehavior>()->Hit();
			}
			else if (B->HasTag("Soldier"))
			{
				B->GetComponent<SoldierBehavior>()->Hit();
			}
		}
		//Some enemies touch player
		if (B->HasTag("Enemy") && A->HasTag("Player") ||
			A->HasTag("Enemy") && B->HasTag("Player"))
		{
			auto* AA = A;
			auto* BB = B;
			if (A->HasTag("Enemy"))
			{
				BB = A;
				AA = B;
			}

			//Put Tag for every enemytype here
			if (B->HasTag("Tank"))
			{
				B->GetComponent<TankBehavior>()->Destroy();
				static_cast<Player*>(A)->Hit(3);
			}
			else if (B->HasTag("Soldier"))
			{
				B->GetComponent<SoldierBehavior>()->Destroy();
			}
			else if (B->HasTag("Aeroplane"))
			{
				//B->GetComponent<AeroplaneBehavior>()->Hit();
				//static_cast<Player*>(A)->Hit();
			}
		}
		//When enemies are dying and are hitting floor
		if (B->HasTag("Enemy") && A->HasTag("Floor"))
		{
			//Put Tag for every enemytype here
			if (B->HasTag("Tank"))
			{
				if (B->GetComponent<TankBehavior>()->isExploding())
				{
					B->GetComponent<TankBehavior>()->Destroy();
				}
			}
			else if (B->HasTag("Soldier"))
			{
				if (B->GetComponent<SoldierBehavior>()->isExploding())
				{
					B->GetComponent<SoldierBehavior>()->Destroy();
				}
			}
		}
		//When enemies are dying and are hitting aeroplane
		if (A->HasTag("Enemy") && B->HasTag("Aeroplane") ||
			B->HasTag("Enemy") && A->HasTag("Aeroplane"))
		{
			auto* AA = A;
			auto* BB = B;
			if (B->HasTag("Enemy"))
			{
				BB = A;
				AA = B;
			}
			//Put Tag for every enemytype here
			if (A->HasTag("Tank"))
			{
				if (A->GetComponent<TankBehavior>()->isExploding())
				{
					A->GetComponent<TankBehavior>()->Destroy();
					B->GetComponent<AeroplaneBehavior>()->Hit();
				}
			}
			else if (A->HasTag("Soldier"))
			{
				if (A->GetComponent<SoldierBehavior>()->isExploding())
				{
					A->GetComponent<SoldierBehavior>()->Destroy();
					B->GetComponent<AeroplaneBehavior>()->Hit();
				}
			}
		}


		if (A->HasTag("Enemy") && B->HasTag("TailCollider") ||
			B->HasTag("Enemy") && A->HasTag("TailCollider"))
		{
			auto* AA = A;
			auto* BB = B;
			if (B->HasTag("Enemy"))
			{
				BB = A;
				AA = B;
			}

			if (A->HasTag("Soldier"))
				A->GetComponent<SoldierBehavior>()->TailWhipHit();
			else if (B->HasTag("Soldier"))
				B->GetComponent<SoldierBehavior>()->TailWhipHit();

		}
		//if (A->HasTag("Enemy") && B->HasTag("Enemy"))
		//{
		//	if (A->HasTag("Tank") && B->HasTag("Tank"))
		//	{
		//		if (A->GetComponent<TankBehavior>()->isExploding() ||
		//			B->GetComponent<TankBehavior>()->isExploding())
		//		{
		//			A->GetComponent<TankBehavior>()->Destroy();
		//			B->GetComponent<TankBehavior>()->Destroy();
		//		}

		//	}
		//	if (A->HasTag("Soldier") && B->HasTag("Soldier"))
		//	{
		//		if (A->GetComponent<SoldierBehavior>()->isExploding() ||
		//			B->GetComponent<SoldierBehavior>()->isExploding())
		//		{
		//			A->GetComponent<SoldierBehavior>()->Destroy();
		//			B->GetComponent<SoldierBehavior>()->Destroy();
		//		}
		//	}
		//}
	};
	m_physWorld.SetContactListener(&contactListener);

}
//Default constructor for initialising constant variables.
GameScene::GameScene()
//: m_bgManager(250,500,150)
	:
	m_bgManager
	(
		uthEngine.GetWindow().GetCamera().GetSize().y - 470,
		uthEngine.GetWindow().GetCamera().GetSize().y - 220,
		uthEngine.GetWindow().GetCamera().GetSize().y - 570
	),
	m_physWorld(0, 10)
{
	getLayer(LayerId::Background);
	getLayer(LayerId::InGame);
	getLayer(LayerId::Foreground);
	getLayer(LayerId::Userinterface);

	for (auto& e : m_layers)
	{
		AddChild(e.second = new Layer());
	}

	//auto & l = getLayer(LayerId::InGame);
	//m_enemyManager = new EnemyManager(l);
}
//Default deconstrutor.
GameScene::~GameScene()
{
	ExplosionEmitter::DeInit();
}

// Main deinitialisation.
// Automatically called inside SceneManager.
bool GameScene::DeInit()
{
	return true;
}