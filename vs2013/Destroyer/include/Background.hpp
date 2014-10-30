#pragma once
#ifndef Background_HPP
#define Background_HPP

#include <UtH/UtHEngine.hpp>

class Background : public uth::Sprite
{
private:

	float m_speed;
	float m_spawnY; 
	float m_shakeMultiplier;
	float m_shakeTimer;
	bool  m_first;

public:
	Background(float speed, float spawnY, float shakeMultiplier, bool first, const std::string& filePath);
	~Background();

	virtual void Init();
	virtual void Update(float);
	void Shake(float time);

};

#endif //Background_HPP