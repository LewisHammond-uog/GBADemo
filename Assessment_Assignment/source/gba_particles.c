#include "gba_particles.h"

//Initalises a particle
void InitParticle(Particle* a_p){
	a_p->x = 0;
	a_p->y = 0;
	a_p->vx = 0;
	a_p->vy = 0;
	a_p->life = 0x1FF;
}

//Emits a particle from a given particle emitter
void EmitParticle(Particle* a_p, Emitter* a_e){
	//Set pos to emitter
	a_p->x = a_e->x;
	a_p->y = a_e->y;

	a_p->vx = int2fix(gba_rand_range(-5, 5)); //xvel
	a_p->vy = int2fix(20 + gba_rand_range(0, 5)); //yvel
	a_p->life = 0; //Start at 0 life
}

//Update particles position based on velocity
void UpdateParticle(Particle* a_p, Emitter* a_e){
	a_p->x = fixAdd(a_p->x, fixMul(fixMul(a_p->vx, g_frameTime), g_pixels2Meter));
	a_p->y = fixAdd(a_p->y, fixMul(fixMul(a_p->vy, g_frameTime), g_pixels2Meter));
	a_p->vy -= fixMul(g_gravity, g_frameTime); //Gravity
	a_p->life += 16;

	//Once particle is over 40 px away re emmit it
	if((a_p->y - a_e->y) > int2fix(40)){
		EmitParticle(a_p, a_e);
	}
}