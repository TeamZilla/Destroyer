#pragma once

#include <pmath/Vector2.hpp>

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