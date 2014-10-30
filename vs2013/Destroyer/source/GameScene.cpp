#include <GameScene.hpp>
#include <ExplosionEmitter.hpp>
//When you want debug, use WriteLog(...), works like printf.

using namespace uth;

uth::Layer& GameScene::getLayer(LayerId id)
{
	return *m_layers[id];
}

// Main initialisation.
// Automatically called inside SceneManager.
bool GameScene::Init()
{
	Randomizer::SetSeed();
	uthEngine.GetWindow().GetCamera().SetSize(1280, 720);
	
	m_enemyManager->SetPhysWorld(&m_physWorld);
	m_gameFloor.AddComponent(new Sprite(pmath::Vec4(1, 0, 0, 1), pmath::Vec2(3000, 80)));
	m_gameFloor.transform.SetPosition(0, uthEngine.GetWindow().GetSize().y);
	m_gameFloor.AddComponent(new Rigidbody(m_physWorld));
	m_gameFloor.GetComponent<Rigidbody>("Rigidbody")->SetKinematic(true);


	m_bgManager.Init(getLayer(LayerId::Background), getLayer(LayerId::Foreground));

	//m_heli = new Heli(pmath::Vec2f(0, 0));
	getLayer(LayerId::InGame).AddChild(m_road = new Road(160));
	getLayer(LayerId::InGame).AddChild(m_player = new Player);
	getLayer(LayerId::InGame).AddChild(m_heli = new Heli(pmath::Vec2f(0, 0)));

	getLayer(LayerId::Userinterface).AddChild(m_health = new Health);

	m_road->Init(m_player);

	//aeroplaneTimer = 0;
	//aeroMinSpawnTime = 0.5;
	//aeroMaxSpawnTime = 6;
	//isCool = 1;

	m_bgManager.SetCameraStartPos(pmath::Vec2f(0, uthEngine.GetWindow().GetSize().y/2));
	//TODO: Initialisation functions
	

	//SOUNDTEST START

	m_music = uthRS.LoadSound("Audio/Music/city_theme2.wav");
	m_music->Play();
	m_music->Loop(true);

	//ParticleInit();
	ExplosionEmitter::Init(&getLayer(LayerId::Foreground));

	return true;
}


// Update loop. Gone trought once per frame.
void GameScene::Update(float dt)
{
	static int count;
	static float time = 0;
	time += dt;
	count++;
	if (time > 1)
	{
		time -= 1;
		std::cout << count << "\t" << m_layers[LayerId::InGame]->m_children.size() << std::endl;
		count = 0;
	}

	//TODO: Update functions
	m_physWorld.Update(dt);
	//m_bgManager.CheckSpeed(m_player->getSpeed(), m_player->CheckIfGoingRight());
	m_bgManager.Update(dt);

	Scene::Update(dt);
	//dt *= 20;

	m_enemyManager->Update(dt);
	m_enemyManager->CheckPlayer(m_player);
	//m_enemyManager->SpawnTanks(dt);
	//m_player->Update(dt);
	//m_health->Update(dt);
	m_heli->Update(dt);
	//m_enemyManger(dt);

	//for (int i = 0; i < m_aeroplane.size(); i++)
	//{
	//	m_aeroplane[i]->Update(dt);
	//}
	

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
		m_health->TakeDamage(1);
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Up))
	{
		if (!m_player->m_isCrouching && !m_player->m_isJumping)
			m_player->Jump();
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Down))
	{
		if (!m_player->m_isJumping && !m_player->m_isCrouching)
		{
			m_player->Crouch();
			//              amount , delay
			//m_bgManager.Shake(5, 0.4f);
			m_enemyManager->DestroyTanks();
			m_enemyManager->DestroySoldiers();
		}
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Left))
	{
		if (m_player->CheckIfGoingRight())
		{
			m_player->ChangeDirection();
		}
	}
	
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Right))
	{
		if (!m_player->CheckIfGoingRight())
		{
			m_player->ChangeDirection();
		}
	}


	if (uthInput.Keyboard.IsKeyDown(uth::Keyboard::R))
	{
		m_road->Shock();
	}


#endif
	//return true; // Update succeeded.
}

// Draw loop. All graphics are drawn during this loop.
//bool GameScene::Draw()
//{
//	//TODO: Draw functions
//
//	m_spriteBatch.Draw(uthEngine.GetWindow());
//	m_bgManager.DrawBack();
//
//	m_player.Draw();
//	m_heli->Draw();
//	m_enemyManager.Draw();
//
//	for (int i = 0; i < m_aeroplane.size(); i++)
//	{
//		m_aeroplane[i]->Draw();
//	}
//
//
//
//	m_bgManager.DrawFront();
//	m_health.Draw();
//	return true; // Drawing succeeded.
//}


void GameScene::m_enemyManger(float m_dt)
{
	//m_heli->Update(m_dt);

	//if (isCool)
	//{
	//	shootTime = Randomizer::GetFloat(aeroMinSpawnTime, aeroMaxSpawnTime);
	//	isCool = false;
	//}

	//if (aeroplaneTimer > shootTime )
	//{

	//	rand = Randomizer::GetInt(0, 2);


	//	if (rand == 0)
	//	{
	//		m_aeroplane.push_back(new Aeroplane(-1800));
	//		aeroplaneTimer = 0;
	//		isCool = true;
	//	}

	//	else
	//	
	//	{
	//		m_aeroplane.push_back(new Aeroplane(1800));
	//		aeroplaneTimer = 0;
	//		isCool = true;
	//	}
	//}

	//aeroplaneTimer += m_dt;

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

	auto & l = getLayer(LayerId::InGame);
	m_enemyManager = new EnemyManager(l);
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