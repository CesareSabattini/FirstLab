#include "ParticleType.hpp"

ParticleType::ParticleType(const std::string particleName,
                           const double particleMass, const int particleCharge)
    : m_name{particleName}, m_mass{particleMass}, m_charge{particleCharge} {}

std::string ParticleType::getName() const { return m_name; }

double ParticleType::getMass() const { return m_mass; }

int ParticleType::getCharge() const { return m_charge; }
const void ParticleType::print() {
  std::cout << "Name:" << m_name << std::endl;
  std::cout << "Mass:" << m_mass << std::endl;
  std::cout << "Charge:" << m_charge << std::endl;
}

double ParticleType::getWidth() const { return 0; }