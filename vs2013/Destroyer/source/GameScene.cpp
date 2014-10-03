#include <GameScene.hpp>
//When you want debug, use WriteLog(...), works like printf.

using namespace uth;

// Main initialisation.
// Automatically called inside SceneManager.
bool GameScene::Init()
{
	// Some shader must be loaded and set window to use it
 	m_shader.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	m_shader.Use();
	uthEngine.GetWindow().SetShader(&m_shader);

	Camera& camera = uthEngine.GetWindow().GetCamera();
	camera.SetSize(1280, 720);
	

	m_heli = new Heli(pmath::Vec2f(0, 0));
	m_tank = new Tank(pmath::Vec2(0, 0));

	aeroplaneTimer = 0;
	aeroMinSpawnTime = 0.5;
	aeroMaxSpawnTime = 20;
	isCool = 1;


	m_bgManager.SetCameraStartPos(pmath::Vec2f(0, uthEngine.GetWindow().GetSize().y/2));
	//TODO: Initialisation functions
	

	//SOUNDTEST START

	m_music = uth::Sound::Load("Audio/Music/city_theme.wav");
	m_music->Play();
	m_music->Loop(true);

	return true;
}


// Update loop. Gone trought once per frame.
bool GameScene::Update(float dt)
{
	//TODO: Update functions
	m_bgManager.CheckSpeed(m_player.getSpeed(), m_player.CheckIfGoingRight());
	m_bgManager.Update(dt);
	m_player.Update(dt);
	m_health.Update(dt);
	m_enemyManger(dt);



	for (int i = 0; i < m_aeroplane.size(); i++)
	{
		m_aeroplane[i]->Update(dt);
	}
	

#ifdef UTH_SYSTEM_ANDROID

	const auto& wnd = uthEngine.GetWindow();
	const pmath::Vec2& touchStart = wnd.PixelToCoords(uthInput.Touch[0].GetStartPosition());
	const pmath::Vec2& touchEnd = wnd.PixelToCoords(uthInput.Touch[0].GetEndPosition());

	if (uthInput.Touch.Motion() == TouchMotion::TAP)
	{
		m_health.TakeDamage(1);
	}

	if(uthInput.Touch.Motion() == TouchMotion::DRAG)
	{
		if (touchStart.y - 80 > touchEnd.y + 80)
		{
			if (!m_player.m_isCrouching)
			{
				m_player.Jump();
			}
		}
		else if (touchStart.y + 80 < touchEnd.y - 80)
		{
			if (!m_player.m_isJumping)
			{
				m_player.Crouch();
				m_bgManager.Shake(5, 0.4f); // Amount, Delay
			}
		}

		if (touchStart.x + 90 > touchEnd.x - 90)
		{
			if (m_player.CheckIfGoingRight())
			{
				m_player.ChangeDirection();
			}
		}
		else if (touchStart.x - 90 < touchEnd.x + 90)
		{
			if (!m_player.CheckIfGoingRight())
			{
				m_player.ChangeDirection();
			}
		}
	}

	
#else
	if (uthInput.Common.Event() == uth::InputEvent::TAP)
	{
		m_health.TakeDamage(1);
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Up))
	{
		if (!m_player.m_isCrouching)
			m_player.Jump();
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Down))
	{
		if (!m_player.m_isJumping)
		{
			m_player.Crouch();
			//              amount , delay
			m_bgManager.Shake(5, 0.4f);
		}
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Left))
	{
		if (m_player.CheckIfGoingRight())
		{
			m_player.ChangeDirection();
		}
	}
	
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Right))
	{
		if (!m_player.CheckIfGoingRight())
		{
			m_player.ChangeDirection();
		}
	}
#endif
	return true; // Update succeeded.
}

// Draw loop. All graphics are drawn during this loop.
bool GameScene::Draw()
{
	//TODO: Draw functions

	m_bgManager.DrawBack();

	m_player.Draw();
	m_heli->Draw();
	m_tank->Draw();


	for (int i = 0; i < m_aeroplane.size(); i++)
	{
		m_aeroplane[i]->Draw();
	}


	m_bgManager.DrawFront();
	m_health.Draw();
	return true; // Drawing succeeded.
}


void GameScene::m_enemyManger(float m_dt)
{
	m_heli->Update(m_dt);


	if (isCool)
	{
		shootTime = Randomizer::GetFloat(aeroMinSpawnTime, aeroMaxSpawnTime);
		isCool = false;
	}

	if (aeroplaneTimer > shootTime )
	{

		rand = Randomizer::GetInt(0, 2);


		if (rand == 0)
		{
			m_aeroplane.push_back(new Aeroplane(-1800));
			aeroplaneTimer = 0;
			std::cout << "New aeroplane added left" << std::endl;
			isCool = true;
		}

		else
		
		{
			m_aeroplane.push_back(new Aeroplane(1800));
			aeroplaneTimer = 0;
			std::cout << "New aeroplane added right" << std::endl;
			isCool = true;
		}
	}

	aeroplaneTimer += m_dt;

}

//Default constructor for initialising constant variables.
GameScene::GameScene()
	: m_bgManager(250,500,150)
{

}
//Default deconstrutor.
GameScene::~GameScene()
{

}

// Main deinitialisation.
// Automatically called inside SceneManager.
bool GameScene::DeInit()
{
	return true;
}