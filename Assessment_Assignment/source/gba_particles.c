#include "gba_particles.h"

//Defines for gravity of particles and frame time
fixed g_gravity = -0x2CC; //Gravity as -9.8 m/s
fixed g_frameTime = 0x04; 
fixed g_pixels2Meter = 0x200;

//Maximum distance particle travel from emitter
//before being re-emitted
const int maxPartDist = 40;

//Initalise are particle with 0'ed values
//a_p - Particle to Init
void InitParticle(Particle* a_p){
	a_p->x = 0;
	a_p->y = 0;
	a_p->vx = 0;
	a_p->vy = 0;
}

//Initalise a particle system
//a_partEmitter - Particle Emitter
//a_sprite - Sprite of particle
ParticleSystem InitParticleSystem(Emitter* a_partEmitter, SpriteObject a_sprite){
	
	//Create a particle system and loop through all particles and add them 
	//to OAM
	ParticleSystem ps;
	for(s8 i =0; i < PARTICLE_COUNT; ++i){
		EmitParticle(&ps.particles, a_partEmitter);
		particleOAM[i] = a_sprite;
	}

}

//Update a particle
//a_p - Particle to Update
//a_e - Emitter of particle
void UpdateParticle(Particle* a_p, Emitter* a_e){
	
	//Add velocities to the particle
	a_p->x = fixAdd(a_p->x, fixMul(fixMul(a_p->vx, g_frameTime), g_pixels2Meter));
	a_p->y = fixAdd(a_p->y, fixMul(fixMul(a_p->vy, g_frameTime), g_pixels2Meter));
	a_p->vy -= fixMul(g_gravity, g_frameTime); 

	//Once particle is over 40 px away re emmit it
	if((a_p->y - a_e->y) > Int2Fix(maxPartDist)){
		EmitParticle(a_p, a_e);
	}
}

//Update an entire particle system
//a_ps - Particle System
//a_e - Emitter of particles
extern void UpdateParticleSystem(ParticleSystem* a_ps, Emitter* a_e){

	//Loop through all particles and update
	for(s8 i = 0; i < PARTICLE_COUNT; ++i){

		UpdateParticle(&a_ps->particles[i], a_e);
		//update oam Buffer wioth new particle pos
		SetSpriteScreenPos(&(particleOAM[i]), Fix2Int(a_ps->particles[i].x), Fix2Int(a_ps->particles[i].y));
	}

}

//Emit a Particle from an emtiter
//a_p - Particle
//a_e - Emitter of particle
void EmitParticle(Particle* a_p, Emitter* a_e){
	
	//Set pos to emitter
	a_p->x = a_e->x;
	a_p->y = a_e->y;

	a_p->vx = Int2Fix(GBARandRange(-5, 5)); //xvel
	a_p->vy = Int2Fix(5); //yvel
}