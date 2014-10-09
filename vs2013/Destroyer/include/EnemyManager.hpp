#pragma once
#ifndef EnemyManager_HPP
#define EnemyManager_HPP

#include <UtH/UtHEngine.hpp>
#include <Player.hpp>
#include <vector>

class EnemyManager
{
private:
	Player* m_player;
	std::vector<uth::GameObject*> m_enemies;
	pmath::Vec2 m_spawnPointLeft;
	pmath::Vec2 m_spawnPointRight;
	float enemyCount;

public:

	EnemyManager();
	~EnemyManager();
	void Create(bool isRight, pmath::Vec2 spawnPos, std::string name);
	void Destroy(std::string name);
	void Update(float dt);
	void Draw();
	void CheckPlayer(Player* player);


};


#endif