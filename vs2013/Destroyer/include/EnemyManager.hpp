#pragma once

#include <UtH/UtHEngine.hpp>
#include <Player.hpp>
#include <Tank.hpp>
#include <Soldier.hpp>
#include <Heli.hpp>
//#include <Aeroplane.hpp>
#include <vector>

#include <map>

class EnemyManager
{
private:
	uth::Layer& m_layer;
	
	//uth::Layer* m_layer;
	Player* m_player;
	std::vector<uth::GameObject*> m_enemies;
	std::vector<Tank*> m_tanks;
	std::vector<Soldier*> m_soldiers;
	std::vector<Heli*> m_helis;
	//std::vector<Aeroplane*> m_planes;
	pmath::Vec2 m_spawnPointLeft;
	pmath::Vec2 m_spawnPointRight;
	float enemyCount;
	float m_tankST, m_soldierST;              //Tank & soldier spawn timer
	float m_tankS, m_soldierS;                //Tank & soldier spawn time
	pmath::Vec2 m_tankSPLeft;                 //Tank spawn left pos
	pmath::Vec2 m_tankSPRight;                //Tank spawn left pos
	pmath::Vec2 m_soldierSPLeft;              //Tank spawn left pos
	pmath::Vec2 m_soldierSPRight;             //Tank spawn left pos
	uth::PhysicsWorld* m_physWorld;
	uth::Sprite* m_gameFloor;

public:
	EnemyManager(uth::Layer& layer);
	~EnemyManager();
	bool Init();
	void Create(bool isRight, pmath::Vec2 spawnPos, std::string name);
	void Destroy(std::string name);
	void Update(float dt);
	void Draw();
	void CheckPlayer(Player* player);
	void SetPhysWorld(uth::PhysicsWorld* pworld);
	void SpawnTanks(float dt);
	void SpawnSoldiers(float dt);
	void DestroyTanks();
	void DestroySoldiers();

};