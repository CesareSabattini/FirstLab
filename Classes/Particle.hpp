#ifndef PARTICLE_H
#define PARTICLE_H
#include"ResonanceType.hpp"
#include<array>
#include<vector>

class Particle{
public:
Particle(const std::string name, double impulseX=0, double impulseY=0, double impulseZ=0);
int getIndex() const;
void setIndex(int index);
void setIndex(std::string name);
static void printArray();
void print();
std::array<double,3> getImpulse() const;
double getMass() const;
double getEnergy() const;
double getInvariantMass(Particle other) const;
void setImpulse(double impulseX, double impulseY, double impulseZ);
static std::vector<ParticleType*> m_particle_type;
static int findParticle(const std::string name);
static void addParticleType(std::string name, double mass, double charge, double width=0);
static const void addParticleType(ParticleType* particleType);
static int m_nParticleType;
private:
std::array<double,3> m_impulseVector;
 static const int m_maxNumParticleType = 10;
int m_index;

void decay2Body();

};

#endif