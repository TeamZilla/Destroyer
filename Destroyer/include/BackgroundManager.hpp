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

public:
	BackgroundManager(float bY, float fY, float mY);
	~BackgroundManager();

	void Update(float);
	void DrawFront();
	void DrawBack();
};

#endif //BackgroundManager_HPP