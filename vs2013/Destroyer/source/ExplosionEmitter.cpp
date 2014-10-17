#include <ExplosionEmitter.hpp>
#include <UtH/Engine/Particles/ParticleSystem.hpp>
#include <UtH/Engine/Particles/ParticleTemplate.hpp>
#include <UtH/Core/Randomizer.hpp>
#include <ExpParAffector.hpp>

using namespace uth;

namespace
{
	ParticleSystem* ps;
}

void ExplosionEmitter::Emit(pmath::Vec2 pos)
{
	if (ps)
	{
		ps->transform.SetPosition(pos);
		ps->Emit(10);
	}
}
void ExplosionEmitter::Init(Layer* m_layer)
{
	if (ps)
		return;

	ParticleTemplate pt;
	pt.SetLifetime(1.f);
	pt.SetSpeed(50.f, 100.f);
	pt.SetTexture(uthRS.LoadTexture("Enemies/Projectiles/explosion.png"));

	ps = new ParticleSystem(200);
	m_layer->AddChild(ps);
	ps->SetTemplate(pt);

	ExpParAffector* expaf = new ExpParAffector();
	expaf->SetParticleInitFunc([](Particle& particle, const ParticleTemplate& pTemplate)
	{
		pmath::Vec2 tvec(Randomizer::InsideCircle());
		tvec /= static_cast<float>(tvec.length());
		particle.direction = Randomizer::GetFloat(pTemplate.minSpeed, pTemplate.maxSpeed) * tvec;
	});

	ps->AddAffector(expaf);
	ps->SetEmitProperties(false);
}
void ExplosionEmitter::DeInit()
{
	ps = nullptr;
}