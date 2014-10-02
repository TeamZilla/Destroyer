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
	m_heli = new Heli(pmath::Vec2f(0, 0));
	m_bgManager.SetCameraStartPos(uthEngine.GetWindow().GetSize() / 2);
	//TODO: Initialisation functions
	
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
	m_heli->Update(dt);

	if (uthInput.Common.Event() == uth::InputEvent::TAP)
	{
		m_health.TakeDamage(1);
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Up) || uthInput.Common.Event() == uth::InputEvent::ZOOM_OUT)
	{
		m_player.Jump();
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Down) || uthInput.Common.Event() == uth::InputEvent::ZOOM_IN)
	{
		m_player.Crouch();
		//              amount , delay
		m_bgManager.Shake(5,0.4f);
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Left) || uthInput.Common.Event() == uth::InputEvent::DRAG)
	{
		if (m_player.CheckIfGoingRight())
		{
			m_player.ChangeDirection();
		}
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Right) || uthInput.Common.Event() == uth::InputEvent::DRAG)
	{
		if (!m_player.CheckIfGoingRight())
		{
			m_player.ChangeDirection();
		}
	}
	
	return true; // Update succeeded.
}

// Draw loop. All graphics are drawn during this loop.
bool GameScene::Draw()
{
	//TODO: Draw functions

	m_bgManager.DrawBack();

	m_player.Draw();
	m_heli->Draw();
	m_bgManager.DrawFront();
	m_health.Draw();
	return true; // Drawing succeeded.
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