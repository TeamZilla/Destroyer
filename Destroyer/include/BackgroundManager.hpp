#pragma once
#ifndef BackgroundManager_HPP
#define BackgroundManager_HPP

#include <UtH/UtHEngine.hpp>
#include <Background.hpp>
#include <vector>

class BackgroundManager
{
private:

	Background* m_back_1;
	Background* m_back_2;

	Background* m_front_1;
	Background* m_front_2;

	Background* m_mountain_1;
	Background* m_mountain_2;

	float m_backSpawnY, m_frontSpawnY, m_mountainSpawnY, m_xBound;
	float m_backSpeed, m_frontSpeed, m_mountainSpeed, m_playerSpeed;
	float m_cameraPan, m_cameraPanMax, m_cameraPanSpd, m_isCameraTurning;
	const float c_backSpeedM = 150;
	const float c_frontSpeedM = 300;
	const float c_mountainSpeedM = 30;
	bool  m_isTurned, m_isTurning;
	void Movement(float dt);
	void GoRight(float dt);

	std::vector<Background*> m_bgs;
	uth::Camera* m_camera;
	pmath::Vec2 m_cameraStartPos;

public:
	BackgroundManager(float bY, float fY, float mY);
	~BackgroundManager();

	void Update(float);
	void DrawFront();
	void DrawBack();
	void ChangeDirection();
	void CheckSpeed(float);
	void CameraMovement(float dt);
	void SetCameraStartPos(pmath::Vec2);
};

#endif //BackgroundManager_HPP