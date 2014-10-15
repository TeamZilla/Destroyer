#include <EnemyManager.hpp>

using namespace uth;

EnemyManager::EnemyManager()
{
	m_spawnPointLeft = pmath::Vec2(-(uthEngine.GetWindow().GetSize().x),
									 uthEngine.GetWindow().GetSize().y / 2);
	m_spawnPointRight = pmath::Vec2( uthEngine.GetWindow().GetSize().x,
									 uthEngine.GetWindow().GetSize().y / 2);

	m_tankSPRight = pmath::Vec2(m_spawnPointRight.x - 400, m_spawnPointRight.y + 240);
	m_tankSPLeft = pmath::Vec2(m_spawnPointLeft.x + 400, m_spawnPointLeft.y + 240);

	enemyCount = 0;
	m_tankST = 4;
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
	for (int i = 0; m_tanks.size() > i; ++i)
	{
		if (m_tanks[i] != nullptr)
		{
			m_tanks[i]->Update(dt);
		}
		if (m_tanks[i]->isDestroyed() == true)
		{
			delete m_tanks[i];
			m_tanks.erase(m_tanks.begin() + i);
		}
	}
	if (m_player != nullptr)
	{

	}
	else
	{
		WriteLog("EnemyManager: Player not detected!");
	}

	SpawnTanks(dt);
}
void EnemyManager::Draw()
{
	//Draw every enemy in the draw loop
	for (int i = 0; m_enemies.size() > i; ++i)
	{
		m_enemies[i]->Draw(uthEngine.GetWindow());
	}
	for (int i = 0; m_tanks.size() > i; ++i)
	{
		if (m_tanks[i] != nullptr)
		{
			m_tanks[i]->Draw();
		}
	}
}
void EnemyManager::CheckPlayer(Player* player)
{
	//Get player reference
	m_player = player;
}
void EnemyManager::SetPhysWorld(PhysicsWorld* pworld)
{
	m_physWorld = pworld;
}
//_____TANKS_____//
void EnemyManager::SpawnTanks(float dt)
{
	m_tankST -= dt;
	if (m_tankST <= 0 && m_tanks.size() < 5)
	{
		if (Randomizer::GetInt(0, 10) < 5)
		{
			m_tanks.push_back(new Tank(pmath::Vec2(m_tankSPLeft), m_physWorld));
		}
		else
		{
			m_tanks.push_back(new Tank(pmath::Vec2(m_tankSPRight), m_physWorld));
		}
		m_tankST = 4;
	}

}
void EnemyManager::DestroyTanks()
{
	for (int i = 0; m_tanks.size() > i; ++i)
	{
		m_tanks[i]->Hit();
	}
}