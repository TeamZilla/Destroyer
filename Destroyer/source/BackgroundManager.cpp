#include <BackgroundManager.hpp>

using namespace uth;

BackgroundManager::BackgroundManager(float bY, float fY, float mY)
	:m_backSpawnY(bY),
	m_frontSpawnY(fY),
	m_mountainSpawnY(mY)
{
	m_playerSpeed = 0;
	m_backSpeed = 0;
	m_frontSpeed = 0;
	m_mountainSpeed = 0;
	m_isTurned = true;
	m_isTurning = false;
	m_xBound = 0;

	//Set textures
	auto backTex  = uthRS.LoadTexture("backgrounds/buildings.png");
	auto frontTex = uthRS.LoadTexture("backgrounds/lamps.png");
	auto mountTex = uthRS.LoadTexture("backgrounds/mountain.png");

	//Put city background in place
	m_back_1 = new Background(backTex);
	m_back_1->transform.SetPosition(
		-uthEngine.GetWindow().GetSize().x / 2, m_backSpawnY);
	m_back_2 = new Background(backTex);
	m_back_2->transform.SetPosition(
		m_back_1->transform.GetPosition().x + m_back_1->transform.GetSize().x, m_backSpawnY);

	//Put front background in place
	m_front_1 = new Background(frontTex);
	m_front_1->transform.SetPosition(
		-uthEngine.GetWindow().GetSize().x / 2, m_frontSpawnY);
	m_front_2 = new Background(frontTex);
	m_front_2->transform.SetPosition(
		m_front_1->transform.GetPosition().x + m_front_1->transform.GetSize().x, m_frontSpawnY);

	//Put mountain background in place
	m_mountain_1 = new Background(mountTex);
	m_mountain_1->transform.SetPosition(
		-uthEngine.GetWindow().GetSize().x / 2, m_mountainSpawnY);
	m_mountain_2 = new Background(mountTex);
	m_mountain_2->transform.SetPosition(
		m_mountain_1->transform.GetPosition().x + m_mountain_1->transform.GetSize().x, m_mountainSpawnY);
}
void BackgroundManager::Update(float dt)
{
	if (uthInput.Keyboard.IsKeyDown(Keyboard::Space) || uthInput.Common.Event() == uth::InputEvent::TAP)
	{
		m_isTurned = !m_isTurned;
	}
	GoLeft(dt);
}
void BackgroundManager::GoLeft(float dt)
{
	// Mountain movement
	if (m_isTurned)
		m_mountainSpeed = -(c_mountainSpeedM + m_playerSpeed)*dt;
	else
		m_mountainSpeed = (c_mountainSpeedM + m_playerSpeed)*dt;

	m_mountain_1->transform.SetPosition(
		m_mountain_1->transform.GetPosition().x + m_mountainSpeed, m_mountainSpawnY);
	m_mountain_2->transform.SetPosition(
		m_mountain_2->transform.GetPosition().x + m_mountainSpeed, m_mountainSpawnY);
	// Back city movement
	if (m_isTurned)
		m_backSpeed = -(c_backSpeedM + m_playerSpeed)*dt;
	else
		m_backSpeed = (c_backSpeedM + m_playerSpeed)*dt;
	m_back_1->transform.SetPosition(
		m_back_1->transform.GetPosition().x + m_backSpeed, m_backSpawnY);
	m_back_2->transform.SetPosition(
		m_back_2->transform.GetPosition().x + m_backSpeed, m_backSpawnY);
	// Front city movement
	if (m_isTurned)
		m_frontSpeed = -(c_frontSpeedM + m_playerSpeed)*dt;
	else
		m_frontSpeed = (c_frontSpeedM + m_playerSpeed)*dt;
	m_front_1->transform.SetPosition(
		m_front_1->transform.GetPosition().x + m_frontSpeed, m_frontSpawnY);
	m_front_2->transform.SetPosition(
		m_front_2->transform.GetPosition().x + m_frontSpeed, m_frontSpawnY);

	auto cameraLeftBound = uthEngine.GetWindow().GetCamera().GetPosition().x - uthEngine.GetWindow().GetSize().x / 2;
	auto cameraRightBound = uthEngine.GetWindow().GetCamera().GetPosition().x + uthEngine.GetWindow().GetSize().x / 2;
	if (m_isTurned)
		m_xBound = cameraLeftBound;
	else
		m_xBound = cameraRightBound;

	auto& M1T = m_mountain_1->transform;  auto& B1T = m_back_1->transform;  auto& F1T = m_front_1->transform;
	auto& M2T = m_mountain_2->transform;  auto& B2T = m_back_2->transform;  auto& F2T = m_front_2->transform;
	// Mountain looping method
	if (m_isTurned)
	{
		if (M1T.GetPosition().x <= m_xBound - M1T.GetSize().x)
		{
			M1T.SetPosition(M2T.GetPosition().x + M2T.GetSize().x, m_mountainSpawnY);
		}
		if (M2T.GetPosition().x <= m_xBound - M2T.GetSize().x)
		{
			M2T.SetPosition(M1T.GetPosition().x + M1T.GetSize().x, m_mountainSpawnY);
		}
	}
	else
	{
		if (M1T.GetPosition().x >= m_xBound)
		{
			M1T.SetPosition(M2T.GetPosition().x - M2T.GetSize().x, m_mountainSpawnY);
		}
		if (M2T.GetPosition().x >= m_xBound)
		{
			M2T.SetPosition(M1T.GetPosition().x - M1T.GetSize().x, m_mountainSpawnY);
		}
	}
	// Front city looping method
	if (m_isTurned)
	{
		if (F1T.GetPosition().x <= m_xBound - F1T.GetSize().x)
		{
			F1T.SetPosition(F2T.GetPosition().x + F2T.GetSize().x, m_frontSpawnY);
		}
		if (F2T.GetPosition().x <= m_xBound - F2T.GetSize().x)
		{
			F2T.SetPosition(F1T.GetPosition().x + F1T.GetSize().x, m_frontSpawnY);
		}
	}
	else
	{
		if (F1T.GetPosition().x >= m_xBound)
		{
			F1T.SetPosition(F2T.GetPosition().x - F2T.GetSize().x, m_frontSpawnY);
		}
		if (F2T.GetPosition().x >= m_xBound)
		{
			F2T.SetPosition(F1T.GetPosition().x - F1T.GetSize().x, m_frontSpawnY);
		}
	}
	// Back city looping method
	if (m_isTurned)
	{
		if (B1T.GetPosition().x <= m_xBound - B1T.GetSize().x)
		{
			B1T.SetPosition(B2T.GetPosition().x + B2T.GetSize().x, m_backSpawnY);
		}
		if (B2T.GetPosition().x <= m_xBound - B2T.GetSize().x)
		{
			B2T.SetPosition(B1T.GetPosition().x + B1T.GetSize().x, m_backSpawnY);
		}
	}
	else
	{
		if (B1T.GetPosition().x >= m_xBound)
		{
			B1T.SetPosition(B2T.GetPosition().x - B2T.GetSize().x, m_frontSpawnY);
		}
		if (B2T.GetPosition().x >= m_xBound)
		{
			B2T.SetPosition(B1T.GetPosition().x - B1T.GetSize().x, m_frontSpawnY);
		}
	}

}
void BackgroundManager::Turning(float dt)
{
	
}
void BackgroundManager::DrawFront()
{
	m_front_1->Draw();
	m_front_2->Draw();
}
void BackgroundManager::DrawBack()
{
	m_mountain_1->Draw();
	m_mountain_2->Draw();
	m_back_1->Draw();
	m_back_2->Draw();
}
void BackgroundManager::ChangeDirection()
{
	m_isTurned = !m_isTurned;
}
void BackgroundManager::CheckSpeed(float speed)
{
	m_playerSpeed = speed;
}
// Deconstructor
BackgroundManager::~BackgroundManager()
{
}