#pragma once

#include <UtH/UtHEngine.hpp>

namespace uth
{
	class Object;
};

class FlameEmitter
{
private:
	FlameEmitter() = delete;
	~FlameEmitter() = delete;
public:
	static void Emit(pmath::Vec2);
	static void FlameEmitter::Emit(pmath::Vec2 pos, float size);
	static void Init(uth::Object*);
	static void DeInit();
};