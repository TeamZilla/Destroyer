#include <FireBreath.hpp>
#include <ExplosionEmitter.hpp>


using namespace uth;

FireBreath::FireBreath(pmath::Vec2 playerPos, pmath::Vec2 targetPos)
{
	m_dirVec = (targetPos - playerPos).normalize();
	m_time = 0;
	m_speed = 100;
	m_sizeModifier = 1;

}

void FireBreath::Init(Layer* m_layer)
{

}

void FireBreath::update(float dt)
{
	ExplosionEmitter::Emit(m_pathFunc(), m_sizeFunc());
	m_time += dt;
}

pmath::Vec2 FireBreath::m_pathFunc()
{
	return m_fromPos + m_time * m_speed * m_dirVec;
}

float FireBreath::m_sizeFunc()
{

	return m_time * m_sizeModifier / m_speed;
}
