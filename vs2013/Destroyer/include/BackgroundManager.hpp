#pragma once

#include <UtH/UtHEngine.hpp>
#include <Background.hpp>
#include <vector>

class BackgroundManager
{
	float m_backSpawnY, m_frontSpawnY, m_mountainSpawnY;
	float m_cameraPan, m_cameraPanMax, m_cameraPanSpd;
	bool m_isCameraTurning;
	float m_camShakeAmount;

	const float c_backSpeedM = 50;
	const float c_frontSpeedM = 100;
	const float c_mountainSpeedM = 10;

	uth::Camera* m_camera;
	uth::Layer* backG;
	uth::Layer* backF;
	pmath::Vec2 m_cameraStartPos;

public:
	BackgroundManager(float bY, float fY, float mY);
	~BackgroundManager();

	bool Init(uth::Object& background, uth::Object& frontground);
	void DeInit();
	void Update(float);
	void CameraMovement(float dt);
	void SetCameraStartPos(pmath::Vec2);
	void Shake(float amount, float delay = 0.1f);
};