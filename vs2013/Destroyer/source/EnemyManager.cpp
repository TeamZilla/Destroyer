#include <EnemyManager.hpp>
#include <ExplosionEmitter.hpp>

using namespace uth;

EnemyManager::EnemyManager(uth::Layer& layer)
	:
	m_layer(layer)
{
	m_spawnPointLeft = pmath::Vec2(-(uthEngine.GetWindow().GetSize().x),
									 uthEngine.GetWindow().GetSize().y / 2);
	m_spawnPointRight = pmath::Vec2( uthEngine.GetWindow().GetSize().x,
									 uthEngine.GetWindow().GetSize().y / 2);

	m_tankSPRight = pmath::Vec2(m_spawnPointRight.x - 400, m_spawnPointRight.y + 140);
	m_tankSPLeft = pmath::Vec2(m_spawnPointLeft.x + 400, m_spawnPointLeft.y + 140);

	enemyCount = 0;
	m_soldierS = 2;
	m_tankS    = 2;
}
EnemyManager::~EnemyManager()
{

}

bool EnemyManager::Init()
{
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
	for (auto& e : m_layer.Children("Tank"))
	{
		auto& tank = *static_cast<Tank*>(e.get());

		if (tank.isDestroyed())
		{
			ExplosionEmitter::Emit(tank.transform.GetPosition());
			m_layer.RemoveChild(e);
		}
	}

	for (auto& e : m_layer.Children("Soldier"))
	{
		auto& soldier = *static_cast<Soldier*>(e.get());

		if (soldier.isDestroyed())
		{
			m_layer.RemoveChild(e);
		}
	}

	SpawnTanks(dt);
	SpawnSoldiers(dt);
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

	if (m_tankST <= 0 && m_layer.Children("Tank").size() < 1500)
	{
		const auto& spawnPosition =
			Randomizer::GetInt(0, 10) < 5
			? m_tankSPLeft
			: m_tankSPRight;

		Tank* tempTank = new Tank(spawnPosition, m_physWorld);
		m_layer.AddChild(tempTank);
		m_tankST = m_tankS;
	}
}

void EnemyManager::SpawnSoldiers(float dt)
{
	m_soldierST -= dt;
	if (m_soldierST <= 0 && m_layer.Children("Soldier").size() < 1500)
	{
		const auto& spawnPosition =
			Randomizer::GetInt(0, 10) < 5
			? m_tankSPLeft
			: m_tankSPRight;

		Soldier* tempSoldier = new Soldier(pmath::Vec2(spawnPosition), m_physWorld);
		m_layer.AddChild(tempSoldier);
		m_soldierST = m_soldierS;
	}
}