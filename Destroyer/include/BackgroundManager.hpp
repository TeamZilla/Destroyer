#pragma once
#ifndef BackgroundManager_HPP
#define BackgroundManager_HPP

#include <UtH/UtHEngine.hpp>
#include <Background.hpp>

class BackgroundManager
{
private:

	Background* m_back_1;
	Background* m_back_2;

	Background* m_front_1;
	Background* m_front_2;

	Background* m_mountain_1;
	Background* m_mountain_2;

	float m_backSpawnY, m_frontSpawnY, m_mountainSpawnY;
	float m_backSpeed, m_frontSpeed, m_mountainSpeed, m_playerSpeed;
	const float c_backSpeedM = 150;
	const float c_frontSpeedM = 300;
	const float c_mountainSpeedM = 30;
	bool  m_isTurned, m_isTurning;
	void GoLeft(float dt);
	void GoRight(float dt);

public:
	BackgroundManager(float bY, float fY, float mY);
	~BackgroundManager();

	void Update(float);
	void DrawFront();
	void DrawBack();
	void Turning(float);
	void CheckIfTurned(bool);
	void CheckSpeed(float);
};

#endif //BackgroundManager_HPP