#pragma once

#include <UtH/Engine/Particles/Affector.hpp>
#include <UtH/Engine/Particles/Particle.hpp>


namespace uth
{

	class FlameParAffector : public Affector
	{
	public:

		void UpdateParticle(Particle& particle, const ParticleTemplate& ptemp, float dt) override
		{
			particle.Move(particle.direction * dt);
			particle.Rotate(150 * dt);
			particle.SetScale(particle.GetScale() - pmath::Vec2(dt)/4);
			particle.color.a -= dt;
		}
		void Update(float dt) override
		{
			GetSystem()->RaiseUpdateFlag();
		}

	};
}