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

	m_bgs.push_back(new Background(backTex));
	m_bgs.push_back(new Background(backTex));
	m_bgs.push_back(new Background(frontTex));
	m_bgs.push_back(new Background(frontTex));
	m_bgs.push_back(new Background(mountTex));
	m_bgs.push_back(new Background(mountTex));

	m_bgs[0]->transform.SetPosition(-uthEngine.GetWindow().GetSize().x / 2, m_backSpawnY);
	m_bgs[1]->transform.SetPosition(m_bgs[0]->transform.GetPosition().x + m_bgs[0]->transform.GetSize().x, m_backSpawnY);
	m_bgs[2]->transform.SetPosition(-uthEngine.GetWindow().GetSize().x / 2, m_frontSpawnY);
	m_bgs[3]->transform.SetPosition(m_bgs[2]->transform.GetPosition().x + m_bgs[2]->transform.GetSize().x, m_frontSpawnY);
	m_bgs[4]->transform.SetPosition(-uthEngine.GetWindow().GetSize().x / 2, m_mountainSpawnY);
	m_bgs[5]->transform.SetPosition(m_bgs[4]->transform.GetPosition().x + m_bgs[4]->transform.GetSize().x, m_mountainSpawnY);

}
void BackgroundManager::Update(float dt)
{
	CameraMovement(dt);
	Movement(dt);
}
void BackgroundManager::CameraMovement(float dt)
{
	m_camera = &uthEngine.GetWindow().GetCamera();
	//Change direction depending where player is looking
	if (m_isTurned)
	{
		m_camera->SetPosition(m_cameraStartPos.x + 150, m_cameraStartPos.y);
	}
	else
	{
		m_camera->SetPosition(m_cameraStartPos.x - 150, m_cameraStartPos.y);
	}
}
void BackgroundManager::Movement(float dt)
{
	// Set speed relevant to direction where we are going 
	if (m_isTurned)
	{
		m_mountainSpeed = -(c_mountainSpeedM + m_playerSpeed)*dt;
		m_backSpeed = -(c_backSpeedM + m_playerSpeed)*dt;
		m_frontSpeed = -(c_frontSpeedM + m_playerSpeed)*dt;
	}
	else
	{
		m_mountainSpeed = (c_mountainSpeedM + m_playerSpeed)*dt;
		m_backSpeed = (c_backSpeedM + m_playerSpeed)*dt;
		m_frontSpeed = (c_frontSpeedM + m_playerSpeed)*dt;
	}
	// Make backgrounds move with given speed
	m_bgs[0]->transform.SetPosition(m_bgs[0]->transform.GetPosition().x + m_backSpeed, m_backSpawnY);
	m_bgs[1]->transform.SetPosition(m_bgs[1]->transform.GetPosition().x + m_backSpeed, m_backSpawnY);
	m_bgs[2]->transform.SetPosition(m_bgs[2]->transform.GetPosition().x + m_frontSpeed, m_frontSpawnY);
	m_bgs[3]->transform.SetPosition(m_bgs[3]->transform.GetPosition().x + m_frontSpeed, m_frontSpawnY);
	m_bgs[4]->transform.SetPosition(m_bgs[4]->transform.GetPosition().x + m_mountainSpeed, m_mountainSpawnY);
	m_bgs[5]->transform.SetPosition(m_bgs[5]->transform.GetPosition().x + m_mountainSpeed, m_mountainSpawnY);
	// Set screen bounds
	auto cameraLeftBound  = uthEngine.GetWindow().GetCamera().GetPosition().x - uthEngine.GetWindow().GetSize().x / 2;
	auto cameraRightBound = uthEngine.GetWindow().GetCamera().GetPosition().x + uthEngine.GetWindow().GetSize().x / 2;
	// Set references to variables for easier use
	auto& M1T = m_bgs[4]->transform;  auto& B1T = m_bgs[2]->transform;  auto& F1T = m_bgs[0]->transform;
	auto& M2T = m_bgs[5]->transform;  auto& B2T = m_bgs[3]->transform;  auto& F2T = m_bgs[1]->transform;
	// Looping method
	for (int i = 0; i < m_bgs.size(); ++i)
	{
		if (m_isTurned) // Is player going right
		{
			m_xBound = cameraLeftBound;
			if ((i % 2) == 0)
			{
				auto& A = m_bgs[i]->transform;
				auto& B = m_bgs[i + 1]->transform;
				if (A.GetPosition().x <= m_xBound - A.GetSize().x)
				{
					A.SetPosition(B.GetPosition().x + B.GetSize().x, m_mountainSpawnY);
				}
				if (B.GetPosition().x <= m_xBound - B.GetSize().x)
				{
					B.SetPosition(A.GetPosition().x + A.GetSize().x, m_mountainSpawnY);
				}
			}
		}
		else // Is player going left
		{
			m_xBound = cameraRightBound;
			if ((i % 2) == 0)
			{
				auto& A = m_bgs[i]->transform;
				auto& B = m_bgs[i + 1]->transform;
				if (A.GetPosition().x >= m_xBound)
				{
					A.SetPosition(B.GetPosition().x - B.GetSize().x, m_mountainSpawnY);
				}
				if (B.GetPosition().x >= m_xBound)
				{
					B.SetPosition(A.GetPosition().x - A.GetSize().x, m_mountainSpawnY);
				}
			}
				
		}
	}
}
void BackgroundManager::DrawFront()
{
	m_bgs[2]->Draw();//Frontcity
	m_bgs[3]->Draw();
}
void BackgroundManager::DrawBack()
{
	m_bgs[4]->Draw();//Mountain
	m_bgs[5]->Draw();
	m_bgs[0]->Draw();//Backcity
	m_bgs[1]->Draw();
}
void BackgroundManager::ChangeDirection()
{
	m_isTurned = !m_isTurned;
}
void BackgroundManager::CheckSpeed(float speed)
{
	m_playerSpeed = speed;
}
void BackgroundManager::SetCameraStartPos(pmath::Vec2 pos)
{
	uthEngine.GetWindow().GetCamera().SetPosition(pos);
	m_cameraStartPos = pos;
}
// Deconstructor
BackgroundManager::~BackgroundManager()
{
}