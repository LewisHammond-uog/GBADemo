/*
Functionaility Related to particles (creation, emission and update)
*/
#ifndef __GBA_PARTICLES_H__
#define __GBA_PARTICLES_H__

#include "gba_types.h"
#include "gba_math.h"
#include "gba_sprites.h"

//Number of particles per particle system
#define PARTICLE_COUNT 16

//Emitter Struct - Location for where particles will be emitted
typedef struct  Emitter
{
	fixed x , y;
}Emitter;

//Particle Struct
typedef struct Particle{
	fixed x,y; //pos
	fixed vx,vy; //velocity
	u32 frame; //lifespan
}Particle;


//Particle System
typedef struct ParticleSystem{
	Particle particles[PARTICLE_COUNT]; //Actual Particles
}ParticleSystem;

//Initalisation Functions
extern void InitParticle(Particle* a_p);
extern ParticleSystem InitParticleSystem(Emitter* a_partEmitter, SpriteObject a_sprite);

//Emission Functions
extern void EmitParticle(Particle* a_p, Emitter* a_e);
extern void EmitPlayerParticle(Particle* a_p, Emitter* a_e);

//Update Functions
extern void UpdateParticle(Particle* a_p, Emitter* a_e);
extern void UpdateParticleSystem(ParticleSystem* a_ps, Emitter* a_e);

#endif //__GBA_PARTICLES_H__