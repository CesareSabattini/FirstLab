#ifndef PARTICLE_H
#define PARTICLE_H
#include"ResonanceType.hpp"
#include<array>

class Particle{
public:
Particle();
~Particle();
private:
std::array<float,3> m_impulse;
int fIndex;
static std::array<ParticleType*,3> m_particle_type;
static int findParticle(const char* name);
static void addParticleType(char name, float mass, float charge, float width);
void decay2Body();
};

#endif