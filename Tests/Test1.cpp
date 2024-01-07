
#include "../Classes/ParticleType.hpp"
#include "../Classes/ResonanceType.hpp"
#include <array>

int main() {
    ParticleType particleType("K+", 0.493, 1);
    ResonanceType resonanceType("K*", 0.892, 0, 0.05);

    // ParticleType methods tests
    std::cout << "Name:\t" << particleType.getName() << std::endl;
    std::cout << "Mass:\t" << particleType.getMass() << std::endl;
    std::cout << "Charge:\t" << particleType.getCharge() << std::endl
              << std::endl;

    particleType.print();
    std::cout << std::endl;

    // ResonanceType methods tests
    std::cout << "Name:\t" << resonanceType.getName() << std::endl;
    std::cout << "Mass:\t" << resonanceType.getMass() << std::endl;
    std::cout << "Charge:\t" << resonanceType.getCharge() << std::endl;
    std::cout << "Width:\t" << resonanceType.getWidth() << std::endl
              << std::endl;

    resonanceType.print();
}