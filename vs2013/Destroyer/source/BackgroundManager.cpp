#include <BackgroundManager.hpp>
#include <Player.hpp>

using namespace uth;

BackgroundManager::BackgroundManager(float bY, float fY, float mY)
{

}
bool BackgroundManager::Init(uth::Layer& bg, uth::Layer& fg)
{
	//m_playerSpeed = 0;
	//m_backSpeed = 0;
	//m_frontSpeed = 0;
	//m_mountainSpeed = 0;
	//m_isTurned = true;
	//m_isTurning = false;
	//m_xBound = 0;
	m_cameraPan = 0;
	m_cameraPanMax = 300;
	m_cameraPanSpd = 5;
	m_isCameraTurning = false;
	//m_isShaking = false;

	// Background
	GameObject* temp;
	//Mountains
	bg.AddChild(temp = new GameObject(std::vector<std::string>{ "bg", "mountain1" }));
	temp->AddComponent(new Background(0.02,
		uthEngine.GetWindow().GetSize().y - 570, 0.5, true,
		"backgrounds/mountains01.png"));
	bg.AddChild(temp = new GameObject(std::vector<std::string>{ "bg", "mountain2" }));
	temp->AddComponent(new Background(0.02,
		uthEngine.GetWindow().GetSize().y - 570, 0.5, false,
		"backgrounds/mountains02.png"));
	//Backcity
	bg.AddChild(temp = new GameObject(std::vector<std::string>{ "bg", "building1" }));
	temp->AddComponent(new Background(50,
		uthEngine.GetWindow().GetSize().y - 470, 2,true, 
		"backgrounds/buildings02.png"));
	bg.AddChild(temp = new GameObject(std::vector<std::string>{ "bg", "building2" }));
	temp->AddComponent(new Background(50,
		uthEngine.GetWindow().GetSize().y - 470, 2, false,
		"backgrounds/buildings02.png"));
	//Frontcity
	fg.AddChild(temp = new GameObject(std::vector<std::string>{ "bg", "lantern1" }));
	temp->AddComponent(new Background(100,
		uthEngine.GetWindow().GetSize().y - 220, 4, true,
		"backgrounds/lanterns.png"));
	fg.AddChild(temp = new GameObject(std::vector<std::string>{ "bg", "lantern2" }));
	temp->AddComponent(new Background(100,
		uthEngine.GetWindow().GetSize().y - 220, 4, false,
		"backgrounds/lanterns.png"));
	
	return true;
}
void BackgroundManager::Update(float dt)
{
	CameraMovement(dt);

	//Movement(dt);
	//if (m_isShaking)
	//{
	//	m_shakeDelay -= dt;
	//	if (m_shakeDelay <= 0)
	//	{
	//		ParallerShake(dt);
	//	}
	//}
}
void BackgroundManager::CameraMovement(float dt)
{
	m_camera = &uthEngine.GetWindow().GetCamera();
	m_camera->SetPosition(m_cameraPan, m_cameraStartPos.y);
	if (!m_isCameraTurning)
	{
		m_isCameraTurning = true;
		m_cameraPan = 0;
	}
	//Change direction depending where player is looking
	if (Player::isGoingRight)
	{
		m_cameraPan += dt*m_cameraPanSpd * ((m_cameraStartPos.x + m_cameraPanMax) - m_camera->GetPosition().x);
	}
	else
	{
		m_cameraPan += dt*m_cameraPanSpd * ((m_cameraStartPos.x - m_cameraPanMax) - m_camera->GetPosition().x);
	}
}
void BackgroundManager::SetCameraStartPos(pmath::Vec2 pos)
{
	m_cameraStartPos = pos;
	uthEngine.GetWindow().GetCamera().SetPosition(pos);
}
BackgroundManager::~BackgroundManager()
{
	DeInit();
}

void BackgroundManager::DeInit()
{
	//for (auto& e : m_bgs)
	//{
	//	//delete e;
	//}
	//m_bgs.clear();

	//for (auto& e : m_bgPos)
	//{
	//	delete e;
	//}
	//m_bgPos.clear();

}
//void BackgroundManager::Movement(float dt)
//{
//	// Set speed relevant to direction where we are going 
//	if (m_isTurned)
//	{
//		m_mountainSpeed = -(c_mountainSpeedM + m_playerSpeed/10)*dt;
//		m_backSpeed = -(c_backSpeedM + m_playerSpeed/3)*dt;
//		m_frontSpeed = -(c_frontSpeedM + m_playerSpeed)*dt;
//	}
//	else
//	{
//		m_mountainSpeed = (c_mountainSpeedM + m_playerSpeed/10)*dt;
//		m_backSpeed = (c_backSpeedM + m_playerSpeed/3)*dt;
//		m_frontSpeed = (c_frontSpeedM + m_playerSpeed)*dt;
//	}
//	// Make backgrounds move with given speed
//	m_bgs[0]->transform.SetPosition(m_bgs[0]->transform.GetPosition().x + m_mountainSpeed, m_mountainSpawnY);
//	m_bgs[1]->transform.SetPosition(m_bgs[1]->transform.GetPosition().x + m_mountainSpeed, m_mountainSpawnY);
//	m_bgs[2]->transform.SetPosition(m_bgs[2]->transform.GetPosition().x + m_backSpeed, m_backSpawnY);
//	m_bgs[3]->transform.SetPosition(m_bgs[3]->transform.GetPosition().x + m_backSpeed, m_backSpawnY);
//	m_bgs[4]->transform.SetPosition(m_bgs[4]->transform.GetPosition().x + m_frontSpeed, m_frontSpawnY);
//	m_bgs[5]->transform.SetPosition(m_bgs[5]->transform.GetPosition().x + m_frontSpeed, m_frontSpawnY);
//	
//	// Set screen bounds
//	auto cameraLeftBound  = uthEngine.GetWindow().GetCamera().GetPosition().x - uthEngine.GetWindow().GetSize().x / 2;
//	auto cameraRightBound = uthEngine.GetWindow().GetCamera().GetPosition().x + uthEngine.GetWindow().GetSize().x / 2;
//	// Set references to variables for easier use
//	auto& M1T = m_bgs[0]->transform;  auto& B1T = m_bgs[4]->transform;  auto& F1T = m_bgs[2]->transform;
//	auto& M2T = m_bgs[1]->transform;  auto& B2T = m_bgs[5]->transform;  auto& F2T = m_bgs[3]->transform;
//	// Looping method
//	for (int i = 0; i < m_bgs.size(); ++i)
//	{
//		if (m_isTurned) // Is player going right
//		{
//			m_xBound = cameraLeftBound;
//			if ((i % 2) == 0)
//			{
//				auto& A = m_bgs[i]->transform;
//				auto& B = m_bgs[i + 1]->transform;
//				if (A.GetPosition().x <= m_xBound - A.GetSize().x)
//				{
//					A.SetPosition(B.GetPosition().x + B.GetSize().x, m_mountainSpawnY);
//				}
//				if (B.GetPosition().x <= m_xBound - B.GetSize().x)
//				{
//					B.SetPosition(A.GetPosition().x + A.GetSize().x, m_mountainSpawnY);
//				}
//			}
//		}
//		else // Is player going left
//		{
//			m_xBound = cameraRightBound;
//			if ((i % 2) == 0)
//			{
//				auto& A = m_bgs[i]->transform;
//				auto& B = m_bgs[i + 1]->transform;
//				if (A.GetPosition().x >= m_xBound)
//				{
//					A.SetPosition(B.GetPosition().x - B.GetSize().x, m_mountainSpawnY);
//				}
//				if (B.GetPosition().x >= m_xBound)
//				{
//					B.SetPosition(A.GetPosition().x - A.GetSize().x, m_mountainSpawnY);
//				}
//			}
//				
//		}
//	}
//}
//void BackgroundManager::DrawFront()
//{
//	//m_bgs[2]->Draw();//Frontcity
//	//m_bgs[3]->Draw();
//}
//void BackgroundManager::DrawBack()
//{
//	//m_bgs[4]->Draw();//Mountain
//	//m_bgs[5]->Draw();
//	//m_bgs[0]->Draw();//Backcity
//	//m_bgs[1]->Draw();
//}
//void BackgroundManager::ChangeDirection()
//{
//	m_isTurned = !m_isTurned;
//}
//void BackgroundManager::CheckSpeed(float speed, bool isDirRight)
//{
//	m_playerSpeed = speed;
//	m_isTurned = isDirRight;
//}
//void BackgroundManager::Shake(float amount, float delay)
//{
//	//Set amount and delay to parameters
//	if (!m_isShaking)
//	{
//		m_shakeDelay = delay;
//		m_shakeAmount = amount;
//		m_shakeTimer = 1.5;
//		m_isShaking = true;
//	}
//	//Put temp position of each bg in memory
//	for (int i = 0; i < m_bgs.size(); ++i)
//	{
//		if (m_bgs[i] != nullptr)
//		m_bgPos.push_back(pmath::Vec2(m_bgs[i]->transform.GetPosition()));
//	}
//}
//void BackgroundManager::ParallerShake(float dt)
//{
//	m_shakeTimer -= dt;
//	m_shakeAmount = m_shakeTimer*5;
//	if (m_shakeTimer >= 0)
//	{
//		//Shake amount randomisation
//		auto am = Randomizer::GetFloat(-m_shakeAmount, m_shakeAmount);
//		//Shake every background but different amount
//		for (int i = 0; i < m_bgs.size(); ++i)
//		{
//			if (i < 2)
//				m_bgs[i]->transform.SetPosition(m_bgs[i]->transform.GetPosition().x, m_bgPos[i].y + am / 5);
//			else if (i >= 2 && i < 4)
//				m_bgs[i]->transform.SetPosition(m_bgs[i]->transform.GetPosition().x, m_bgPos[i].y + am);
//			else
//				m_bgs[i]->transform.SetPosition(m_bgs[i]->transform.GetPosition().x, m_bgPos[i].y + am * 5);
//		}
//	}
//	else
//	{
//		//Put background in right position
//		m_isShaking = false;
//		for (int i = 0; i < m_bgs.size(); ++i)
//		{
//			m_bgs[i]->transform.SetPosition(m_bgs[i]->transform.GetPosition().x, m_bgPos[i].y);
//		}
//		m_bgPos.clear();
//	}
//
//}
//// Deconstructor