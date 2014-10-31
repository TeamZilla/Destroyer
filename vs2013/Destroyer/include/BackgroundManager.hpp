#pragma once
#ifndef BackgroundManager_HPP
#define BackgroundManager_HPP

#include <UtH/UtHEngine.hpp>
#include <Background.hpp>
#include <vector>

class BackgroundManager
{
private:

	float m_backSpawnY, m_frontSpawnY, m_mountainSpawnY; // m_xBound;
	//float m_backSpeed, m_frontSpeed, m_mountainSpeed, m_playerSpeed;
	float m_cameraPan, m_cameraPanMax, m_cameraPanSpd, m_isCameraTurning;
	//float m_shakeTimer, m_shakeAmount, m_shakeDelay;

	float m_camShakeAmount;
	const float c_backSpeedM = 50;
	const float c_frontSpeedM = 100;
	const float c_mountainSpeedM = 10;


	uth::Camera* m_camera;
	pmath::Vec2 m_cameraStartPos;
	uth::Layer* backG;
	uth::Layer* backF;
	//bool  m_isTurned, m_isTurning, m_isSet, m_isShaking;
	//void Movement(float dt);
	//void GoRight(float dt);
	//void ParallerShake(float dt);

	//std::vector<std::shared_ptr<Background>> m_bgs;
	//std::vector<pmath::Vec2> m_bgPos;

public:
	BackgroundManager(float bY, float fY, float mY);
	~BackgroundManager();

	bool Init(uth::Object& background, uth::Object& frontground);
	void DeInit();
	void Update(float);
	void CameraMovement(float dt);
	void SetCameraStartPos(pmath::Vec2);
	//void DrawFront();
	//void DrawBack();
	//void ChangeDirection();
	//void CheckSpeed(float, bool isDirRight);
	void Shake(float amount, float delay = 0.1f);
};

#endif //BackgroundManager_HPP