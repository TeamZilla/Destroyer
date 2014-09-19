#include <BackgroundManager.hpp>

using namespace uth;

BackgroundManager::BackgroundManager(float bY, float fY, float mY)
	:m_backSpawnY(bY),
	m_frontSpawnY(fY),
	m_mountainSpawnY(mY)
{
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
// Deconstructor
BackgroundManager::~BackgroundManager()
{
}