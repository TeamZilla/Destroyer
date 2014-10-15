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
	float m_shakeTimer, m_shakeAmount, m_shakeDelay;
	const float c_backSpeedM = 100;
	const float c_frontSpeedM = 175;
	const float c_mountainSpeedM = 0.05;
	bool  m_isTurned, m_isTurning, m_isSet, m_isShaking;
	void Movement(float dt);
	//void GoRight(float dt);
	void ParallerShake(float dt);

	std::vector<Background*> m_bgs;
	uth::Camera* m_camera;
	pmath::Vec2 m_cameraStartPos;
	std::vector<pmath::Vec2*> m_bgPos;


public:
	BackgroundManager(float bY, float fY, float mY);
	~BackgroundManager();

	bool Init(uth::Object* background, uth::Object* frontground);

	void Update(float);
	void DrawFront();
	void DrawBack();
	void ChangeDirection();
	void CheckSpeed(float, bool isDirRight);
	void CameraMovement(float dt);
	void SetCameraStartPos(pmath::Vec2);
	void Shake(float amount, float delay = 0.1f);
};

#endif //BackgroundManager_HPP