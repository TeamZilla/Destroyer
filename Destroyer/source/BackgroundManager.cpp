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
	GoLeft(dt);
}
void BackgroundManager::GoLeft(float dt)
{
	m_mountain_1->transform.SetPosition(
		m_mountain_1->transform.GetPosition().x - (c_mountainSpeedM + m_playerSpeed)*dt, m_mountainSpawnY);
	m_mountain_2->transform.SetPosition(
		m_mountain_2->transform.GetPosition().x - (c_mountainSpeedM + m_playerSpeed)*dt, m_mountainSpawnY);

	m_back_1->transform.SetPosition(
		m_back_1->transform.GetPosition().x - (c_backSpeedM + m_playerSpeed)*dt, m_backSpawnY);
	m_back_2->transform.SetPosition(
		m_back_2->transform.GetPosition().x - (c_backSpeedM + m_playerSpeed)*dt, m_backSpawnY);

	m_front_1->transform.SetPosition(
		m_front_1->transform.GetPosition().x - (c_frontSpeedM + m_playerSpeed)*dt, m_frontSpawnY);
	m_front_2->transform.SetPosition(
		m_front_2->transform.GetPosition().x - (c_frontSpeedM + m_playerSpeed)*dt, m_frontSpawnY);

}
void BackgroundManager::Turning(float dt)
{
	if (m_isTurning)
	{

	}
	else
	{
		m_isTurned = true;
	}
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
void BackgroundManager::CheckIfTurned(bool isTurned)
{
	m_isTurned = isTurned;
}
void BackgroundManager::CheckSpeed(float speed)
{
	m_playerSpeed = speed;
}
// Deconstructor
BackgroundManager::~BackgroundManager()
{
}