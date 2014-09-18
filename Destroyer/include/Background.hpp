#pragma once
#ifndef Background_HPP
#define Background_HPP

#include <UtH/UtHEngine.hpp>

class Background : public uth::GameObject
{
private:


public:
	Background(uth::Texture* tex);
	~Background();

	void Update(float);
	void Draw();
};

#endif //Background_HPP