#include <EnemyFactory.hpp>
#include <TankBehavior.hpp>
#include <SoldierBehavior.hpp>
#include <AeroplaneBehavior.hpp>
#include <ExplosionEmitter.hpp>
#include <Heli.hpp>
#include <GameStats.hpp>
#include <Pickup.hpp>

using namespace uth;

uth::Layer*			EnemyFactory::m_layer;
uth::PhysicsWorld*	EnemyFactory::m_physicsWorld;
Player*				EnemyFactory::m_player;
uth::Sound*			EnemyFactory::m_expSound;
uth::Sound*			EnemyFactory::m_hpSound;
uth::Sound*			EnemyFactory::m_starSound;

float EnemyFactory::m_aeroplaneSpawnCooldown = 45;
float EnemyFactory::m_aeroplaneSpawnTimer = 0;
float EnemyFactory::m_tankSpawnCooldown = 3;
float EnemyFactory::m_tankSpawnTimer = 0;
float EnemyFactory::m_soldierSpawnCooldown = 1;
float EnemyFactory::m_soldierSpawnTimer = 0;
float EnemyFactory::m_heliSpawnCooldown = 7;
float EnemyFactory::m_heliSpawnTimer = 0;
float EnemyFactory::m_timeCounter = 0;

std::shared_ptr<GameObject> EnemyFactory::CreateTank()
{
	const static float speed(8.0f);
	static uth::Texture* textureId = uthRS.LoadTexture("Enemies/tank_sheet.png");

	auto obj = std::shared_ptr<GameObject>(new GameObject());
	obj->AddTags({ "Tank", "Enemy" });
	obj->AddComponent(new AnimatedSprite(textureId,3,3,1,0));

	const static pmath::Vec2 CollisionSize(obj->transform.GetSize()/2);
	obj->transform.SetPosition(SpawnPosition());

	obj->transform.SetScale(0.5f);
	obj->AddComponent(new Rigidbody(*m_physicsWorld, uth::COLLIDER_BOX, CollisionSize));
	obj->AddComponent(new TankBehavior(speed, m_player, m_layer));

	return m_layer->AddChild(obj);

}

std::shared_ptr<GameObject> EnemyFactory::CreateSoldier()
{
	const static float speed(uth::Randomizer::GetFloat(1.5f,4.5f));
	static uth::Texture* textureId = uthRS.LoadTexture("Enemies/soldier.png");

	auto obj = std::shared_ptr<GameObject>(new GameObject());
	obj->AddTags({ "Soldier", "Enemy" });
	obj->AddComponent(new AnimatedSprite(textureId, 12, 6, 2, 12));
	obj->GetComponent<AnimatedSprite>()->ChangeAnimation(0, 6, 0, 12);

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

	auto obj = std::shared_ptr<GameObject>(new GameObject());
	obj->AddTags({ "Aeroplane", "Enemy" });
	obj->AddComponent(new Sprite(textureId));

	const static pmath::Vec2 CollisionSize(obj->transform.GetSize() / 2);

	obj->transform.SetScale(0.5f);
	obj->AddComponent(new Rigidbody(*m_physicsWorld, uth::COLLIDER_BOX, CollisionSize));
	obj->AddComponent(new AeroplaneBehavior(m_layer, m_player));

	return m_layer->AddChild(obj);

}


std::shared_ptr<GameObject> EnemyFactory::CreateHeli()
{
	const static std::string textureId("Enemies/heli.png");

	auto spawn = pmath::Vec2(SpawnPosition().x - 100,SpawnPosition().y - 300);
	auto obj = new Heli(spawn,m_player);
	obj->AddTags({ "Heli", "Enemy" });

	const static pmath::Vec2 CollisionSize(obj->transform.GetSize() / 2);

	obj->transform.SetScale(0.5f);
	obj->AddComponent(new Rigidbody(*m_physicsWorld, uth::COLLIDER_BOX, CollisionSize));


	return m_layer->AddChild(obj);

}

std::shared_ptr<GameObject> EnemyFactory::CreateHP(pmath::Vec2 pos)
{
	auto obj = new Pickup(0);
	obj->AddTag("HealthPickup");
	obj->transform.SetPosition(pos);

	return m_layer->AddChild(obj);
}

std::shared_ptr<GameObject> EnemyFactory::CreateStar(pmath::Vec2 pos)
{
	auto obj = new Pickup(1);
	obj->AddTag("StarPickup");
	obj->transform.SetPosition(pos);

	return m_layer->AddChild(obj);
}


pmath::Vec2 EnemyFactory::SpawnPosition()
{
	const static pmath::Vec2 spawnPosition(m_player->transform.GetPosition().x + 1100, 500);

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
		{	//Emit pickups
			CreateHP(obj.transform.GetPosition());
			CreateStar(obj.transform.GetPosition());

			ExplosionEmitter::Emit(obj.transform.GetPosition());
			m_expSound->PlayEffect();
			m_layer->RemoveChild(&obj);
			Statistics.score.tankKills++;
			Statistics.score.current += 10;
		}
	}
	for (auto& e : m_layer->Children("Soldier"))
	{
		auto& obj  = *static_cast<GameObject*>(e.get());
		auto& tank = *static_cast<SoldierBehavior*>(obj.GetComponent<SoldierBehavior>());

		if (tank.isDestroyed())
		{	//Emit pickups
			CreateStar(obj.transform.GetPosition());

			ExplosionEmitter::Emit(obj.transform.GetPosition());
			m_expSound->PlayEffect();
			m_layer->RemoveChild(&obj);
			Statistics.score.soldKills++;
			Statistics.score.current += 1;
		}
	}

	for (auto& e : m_layer->Children("Aeroplane"))
	{
		auto& obj = *static_cast<GameObject*>(e.get());
		auto& aeroplane = *static_cast<AeroplaneBehavior*>(obj.GetComponent<AeroplaneBehavior>());

		if (aeroplane.isDestroyed())
		{	//Emit pickups
			CreateHP(obj.transform.GetPosition());
			CreateStar(obj.transform.GetPosition());

			if (abs(aeroplane.m_rigidBody->GetPosition().x) < 1000)
			{
				Statistics.score.current += 150;
				Statistics.score.aeroKills++;
			}
			ExplosionEmitter::Emit(obj.transform.GetPosition());
			m_expSound->PlayEffect();
			m_layer->RemoveChild(&obj);


		}
	}

	for (auto& e : m_layer->Children("Heli"))
	{
		auto& obj = *static_cast<Heli*>(e.get());
		//auto& heli = *static_cast<Heli*>(obj.GetComponent<Heli>());
	
		if (obj.isDestroyed())
		{	//Emit pickups
			CreateHP(obj.transform.GetPosition());
			CreateStar(obj.transform.GetPosition());

			ExplosionEmitter::Emit(obj.transform.GetPosition());
			m_expSound->PlayEffect();
			m_layer->RemoveChild(&obj);
			Statistics.score.heliKills++;
			Statistics.score.current += 20;
		}
	}
	
	////////////////////////////////////
	
	for (auto& e : m_layer->Children("HealthPickup"))
	{
		auto& obj = *static_cast<Pickup*>(e.get());
	
		if (obj.isDestroyed)
		{
			m_hpSound->PlayEffect();
			m_layer->RemoveChild(&obj);

			if (Statistics.player.hp < Statistics.player.maxHp)
				Statistics.player.hp += 0.05f;
			else
				Statistics.player.hp = Statistics.player.maxHp;
		}
	
	}
	
	for (auto& e : m_layer->Children("StarPickup"))
	{
		auto& obj = *static_cast<Pickup*>(e.get());
	
		if (obj.isDestroyed)
		{
			m_starSound->PlayEffect();
			m_layer->RemoveChild(&obj);
			Statistics.score.current += 10;
		}
	
	}
}

void EnemyFactory::Update(float dt)
{
	m_timeCounter += 1.2 * dt;

	// easy 1

	if (m_timeCounter < 15)
	{

		EnemyFactory::m_aeroplaneSpawnCooldown = 0;
		EnemyFactory::m_tankSpawnCooldown = 0;
		EnemyFactory::m_soldierSpawnCooldown = 1.5;
		EnemyFactory::m_heliSpawnCooldown = 1;


		if (m_layer->Children("Tank").size() < 0)
			m_tankSpawn(dt);
		if (m_layer->Children("Soldier").size() < 15)
			m_soldierSpawn(dt);
		if (m_layer->Children("Aeroplane").size() < 0)
			m_aeroplaneSpawn(dt);
		if (m_layer->Children("Heli").size() < 0)
			m_heliSpawn(dt);
	}

// easy 2
	if (m_timeCounter < 45 && m_timeCounter > 15)
	{
		EnemyFactory::m_aeroplaneSpawnCooldown = 0;
		EnemyFactory::m_tankSpawnCooldown = 4;
		EnemyFactory::m_soldierSpawnCooldown = 1;
		EnemyFactory::m_heliSpawnCooldown = 0;

		if (m_layer->Children("Tank").size() < 1)
			m_tankSpawn(dt);
		if (m_layer->Children("Soldier").size() < 20)
			m_soldierSpawn(dt);
		if (m_layer->Children("Aeroplane").size() < 0)
			m_aeroplaneSpawn(dt);
		if (m_layer->Children("Heli").size() < 0)
			m_heliSpawn(dt);
	}

// easy 3
	if (m_timeCounter < 80 && m_timeCounter > 45)
	{
		EnemyFactory::m_aeroplaneSpawnCooldown = 0;
		EnemyFactory::m_tankSpawnCooldown = 3;
		EnemyFactory::m_soldierSpawnCooldown = 1;
		EnemyFactory::m_heliSpawnCooldown = 10;

		if (m_layer->Children("Tank").size() < 3)
			m_tankSpawn(dt);
		if (m_layer->Children("Soldier").size() < 20)
			m_soldierSpawn(dt);
		if (m_layer->Children("Aeroplane").size() < 0)
			m_aeroplaneSpawn(dt);
		if (m_layer->Children("Heli").size() < 1)
			m_heliSpawn(dt);
	}

	//Easy 4

	if (m_timeCounter < 150 && m_timeCounter > 80)
	{
		EnemyFactory::m_aeroplaneSpawnCooldown = 0;
		EnemyFactory::m_tankSpawnCooldown = 3;
		EnemyFactory::m_soldierSpawnCooldown = 1;
		EnemyFactory::m_heliSpawnCooldown = 10;

		if (m_layer->Children("Tank").size() < 4)
			m_tankSpawn(dt);
		if (m_layer->Children("Soldier").size() < 20)
			m_soldierSpawn(dt);
		if (m_layer->Children("Aeroplane").size() < 0)
			m_aeroplaneSpawn(dt);
		if (m_layer->Children("Heli").size() < 2)
			m_heliSpawn(dt);
	}

	// Pre-boss scene

	if (m_timeCounter < 160 && m_timeCounter > 150)
	{
		EnemyFactory::m_aeroplaneSpawnCooldown = 0;
		EnemyFactory::m_tankSpawnCooldown = 0;
		EnemyFactory::m_soldierSpawnCooldown = 0;
		EnemyFactory::m_heliSpawnCooldown = 0;


		if (m_layer->Children("Tank").size() < 0)
			m_tankSpawn(dt);
		if (m_layer->Children("Soldier").size() < 0)
			m_soldierSpawn(dt);
		if (m_layer->Children("Aeroplane").size() < 0)
			m_aeroplaneSpawn(dt);
		if (m_layer->Children("Heli").size() < 0)
			m_heliSpawn(dt);
	}


	// Aeroplain boss

	if (m_timeCounter < 190 && m_timeCounter > 160)
	{
		EnemyFactory::m_aeroplaneSpawnCooldown = 7;
		EnemyFactory::m_tankSpawnCooldown = 0;
		EnemyFactory::m_soldierSpawnCooldown = 0;
		EnemyFactory::m_heliSpawnCooldown = 0;


		if (m_layer->Children("Tank").size() < 0)
			m_tankSpawn(dt);
		if (m_layer->Children("Soldier").size() < 0)
			m_soldierSpawn(dt);
		if (m_layer->Children("Aeroplane").size() < 3)
			m_aeroplaneSpawn(dt);
		if (m_layer->Children("Heli").size() < 0)
			m_heliSpawn(dt);
	}

	// after boss scene

	if (m_timeCounter < 200 && m_timeCounter > 195)
	{
		EnemyFactory::m_aeroplaneSpawnCooldown = 0;
		EnemyFactory::m_tankSpawnCooldown = 1;
		EnemyFactory::m_soldierSpawnCooldown = 0;
		EnemyFactory::m_heliSpawnCooldown = 0;


		if (m_layer->Children("Tank").size() < 16)
			m_tankSpawn(dt);
		if (m_layer->Children("Soldier").size() < 0)
			m_soldierSpawn(dt);
		if (m_layer->Children("Aeroplane").size() < 0)
			m_aeroplaneSpawn(dt);
		if (m_layer->Children("Heli").size() < 0)
			m_heliSpawn(dt);
	}


	// all enemies 1

	if (m_timeCounter < 230 && m_timeCounter > 200)
	{
		EnemyFactory::m_aeroplaneSpawnCooldown = 17;
		EnemyFactory::m_tankSpawnCooldown = 3;
		EnemyFactory::m_soldierSpawnCooldown = 2;
		EnemyFactory::m_heliSpawnCooldown = 10;


		if (m_layer->Children("Tank").size() < 1)
			m_tankSpawn(dt);
		if (m_layer->Children("Soldier").size() < 20)
			m_soldierSpawn(dt);
		if (m_layer->Children("Aeroplane").size() < 1)
			m_aeroplaneSpawn(dt);
		if (m_layer->Children("Heli").size() < 1)
			m_heliSpawn(dt);
	}

	// all enemies 2

	if (m_timeCounter < 280 && m_timeCounter > 230)
	{
		EnemyFactory::m_aeroplaneSpawnCooldown = 15;
		EnemyFactory::m_tankSpawnCooldown = 3;
		EnemyFactory::m_soldierSpawnCooldown = 2;
		EnemyFactory::m_heliSpawnCooldown = 10;


		if (m_layer->Children("Tank").size() < 3)
			m_tankSpawn(dt);
		if (m_layer->Children("Soldier").size() < 20)
			m_soldierSpawn(dt);
		if (m_layer->Children("Aeroplane").size() < 1)
			m_aeroplaneSpawn(dt);
		if (m_layer->Children("Heli").size() < 2)
			m_heliSpawn(dt);
	}

	// all enemies 3

	if (m_timeCounter < 340 && m_timeCounter > 280)
	{
		EnemyFactory::m_aeroplaneSpawnCooldown = 12;
		EnemyFactory::m_tankSpawnCooldown = 3;
		EnemyFactory::m_soldierSpawnCooldown = 1;
		EnemyFactory::m_heliSpawnCooldown = 7;


		if (m_layer->Children("Tank").size() < 4)
			m_tankSpawn(dt);
		if (m_layer->Children("Soldier").size() < 20)
			m_soldierSpawn(dt);
		if (m_layer->Children("Aeroplane").size() < 1)
			m_aeroplaneSpawn(dt);
		if (m_layer->Children("Heli").size() < 3)
			m_heliSpawn(dt);
	}

	// all enemies 4

	if (m_timeCounter < 380 && m_timeCounter > 340)
	{
		EnemyFactory::m_aeroplaneSpawnCooldown = 12;
		EnemyFactory::m_tankSpawnCooldown = 2;
		EnemyFactory::m_soldierSpawnCooldown = 1;
		EnemyFactory::m_heliSpawnCooldown = 7;


		if (m_layer->Children("Tank").size() < 6)
			m_tankSpawn(dt);
		if (m_layer->Children("Soldier").size() < 25)
			m_soldierSpawn(dt);
		if (m_layer->Children("Aeroplane").size() < 1)
			m_aeroplaneSpawn(dt);
		if (m_layer->Children("Heli").size() < 4)
			m_heliSpawn(dt);
	}


	// pre-boss scene

	if (m_timeCounter < 390 && m_timeCounter > 380)
	{
		EnemyFactory::m_aeroplaneSpawnCooldown = 0;
		EnemyFactory::m_tankSpawnCooldown = 0;
		EnemyFactory::m_soldierSpawnCooldown = 0;
		EnemyFactory::m_heliSpawnCooldown = 0;


		if (m_layer->Children("Tank").size() < 0)
			m_tankSpawn(dt);
		if (m_layer->Children("Soldier").size() < 0)
			m_soldierSpawn(dt);
		if (m_layer->Children("Aeroplane").size() < 0)
			m_aeroplaneSpawn(dt);
		if (m_layer->Children("Heli").size() < 0)
			m_heliSpawn(dt);
	}

	// Heli boss

	if (m_timeCounter < 420 && m_timeCounter > 390)
	{
		EnemyFactory::m_aeroplaneSpawnCooldown = 0;
		EnemyFactory::m_tankSpawnCooldown = 0;
		EnemyFactory::m_soldierSpawnCooldown = 0;
		EnemyFactory::m_heliSpawnCooldown = 1;

		if (m_layer->Children("Tank").size() < 0)
			m_tankSpawn(dt);
		if (m_layer->Children("Soldier").size() < 0)
			m_soldierSpawn(dt);
		if (m_layer->Children("Aeroplane").size() < 0)
			m_aeroplaneSpawn(dt);
		if (m_layer->Children("Heli").size() < 4)
			m_heliSpawn(dt);
	}

	// after boss scene

	if (m_timeCounter < 445 && m_timeCounter > 430)
	{
		EnemyFactory::m_aeroplaneSpawnCooldown = 0;
		EnemyFactory::m_tankSpawnCooldown = 1;
		EnemyFactory::m_soldierSpawnCooldown = 0;
		EnemyFactory::m_heliSpawnCooldown = 0;


		if (m_layer->Children("Tank").size() < 16)
			m_tankSpawn(dt);
		if (m_layer->Children("Soldier").size() < 0)
			m_soldierSpawn(dt);
		if (m_layer->Children("Aeroplane").size() < 0)
			m_aeroplaneSpawn(dt);
		if (m_layer->Children("Heli").size() < 0)
			m_heliSpawn(dt);
	}

	// all enemies 5

	if (m_timeCounter > 445)
	{
		EnemyFactory::m_aeroplaneSpawnCooldown = 6;
		EnemyFactory::m_tankSpawnCooldown = 2;
		EnemyFactory::m_soldierSpawnCooldown = 1;
		EnemyFactory::m_heliSpawnCooldown = 6;


		if (m_layer->Children("Tank").size() < 6)
			m_tankSpawn(dt);
		if (m_layer->Children("Soldier").size() < 25)
			m_soldierSpawn(dt);
		if (m_layer->Children("Aeroplane").size() < 1)
			m_aeroplaneSpawn(dt);
		if (m_layer->Children("Heli").size() < 4)
			m_heliSpawn(dt);
	}

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

////////////////////

void EnemyFactory::m_heliSpawn(float dt)
{
	if (m_heliSpawnTimer > m_heliSpawnCooldown)
	{
		CreateHeli();
		m_heliSpawnTimer = 0;
	}
	m_heliSpawnTimer += dt;
}

//////////////////////////