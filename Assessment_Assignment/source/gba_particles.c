#include "gba_particles.h"

//Defines for gravity of particles and frame time
fixed g_gravity = -0x2CC; //Gravity as -9.8 m/s
fixed g_frameTime = 0x04; 
fixed g_pixels2Meter = 0x200;

//Maximum distance particle travel from emitter
//before being re-emitted
const int maxPartDist = 40;

void InitParticle(Particle* a_p){
	a_p->x = 0;
	a_p->y = 0;
	a_p->vx = 0;
	a_p->vy = 0;
}

ParticleSystem InitParticleSystem(Emitter* a_partEmitter, SpriteObject a_sprite, SpriteObject* a_memLocation){
	
	ParticleSystem ps;
	for(s8 i =0; i < PARTICLE_COUNT; ++i){
		EmitParticle(&ps.particles, a_partEmitter);
		particleOAM[i] = a_sprite;
	}

}

void UpdateParticle(Particle* a_p, Emitter* a_e){
	
	a_p->x = fixAdd(a_p->x, fixMul(fixMul(a_p->vx, g_frameTime), g_pixels2Meter));
	a_p->y = fixAdd(a_p->y, fixMul(fixMul(a_p->vy, g_frameTime), g_pixels2Meter));
	a_p->vy -= fixMul(g_gravity, g_frameTime); 

	//Once particle is over 40 px away re emmit it
	if((a_p->y - a_e->y) > Int2Fix(maxPartDist)){
		EmitParticle(a_p, a_e);
	}
}

extern void UpdateParticleSystem(ParticleSystem* a_ps, Emitter* a_e){

	for(s8 i = 0; i < PARTICLE_COUNT; ++i){

		//update each particle
		UpdateParticle(&a_ps->particles[i], a_e);
		//update oam Buffer wioth new particle pos
		SetSpriteScreenPos(&(particleOAM[i]), Fix2Int(a_ps->particles[i].x), Fix2Int(a_ps->particles[i].y));

		particleOAM[i].attr2 = SetSpriteObjectAttribute2(ParticleSpriteLocation, 0, 1);
	}

}

void EmitParticle(Particle* a_p, Emitter* a_e){
	//Set pos to emitter
	a_p->x = a_e->x;
	a_p->y = a_e->y;

	a_p->vx = Int2Fix(GBARandRange(-5, 5)); //xvel
	a_p->vy = Int2Fix(5); //yvel
}