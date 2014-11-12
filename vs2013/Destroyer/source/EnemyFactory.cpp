#include <EnemyFactory.hpp>
#include <TankBehavior.hpp>
#include <SoldierBehavior.hpp>
#include <AeroplaneBehavior.hpp>
#include <ExplosionEmitter.hpp>

using namespace uth;

uth::Layer*			EnemyFactory::m_layer;
uth::PhysicsWorld*	EnemyFactory::m_physicsWorld;
Player*				EnemyFactory::m_player;

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
		auto& obj = *static_cast<GameObject*>(e.get());
		auto& tank = *static_cast<TankBehavior*>(obj.GetComponent<TankBehavior>());

		if (tank.isDestroyed())
		{
			ExplosionEmitter::Emit(obj.transform.GetPosition());
			m_layer->RemoveChild(&obj);
		}
	}
	for (auto& e : m_layer->Children("Soldier"))
	{
		auto& obj = *static_cast<GameObject*>(e.get());
		auto& tank = *static_cast<SoldierBehavior*>(obj.GetComponent<SoldierBehavior>());

		if (tank.isDestroyed())
		{
			ExplosionEmitter::Emit(obj.transform.GetPosition());
			m_layer->RemoveChild(&obj);
		}
	}
}