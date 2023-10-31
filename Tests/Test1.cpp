#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include "Particle.hpp"
#include<array>

int main() {
    ParticleType particletype("carlone", 100.5 , 2000);
    ResonanceType resonancetype("stefanino", 100.5, 2000, 100);
    Particle particle("carlone", 10,10,20);
 std::array<ParticleType*,2> typeArray{&particletype, &resonancetype};
 for(int i=0; i<=1; i++){
typeArray[i]->print();
 }

    return 0;
}