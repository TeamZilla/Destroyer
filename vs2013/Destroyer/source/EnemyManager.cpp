#include <EnemyManager.hpp>

using namespace uth;

EnemyManager::EnemyManager()
{
	m_spawnPointLeft = pmath::Vec2(-100,0);
	m_spawnPointRight = pmath::Vec2(uthEngine.GetWindow().GetSize().x + 100);
	enemyCount = 0;
}
EnemyManager::~EnemyManager()
{

}
void EnemyManager::Create(bool isRight, pmath::Vec2 spawnPos, std::string name)
{	
	//Put enemy in vector list with unique name for easier handling
	m_enemies.push_back(new GameObject(name + std::to_string(enemyCount)));
	//Check if spawn left or right
	if (isRight)
		m_enemies[enemyCount]->transform.SetPosition(spawnPos);
	if (!isRight)
		m_enemies[enemyCount]->transform.SetPosition(spawnPos);
	//Add 1 to enemy count
	enemyCount++;
}
void EnemyManager::Destroy(std::string name)
{
	//Erase enemy with name
	for (int i = 0; m_enemies.size() > i; ++i)
	{
		if (m_enemies[i]->GetName() == name) 
		{
			//TODO: REMOVE THE OBJECT
		}
	}
}
void EnemyManager::Update(float dt)
{
	//Update every enemy in the update loop
	for (int i = 0; m_enemies.size() > i; ++i)
	{
		m_enemies[i]->Update(dt);
	}
}
void EnemyManager::Draw()
{
	//Draw every enemy in the draw loop
	for (int i = 0; m_enemies.size() > i; ++i)
	{
		m_enemies[i]->Draw(uthEngine.GetWindow());
	}
}
void EnemyManager::CheckPlayer(Player* player)
{
	//Get player reference
	m_player = player;
}
