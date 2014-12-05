#include <ExplosionEmitter.hpp>
#include <ExpParAffector.hpp>
#include <SmokeParAffector.hpp>

using namespace uth;

namespace
{
	ParticleSystem* ps;
	ParticleSystem* ss;
}

void ExplosionEmitter::Emit(pmath::Vec2 pos)
{
	if (ps && ss)
	{
		ps->transform.SetPosition(pos);
		ps->Emit(10);
		ss->transform.SetPosition(pos);
		ss->Emit(10);
	}
}
//
void ExplosionEmitter::Emit(pmath::Vec2 pos, float size)
{
	if (ps && ss)
	{
		ps->transform.SetPosition(pos);
		ps->Emit(10);
		ps->transform.SetScale(size);

		ss->transform.SetPosition(pos);
		ss->transform.SetScale(size);
		ss->Emit(10);


	}
}
//
void ExplosionEmitter::Init(Layer* m_layer)
{
	if (ps && ss)
		return;

	////SMOKE
	ParticleTemplate st;
	st.SetLifetime(3.f);
	st.SetSpeed(50.f, 50.f);
	st.SetTexture(uthRS.LoadTexture("Enemies/Projectiles/smoke.png"));

	ss = new ParticleSystem(200);
	m_layer->AddChild(ss);
	ss->SetTemplate(st);

	SmokeParAffector* smpaf = new SmokeParAffector();
	smpaf->SetParticleInitFunc([](Particle& particle, const ParticleTemplate& pTemplate)
	{
		pmath::Vec2 tvec(Randomizer::InsideCircle());
		tvec /= static_cast<float>(tvec.length());
		particle.direction = Randomizer::GetFloat(pTemplate.minSpeed, pTemplate.maxSpeed) * tvec;
		particle.SetScale(0.2f);
	});

	ss->AddAffector(smpaf);
	ss->SetEmitProperties(false);

	////EXPLOSION
	ParticleTemplate pt;
	pt.SetLifetime(1.f);
	pt.SetSpeed(40.f, 50.f);
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
	ss = nullptr;
}