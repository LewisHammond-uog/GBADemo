#ifndef __GBA_PARTICLES_H__
#define __GBA_PARTICLES_H__

#include "gba_types.h"
#include "gba_math.h"
#include "gba_sprites.h"

//Emitter Struct - Location for where particles will be emitted
typedef struct  Emitter
{
	fixed x , y;
}Emitter;

//Particle Struct
typedef struct Particle{
	fixed x,y; //pos
	fixed vx,vy; //velocity
	u32 life; //lifespan
}Particle;

#define PARTICLE_COUNT 32

//Particle System
typedef struct ParticleSystem{
	Particle particles[PARTICLE_COUNT]; //Actuall Particles
}ParticleSystem;

//Particle Functions
extern void InitParticle(Particle* a_p);
extern ParticleSystem InitParticleSystem(Emitter* a_partEmitter, SpriteObject a_sprite, SpriteObject* a_memLocation);
extern void EmitParticle(Particle* a_p, Emitter* a_e);
extern void UpdateParticle(Particle* a_p, Emitter* a_e);
extern void UpdateParticleSystem(ParticleSystem* a_ps, Emitter* a_e);

#endif //__GBA_PARTICLES_H__