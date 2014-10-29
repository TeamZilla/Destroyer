#pragma once
#ifndef SMOKEPPARAFFECTOR_H_UTH
#define SMOKEPPARAFFECTOR_H_UTH

#include <UtH/Engine/Particles/Affector.hpp>
#include <UtH/Engine/Particles/Particle.hpp>


namespace uth
{

	class SmokeParAffector : public Affector
	{
	public:

		void UpdateParticle(Particle& particle, const ParticleTemplate& ptemp, float dt) override
		{
			particle.Move(particle.direction * dt);
			particle.Rotate(150 * dt);
			particle.SetScale(particle.GetScale() + pmath::Vec2(dt));
			//ptemp.SetColor(ptemp.color.r, ptemp.color.g, ptemp.color.b, ptemp.color.a);
			particle.color.a -= dt;
		}
			void Update(float dt) override
			{
				GetSystem()->RaiseUpdateFlag();
			}

	};
}

#endif