#pragma once

#include <UtH/UtHEngine.hpp>

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
	static void Emit(pmath::Vec2 pos, float size);
	static void Init(uth::Object*);
	static void DeInit();
};