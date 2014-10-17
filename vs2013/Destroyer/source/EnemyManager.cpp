#include <EnemyManager.hpp>
#include <ExplosionEmitter.hpp>

using namespace uth;

EnemyManager::EnemyManager()
{
	m_spawnPointLeft = pmath::Vec2(-(uthEngine.GetWindow().GetSize().x),
									 uthEngine.GetWindow().GetSize().y / 2);
	m_spawnPointRight = pmath::Vec2( uthEngine.GetWindow().GetSize().x,
									 uthEngine.GetWindow().GetSize().y / 2);

	m_tankSPRight = pmath::Vec2(m_spawnPointRight.x - 400, m_spawnPointRight.y + 140);
	m_tankSPLeft = pmath::Vec2(m_spawnPointLeft.x + 400, m_spawnPointLeft.y + 140);

	enemyCount = 0;
	m_soldierS = 1;
	m_tankS    = 3;
}
EnemyManager::~EnemyManager()
{

}
bool EnemyManager::Init(uth::Layer* layer)
{
	m_layer = layer;

	return true;
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
		//	//TODO: REMOVE THE OBJECT
	}
}
void EnemyManager::Update(float dt)
{
	//Update every enemy in the update loop
	for (int i = 0; m_enemies.size() > i; ++i)
	{
		//m_enemies[i]->Update(dt);
	}
	for (int i = 0; m_tanks.size() > i; ++i)
	{
		if (m_tanks[i]->isDestroyed() == true)
		{
			ExplosionEmitter::Emit(m_tanks[i]->transform.GetPosition());
			m_layer->RemoveChild(m_tanks[i]);
			//delete m_tanks[i];
			m_tanks.erase(m_tanks.begin() + i);
		}
	}
	for (int i = 0; m_soldiers.size() > i; ++i)
	{
		if (m_soldiers[i]->isDestroyed() == true)
		{
			ExplosionEmitter::Emit(m_soldiers[i]->transform.GetPosition());
			m_layer->RemoveChild(m_soldiers[i]);
			m_soldiers.erase(m_soldiers.begin() + i);
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
	SpawnSoldiers(dt);
}
//void EnemyManager::Draw()
//{
//	//Draw every enemy in the draw loop
//	for (int i = 0; m_enemies.size() > i; ++i)
//	{
//		//m_enemies[i]->Draw(uthEngine.GetWindow());
//	}
//	for (int i = 0; m_tanks.size() > i; ++i)
//	{
//		if (m_tanks[i] != nullptr)
//		{
//			//m_tanks[i]->Draw();
//		}
//	}
//}
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
	if (m_tankST <= 0 && m_tanks.size() < 150)
	{
		if (Randomizer::GetInt(0, 10) < 5)
		{
			Tank* tempTank = new Tank(pmath::Vec2(m_tankSPLeft), m_physWorld);
			m_layer->AddChild(tempTank);
			m_tanks.push_back(tempTank);
		}
		else
		{
			Tank* tempTank = new Tank(pmath::Vec2(m_tankSPRight), m_physWorld);
			m_layer->AddChild(tempTank);
			m_tanks.push_back(tempTank);
		}
		m_tankST = m_tankS;
	}

}
void EnemyManager::SpawnSoldiers(float dt)
{
	m_soldierST -= dt;
	if (m_soldierST <= 0 && m_soldiers.size() < 150)
	{
		if (Randomizer::GetInt(0, 10) < 5)
		{
			Soldier* tempSoldier = new Soldier(pmath::Vec2(m_tankSPLeft), m_physWorld);
			m_layer->AddChild(tempSoldier);
			m_soldiers.push_back(tempSoldier);
		}
		else
		{
			Soldier* tempSoldier = new Soldier(pmath::Vec2(m_tankSPRight), m_physWorld);
			m_layer->AddChild(tempSoldier);
			m_soldiers.push_back(tempSoldier);
		}
		m_soldierST = m_soldierS;
	}

}
void EnemyManager::DestroyTanks()
{
	for (int i = 0; m_tanks.size() > i; ++i)
	{
		m_tanks[i]->Hit();
	}
}
void EnemyManager::DestroySoldiers()
{
	for (int i = 0; m_soldiers.size() > i; ++i)
	{
		m_soldiers[i]->Hit();
	}
}