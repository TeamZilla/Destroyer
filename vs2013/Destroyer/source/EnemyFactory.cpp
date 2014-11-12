#include <EnemyFactory.hpp>
#include <TankBehavior.hpp>
#include <SoldierBehavior.hpp>
#include <AeroplaneBehavior.hpp>
#include <ExplosionEmitter.hpp>

using namespace uth;

uth::Layer*			EnemyFactory::m_layer;
uth::PhysicsWorld*	EnemyFactory::m_physicsWorld;
Player*				EnemyFactory::m_player;
uth::Sound*			EnemyFactory::m_expSound;


float EnemyFactory::m_aeroplaneSpawnCooldown = 5;
float EnemyFactory::m_aeroplaneSpawnTimer = 0;
float EnemyFactory::m_tankSpawnCooldown = 3;
float EnemyFactory::m_tankSpawnTimer = 0;
float EnemyFactory::m_soldierSpawnCooldown = 1;
float EnemyFactory::m_soldierSpawnTimer = 0;

std::shared_ptr<GameObject> EnemyFactory::CreateTank()
{
	const static float speed(8.0f);
	const static std::string textureId("Enemies/tank.png");

	auto& obj = std::shared_ptr<GameObject>(new GameObject());
	obj->AddTags({ "Tank", "Enemy" });
	obj->AddComponent(new Sprite(textureId));

	const static pmath::Vec2 CollisionSize(obj->transform.GetSize()/2);
	obj->transform.SetPosition(SpawnPosition());

	obj->transform.SetScale(0.5f);
	obj->AddComponent(new Rigidbody(*m_physicsWorld, uth::COLLIDER_BOX, CollisionSize));
	obj->AddComponent(new TankBehavior(speed, m_player));

	return m_layer->AddChild(obj);

}

std::shared_ptr<GameObject> EnemyFactory::CreateSoldier()
{
	const static float speed(8.0f);
	const static std::string textureId("Enemies/soldier.png");

	auto& obj = std::shared_ptr<GameObject>(new GameObject());
	obj->AddTags({ "Soldier", "Enemy" });
	obj->AddComponent(new Sprite(textureId));

	const static pmath::Vec2 CollisionSize(obj->transform.GetSize() / 2);
	obj->transform.SetPosition(SpawnPosition());

	obj->transform.SetScale(0.5f);
	obj->AddComponent(new Rigidbody(*m_physicsWorld, uth::COLLIDER_BOX, CollisionSize));
	obj->AddComponent(new SoldierBehavior(speed, m_player));

	return m_layer->AddChild(obj);

}


std::shared_ptr<GameObject> EnemyFactory::CreateAeroplane()
{
	const static std::string textureId("Enemies/aeroplane.png");

	auto& obj = std::shared_ptr<GameObject>(new GameObject());
	obj->AddTags({ "Aeroplane", "Enemy" });
	obj->AddComponent(new Sprite(textureId));
	const static pmath::Vec2 CollisionSize(obj->transform.GetSize() / 2);

	obj->transform.SetScale(0.5f);
	obj->AddComponent(new Rigidbody(*m_physicsWorld, uth::COLLIDER_BOX, CollisionSize));
	obj->AddComponent(new AeroplaneBehavior());

	return m_layer->AddChild(obj);

}


pmath::Vec2 EnemyFactory::SpawnPosition()
{
	const static pmath::Vec2 spawnPosition(m_player->transform.GetPosition().x + 800, 500);

	if (uth::Randomizer::GetInt(0, 11) < 6)
		return pmath::Vec2(spawnPosition.x, spawnPosition.y);
	else
		return pmath::Vec2(-spawnPosition.x, spawnPosition.y);
}

void EnemyFactory::CheckEnemies()
{
	for (auto& e : m_layer->Children("Tank"))
	{
		auto& obj  = *static_cast<GameObject*>(e.get());
		auto& tank = *static_cast<TankBehavior*>(obj.GetComponent<TankBehavior>());

		if (tank.isDestroyed())
		{
			ExplosionEmitter::Emit(obj.transform.GetPosition());
			m_expSound->Play();
			m_layer->RemoveChild(&obj);
		}
	}
	for (auto& e : m_layer->Children("Soldier"))
	{
		auto& obj  = *static_cast<GameObject*>(e.get());
		auto& tank = *static_cast<SoldierBehavior*>(obj.GetComponent<SoldierBehavior>());

		if (tank.isDestroyed())
		{
			ExplosionEmitter::Emit(obj.transform.GetPosition());
			m_expSound->Play();
			m_layer->RemoveChild(&obj);
		}
	}

	for (auto& e : m_layer->Children("Aeroplane"))
	{
		auto& obj = *static_cast<GameObject*>(e.get());
		auto& aeroplane = *static_cast<AeroplaneBehavior*>(obj.GetComponent<AeroplaneBehavior>());

		if (aeroplane.isDestroyed())
		{
			ExplosionEmitter::Emit(obj.transform.GetPosition());
			m_layer->RemoveChild(&obj);
		}
	}
}

void EnemyFactory::Update(float dt)
{
	m_tankSpawn(dt);
	m_soldierSpawn(dt);
	m_aeroplaneSpawn(dt);
	CheckEnemies();
}

void EnemyFactory::m_soldierSpawn(float dt)
{
	if (m_soldierSpawnTimer > m_soldierSpawnCooldown)
	{
		CreateSoldier();
		m_soldierSpawnTimer = 0;
	}
	m_soldierSpawnTimer += dt;
}


void EnemyFactory::m_tankSpawn(float dt)
{
	if (m_tankSpawnTimer > m_tankSpawnCooldown)
	{
		CreateTank();
		m_tankSpawnTimer = 0;
	}
	m_tankSpawnTimer += dt;
}

void EnemyFactory::m_aeroplaneSpawn(float dt)
{
	if (m_aeroplaneSpawnTimer > m_aeroplaneSpawnCooldown)
	{
		CreateAeroplane();
		m_aeroplaneSpawnTimer = 0;
	}
	m_aeroplaneSpawnTimer += dt;
}