#include <FlameEmitter.hpp>
#include <FlameParAffector.hpp>

using namespace uth;

namespace
{
	ParticleSystem* ps;
}

void FlameEmitter::Emit(pmath::Vec2 pos)
{
	if (ps)
	{
		ps->transform.SetPosition(pos);
		ps->Emit(10);
	}
}
//
void FlameEmitter::Emit(pmath::Vec2 pos, float size)
{
	if (ps)
	{
		ps->transform.SetPosition(pos);
		ps->Emit(10);
		ps->transform.SetScale(size);
	}
}
//
void FlameEmitter::Init(Layer* m_layer)
{
	if (ps)
	  return;

	//////SMOKE
	//ParticleTemplate st;
	//st.SetLifetime(3.f);
	//st.SetSpeed(50.f, 50.f);
	//st.SetTexture(uthRS.LoadTexture("Enemies/Projectiles/smoke.png"));

	//ss = new ParticleSystem(200);
	//m_layer->AddChild(ss);
	//ss->SetTemplate(st);

	//SmokeParAffector* smpaf = new SmokeParAffector();
	//smpaf->SetParticleInitFunc([](Particle& particle, const ParticleTemplate& pTemplate)
	//{
	//	pmath::Vec2 tvec(Randomizer::InsideCircle());
	//	tvec /= static_cast<float>(tvec.length());
	//	particle.direction = Randomizer::GetFloat(pTemplate.minSpeed, pTemplate.maxSpeed) * tvec;
	//	particle.SetScale(0.2f);
	//});

	//ss->AddAffector(smpaf);
	//ss->SetEmitProperties(false);

	////FLAME
	ParticleTemplate pt;
	pt.SetLifetime(1.f);
	pt.SetSpeed(40.f, 50.f);
	pt.SetTexture(uthRS.LoadTexture("Enemies/Projectiles/explosion.png"));

	ps = new ParticleSystem(200);
	m_layer->AddChild(ps);
	ps->SetTemplate(pt);

	FlameParAffector* expaf = new FlameParAffector();
	expaf->SetParticleInitFunc([](Particle& particle, const ParticleTemplate& pTemplate)
	{
		pmath::Vec2 tvec(Randomizer::InsideCircle());
		tvec /= static_cast<float>(tvec.length());
		particle.direction = Randomizer::GetFloat(pTemplate.minSpeed, pTemplate.maxSpeed) * tvec;
	});

	ps->AddAffector(expaf);
	ps->SetEmitProperties(false);


}
void FlameEmitter::DeInit()
{
	ps = nullptr;
}