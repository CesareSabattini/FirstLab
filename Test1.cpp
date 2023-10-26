#include "ParticleType.hpp"
#include "ResonanceType.hpp"

int main() {
    ParticleType particletype("carlone", 100.5 , 2000);
    ResonanceType resonancetype("stefanino", 100.5, 2000, 100);
    particletype.print();
    resonancetype.print();

    return 0;
}