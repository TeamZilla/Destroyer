#pragma once
#ifndef Tank_HPP
#define Tank_HPP

#include <UtH/UtHEngine.hpp>

class Tank : public uth::GameObject
{
private:
	pmath::Vec2 spawnPos;


public:
	Tank(pmath::Vec2 pos);
	~Tank();

	void Update(float);
	void Draw();

};

#endif //Tank_HPP