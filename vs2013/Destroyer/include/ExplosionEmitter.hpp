#pragma once

#include <pmath/Vector2.hpp>

namespace uth
{
	class Object;
};

class ExplosionEmitter
{
private:
	ExplosionEmitter() = delete;
	~ExplosionEmitter() = delete;
public:
	static void Emit(pmath::Vec2);
	static void Init(uth::Object*);
	static void DeInit();
};