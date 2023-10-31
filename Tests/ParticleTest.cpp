#include"../Classes/Particle.hpp"

int main(){
ParticleType particleType("K+", 0.493 ,1);
Particle::addParticleType(&particleType);
Particle::addParticleType("K*", 0.892, 0, 0.05);

Particle particle("K+");
Particle resonance("K*", 0.892, 0, 0.05);
particle.print();
std::cout<<std::endl;
resonance.print();

}