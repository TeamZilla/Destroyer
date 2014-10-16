#pragma once
#ifndef EnemyManager_HPP
#define EnemyManager_HPP

#include <UtH/UtHEngine.hpp>
#include <Player.hpp>
#include <Tank.hpp>
#include <Heli.hpp>
#include <Aeroplane.hpp>
#include <vector>

class EnemyManager
{
private:
	uth::Layer* m_layer;
	Player* m_player;
	std::vector<uth::GameObject*> m_enemies;
	std::vector<Tank*> m_tanks;
	std::vector<Heli*> m_helis;
	std::vector<Aeroplane*> m_planes;
	pmath::Vec2 m_spawnPointLeft;
	pmath::Vec2 m_spawnPointRight;
	float enemyCount;
	float m_tankST;                           //Tank spawn time
	pmath::Vec2 m_tankSPLeft;                 //Tank spawn left pos
	pmath::Vec2 m_tankSPRight;                //Tank spawn left pos
	uth::PhysicsWorld* m_physWorld;
	uth::Sprite* m_gameFloor;

public:

	EnemyManager();
	~EnemyManager();
	bool Init(uth::Layer* m_layer);
	void Create(bool isRight, pmath::Vec2 spawnPos, std::string name);
	void Destroy(std::string name);
	void Update(float dt);
	void Draw();
	void CheckPlayer(Player* player);
	void SetPhysWorld(uth::PhysicsWorld* pworld);
	void SpawnTanks(float dt);
	void DestroyTanks();

};


#endif