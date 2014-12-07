#include <GameScene.hpp>
#include <ExplosionEmitter.hpp>
#include <FlameEmitter.hpp>

#include <EnemyFactory.hpp>
#include <TankBehavior.hpp>
#include <SoldierBehavior.hpp>
#include <AeroplaneBehavior.hpp>
#include <FireBreath.hpp>

#include <Scenes.hpp>
#include <GameStats.hpp>

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
	//Put score to 0 at start of the game
	Statistics.score.current = 0;

	Randomizer::SetSeed();
	uthEngine.GetWindow().GetCamera().SetSize(1280, 720);
	auto& camera = uthEngine.GetWindow().GetCamera();
	
	m_gameFloor.AddComponent(new Sprite(pmath::Vec4(1, 0, 0, 1), pmath::Vec2(3000, 100)));
	m_gameFloor.AddTag("Floor");
	m_gameFloor.transform.SetPosition(0, camera.GetSize().y);
	m_gameFloor.AddComponent(new Rigidbody(m_physWorld));
	m_gameFloor.GetComponent<Rigidbody>()->SetKinematic(true);

	m_bgManager.Init(getLayer(LayerId::Background), getLayer(LayerId::Foreground));

	getLayer(LayerId::InGame).AddChild(m_road = new Road(225));
	getLayer(LayerId::InGame).AddChild(m_player = new Player(&m_physWorld));
	getLayer(LayerId::Userinterface).AddChild(m_health = new Health);
	m_player->init(&m_physWorld, m_health);


	m_road->Init(m_player,&m_physWorld);
	
	m_bgManager.SetCameraStartPos(pmath::Vec2f(0, camera.GetSize().y / 2));
	

	m_gameOverMusic  = uthRS.LoadSound("Audio/Music/game_over.wav");
	m_afterMathMusic = uthRS.LoadSound("Audio/Music/aftermath_theme.wav");
	m_music = uthRS.LoadSound("Audio/Music/city_theme3.wav");
	m_music->Play();
	m_music->SetPitch(100);
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
	auto gotext =		uthRS.LoadTexture("UI/GOmenu.png");
	auto restarttext =	uthRS.LoadTexture("UI/restart.png");
	auto menutext =		uthRS.LoadTexture("UI/menu.png");
	auto pauseBG =		uthRS.LoadTexture("UI/pausemenu.png");
	auto ExitText =		uthRS.LoadTexture("UI/esc.png");
	
	playTex->SetSmooth(true);
	//UI
	getLayer(LayerId::Userinterface).AddChild(m_pauseMenu = new GameObject());
	m_pauseMenu->AddComponent(new Sprite(pauseBG, "pauseBGsprite"));
	m_pauseMenu->transform.SetOrigin(uth::Origin::TopLeft);
	m_pauseMenu->transform.SetScale(0.90f, 0.90f);
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

	getLayer(LayerId::Userinterface).AddChild(m_blackOverlay = new GameObject());
	m_blackOverlay->AddComponent(new Sprite(pmath::Vec4(0, 0, 0, 1), pmath::Vec2(3500, 3500)));
	m_blackOverlay->transform.SetPosition(camera.GetPosition().x / 2,
										  camera.GetPosition().y / 2 - camera.GetSize().y / 2);

	return true;
}


// Update loop. Gone trought once per frame.
void GameScene::Update(float dt)
{

	if (dt > 0.1)
		dt = 0.1;

	auto& camera = uthEngine.GetWindow().GetCamera();

	if (m_blackOverlay->GetComponent<Sprite>()->GetColor().a > 0)
	{
		m_blackOverlay->transform.SetPosition(camera.GetPosition().x,
											  camera.GetPosition().y);
		m_blackOverlay->GetComponent<Sprite>()->SetColor(pmath::Vec4(0, 0, 0, m_blackOverlay->GetComponent<Sprite>()->GetColor().a - 0.5f*dt));
	}
	else
	{
		m_blackOverlay->SetActive(false);
	}
	

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
		ControlFunctions();

		if (Statistics.player.hp <= 0)
		{
			m_music->Stop();
			m_player->Die();
			if (!m_gameOverMusic->IsPlaying())
				m_gameOverMusic->Play();
			if (m_player->m_isDoneDying)
			{
				m_afterMathMusic->Play();
				m_afterMathMusic->Loop(true);
				isPlayerDead = true;
			}
		}

		m_pauseB->update(dt);
		if (m_pauseB->IsPressedS())
		{
			isPaused = true;	
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
			m_music->SetPitch(100 - m_soundSlowerTimer);
		}

		m_pauseMenu->SetActive(true);
		m_MenuButton->SetActive(true);
		m_RestartButton->SetActive(true);
		m_player->SetActive(false);
		

		m_pauseMenu->transform.SetPosition(camera.GetPosition().x - camera.GetSize().x / 3 + 50, camera.GetPosition().y - camera.GetSize().y / 2 );
		m_MenuButton->transform.SetPosition(camera.GetPosition().x - camera.GetSize().x / 3 + 120, camera.GetPosition().y - camera.GetSize().y / 2 + 525);
		m_RestartButton->transform.SetPosition(camera.GetPosition().x - camera.GetSize().x / 3 + 470, camera.GetPosition().y - camera.GetSize().y / 2 + 525);

	#ifdef UTH_SYSTEM_ANDROID
		//TODO: Android only pause functions here

	#else
		//PC only code here

	#endif
		//If user press m_pause button game resumes
		m_menuB->update(dt);
		m_restartB->update(dt);
		m_pauseB->update(dt);
		if (m_pauseB->IsPressedS())
		{
			m_pauseMenu->SetActive(false);
			m_MenuButton->SetActive(false);
			m_RestartButton->SetActive(false);
			m_player->SetActive(true);
			
			isPaused = false;
		}
		if (m_restartB->IsPressedS())
		{
			uthSceneM.GoToScene(GAME);
			m_music->Stop();
		}
		if (m_menuB->IsPressedS())
		{
			uthSceneM.GoToScene(TITLE);
			m_music->Stop();
		}
	}
	else if (!isPaused && isPlayerDead) //Game over functions here
	{
		m_gameOverScreenPicture->SetActive(true);
		m_MenuButton->SetActive(true);
		m_RestartButton->SetActive(true);
		m_health->update(dt);

		m_menuB->update(dt);
		m_restartB->update(dt);

		auto& camera = uthEngine.GetWindow().GetCamera();

		m_gameOverScreenPicture->transform.SetPosition(camera.GetPosition().x - camera.GetSize().x / 3 + 50, camera.GetPosition().y - camera.GetSize().y / 2);
		m_MenuButton->transform.SetPosition(camera.GetPosition().x - camera.GetSize().x / 3 + 120, camera.GetPosition().y - camera.GetSize().y /2 + 525);
		m_RestartButton->transform.SetPosition(camera.GetPosition().x - camera.GetSize().x / 3 + 470, camera.GetPosition().y - camera.GetSize().y /2 + 525);

		if (m_restartB->IsPressedS())
		{
			uthSceneM.GoToScene(GAME);
			m_afterMathMusic->Stop();
			Statistics.Save();
		}
		if (m_menuB->IsPressedS())
		{
			uthSceneM.GoToScene(TITLE);
			m_afterMathMusic->Stop();
			Statistics.Save();
		}
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
			if (BB->HasTag("Tank"))
			{
				BB->GetComponent<TankBehavior>()->Destroy();
				static_cast<Player*>(AA)->Hit(3);
			}
			else if (BB->HasTag("Soldier"))
			{
				if (static_cast<Player*>(AA)->m_isJumping)
				{
					//TODO: player gets health
				}

				BB->GetComponent<SoldierBehavior>()->Destroy();
			}
			else if (BB->HasTag("Aeroplane"))
			{
				//B->GetComponent<AeroplaneBehavior>()->Hit();
				//static_cast<Player*>(A)->Hit();
			}
			else if (BB->HasTag("Heli"))
			{
				if (static_cast<Player*>(AA)->m_isJumping)
				{
					static_cast<Heli*>(BB)->takeDamage(100);
				}
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
			if (A->HasTag("Aeroplane"))
			{
				BB = A;
				AA = B;
			}
			//Put Tag for every enemytype here
			if (AA->HasTag("Tank"))
			{
				if (AA->GetComponent<TankBehavior>()->isExploding())
				{
					AA->GetComponent<TankBehavior>()->Destroy();
					BB->GetComponent<AeroplaneBehavior>()->Hit();
				}
			}
			else if (AA->HasTag("Soldier"))
			{
				if (AA->GetComponent<SoldierBehavior>()->isExploding())
				{
					AA->GetComponent<SoldierBehavior>()->Destroy();
					BB->GetComponent<AeroplaneBehavior>()->Hit();
				}
			}
		}
		//When enemies are dying and are hitting Helicopter
		if (A->HasTag("Enemy") && B->HasTag("Heli") ||
			B->HasTag("Enemy") && A->HasTag("Heli"))
		{
			auto* AA = A;
			auto* BB = B;
			if (A->HasTag("Heli"))
			{
				BB = A;
				AA = B;
			}
			//Put Tag for every enemytype here
			if (AA->HasTag("Tank"))
			{
				if (AA->GetComponent<TankBehavior>()->isExploding())
				{
					AA->GetComponent<TankBehavior>()->Destroy();
					static_cast<Heli*>(BB)->takeDamage(100);
				}
			}
			else if (AA->HasTag("Soldier"))
			{
				if (AA->GetComponent<SoldierBehavior>()->isExploding())
				{
					AA->GetComponent<SoldierBehavior>()->Destroy();
					static_cast<Heli*>(BB)->takeDamage(35);
				}
			}
		}
		//TODO: make smarter soldier collides soldier functions
		//When enemies are dying and are hitting non dying enemies
		//if (A->HasTag("Enemy") && B->HasTag("Heli") ||
		//	B->HasTag("Enemy") && A->HasTag("Heli"))
		//{
		//	auto* AA = A;
		//	auto* BB = B;
		//	if (A->HasTag("Heli"))
		//	{
		//		BB = A;
		//		AA = B;
		//	}
		//	//Put Tag for every enemytype here
		//	if (AA->HasTag("Tank"))
		//	{
		//		if (AA->GetComponent<TankBehavior>()->isExploding())
		//		{
		//			AA->GetComponent<TankBehavior>()->Destroy();
		//			static_cast<Heli*>(BB)->takeDamage(100);
		//		}
		//	}
		//	else if (AA->HasTag("Soldier"))
		//	{
		//		if (AA->GetComponent<SoldierBehavior>()->isExploding())
		//		{
		//			AA->GetComponent<SoldierBehavior>()->Destroy();
		//			static_cast<Heli*>(BB)->takeDamage(35);
		//		}
		//	}
		//}

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

			if (AA->HasTag("Soldier"))
				AA->GetComponent<SoldierBehavior>()->TailWhipHit();
			else if (BB->HasTag("Soldier"))
				BB->GetComponent<SoldierBehavior>()->TailWhipHit();

		}
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