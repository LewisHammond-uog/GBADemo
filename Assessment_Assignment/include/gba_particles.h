#ifndef __GBA_PARTICLES_H__
#define __GBA_PARTICLES_H__

#include "gba_types.h"

//Defines for gravity of particles and frame time
fixed g_gravity = -0x9CC; //Gravity as -9.8 m/s
fixed g_frameTime = 0x04; 
fixed g_pixels2Meter = 0x500;

//Emitter - Location for where particles will be emitter
typedef struct  Emitter
{
	fixed x , y;
}Emitter;

//Particle
typedef struct Particle{
	fixed x,y; //pos
	fixed vx,vy; //velocity
	u32 life; //lifespan
}Particle;

//Particle Functions
extern void InitParticle(Particle* a_p);
extern void EmitParticle(Particle* a_p, Emitter* a_e);
extern void UpdateParticle(Particle* a_p, Emitter* a_e);

#endif //__GBA_PARTICLES_H__