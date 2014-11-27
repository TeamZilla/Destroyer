#include <GameScene.hpp>
#include <ExplosionEmitter.hpp>
#include <FlameEmitter.hpp>

#include <EnemyFactory.hpp>
#include <TankBehavior.hpp>
#include <SoldierBehavior.hpp>
#include <AeroplaneBehavior.hpp>
#include <FireBreath.hpp>

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
	
	m_gameFloor.AddComponent(new Sprite(pmath::Vec4(1, 0, 0, 1), pmath::Vec2(3000, 100)));
	m_gameFloor.AddTag("Floor");
	m_gameFloor.transform.SetPosition(0, uthEngine.GetWindow().GetSize().y);
	m_gameFloor.AddComponent(new Rigidbody(m_physWorld));
	m_gameFloor.GetComponent<Rigidbody>()->SetKinematic(true);

	m_bgManager.Init(getLayer(LayerId::Background), getLayer(LayerId::Foreground));

	//m_heli = new Heli(pmath::Vec2f(0, 0));
	//getLayer(LayerId::InGame).AddChild(&m_gameFloor);
	getLayer(LayerId::InGame).AddChild(m_road = new Road(225));
	getLayer(LayerId::InGame).AddChild(m_player = new Player(&m_physWorld));
	getLayer(LayerId::Userinterface).AddChild(m_health = new Health);
	m_player->init(&m_physWorld, m_health);
	getLayer(LayerId::InGame).AddChild(m_heli = new Heli(pmath::Vec2f(0, 0),m_player));


	m_road->Init(m_player,&m_physWorld);
	
	m_bgManager.SetCameraStartPos(pmath::Vec2f(0, uthEngine.GetWindow().GetSize().y/2));
	

	m_music = uthRS.LoadSound("Audio/Music/city_theme3.wav");
	m_music->Play();
	m_music->Loop(true);

	m_waveSound = uthRS.LoadSound("Audio/Effects/Explosion1.wav");
	//m_waveSound->SetVolume(10);

	//ParticleInit();
	ExplosionEmitter::Init(&getLayer(LayerId::Foreground));
	FlameEmitter::Init(&getLayer(LayerId::Foreground));

	EnemyFactory::Init(&getLayer(LayerId::InGame),&m_physWorld,m_player);
	//EnemyFactory::CreateTank();

	colliderChecks();
	isPaused = false;

	return true;
}


// Update loop. Gone trought once per frame.
void GameScene::Update(float dt)
{
	if (!isPaused)
	{
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
		//dt *= 20;

		m_heli->Update(dt);


#ifdef UTH_SYSTEM_ANDROID

		const auto& wnd = uthEngine.GetWindow();
		const pmath::Vec2& touchStart = wnd.PixelToCoords(uthInput.Touch[0].GetStartPosition());
		const pmath::Vec2& touchEnd = wnd.PixelToCoords(uthInput.Touch[0].GetEndPosition());

		if (uthInput.Touch.Motion() == TouchMotion::TAP)
		{
			m_health->TakeDamage(1);
		}

		if(uthInput.Touch.Motion() == TouchMotion::DRAG)
		{
			if (touchStart.y - 80 > touchEnd.y + 80)
			{
				if (!m_player.m_isCrouching)
				{
					m_player->Jump();
				}
			}
			else if (touchStart.y + 80 < touchEnd.y - 80)
			{
				if (!m_player.m_isJumping)
				{
					m_player->Crouch();
					m_bgManager.Shake(5, 0.4f); // Amount, Delay
				}
			}

			if (touchStart.x + 90 > touchEnd.x - 90)
			{
				if (m_player->CheckIfGoingRight())
				{
					m_player->ChangeDirection();
				}
			}
			else if (touchStart.x - 90 < touchEnd.x + 90)
			{
				if (!m_player->CheckIfGoingRight())
				{
					m_player->ChangeDirection();
				}
			}
		}


#else
		if (uthInput.Common.Event() == uth::InputEvent::TAP)
		{
			//m_health->TakeDamage(1);
			m_player->Hit();
		}
		if (uthInput.Keyboard.IsKeyDown(Keyboard::Up))
		{
			if (!m_player->m_isCrouching && !m_player->m_isJumping)
				m_player->Jump();
		}
		if (uthInput.Keyboard.IsKeyDown(Keyboard::Down))
		{
			if (!m_player->m_isJumping && !m_player->m_isCrouching && !m_player->m_isTurning)
			{
				m_player->Crouch();
				isInitedShake = true;
			}
		}
		if (uthInput.Keyboard.IsKeyDown(Keyboard::Left) &&
			!uthInput.Keyboard.IsKeyDown(Keyboard::Right))
		{
			if (m_player->CheckIfGoingRight())
			{
				m_player->ChangeDirection();
			}
		}

		if (uthInput.Keyboard.IsKeyDown(Keyboard::Right) &&
			!uthInput.Keyboard.IsKeyDown(Keyboard::Left))
		{
			if (!m_player->CheckIfGoingRight())
			{
				m_player->ChangeDirection();
			}
		}

		if (uthInput.Mouse.IsButtonReleased(Mouse::LEFT))
		{
			FlameEmitter::Emit(uthInput.Mouse.Position());
			getLayer(LayerId::InGame).AddChild(new FireBreath(pmath::Vec2(0, 280), uthInput.Mouse.Position()));
		}

		if (uthInput.Keyboard.IsKeyDown(Keyboard::P))
		{
			isPaused = true;
		}
	}
	else //TODO:: Pause menu stuff here
	{
		if (uthInput.Keyboard.IsKeyDown(Keyboard::O))
		{
			isPaused = false;
		}
	}

#endif
	//return true; // Update succeeded.
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
				static_cast<Player*>(A)->Hit();
			}
			else if (B->HasTag("Soldier"))
			{
				B->GetComponent<SoldierBehavior>()->Destroy();
				static_cast<Player*>(A)->Hit();
			}
			else if (B->HasTag("Aeroplane"))
			{
				B->GetComponent<AeroplaneBehavior>()->Hit();
				static_cast<Player*>(A)->Hit();
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
		uthEngine.GetWindow().GetSize().y - 470,
		uthEngine.GetWindow().GetSize().y - 220,
		uthEngine.GetWindow().GetSize().y - 570
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