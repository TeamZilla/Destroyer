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
	m_bgManager.Update(dt);
	m_player.Update(dt);
	m_health.Update(dt);
	m_heli->Update(dt);

	if (uthInput.Keyboard.IsKeyDown(Keyboard::Space) || uthInput.Common.Event() == uth::InputEvent::TAP)
	{
		m_bgManager.ChangeDirection();
		m_player.ChangeDirection();
		m_health.TakeDamage(1);
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Up))
	{

	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Down))
	{

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