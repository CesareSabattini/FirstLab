#include "ResonanceType.hpp"

ResonanceType::ResonanceType(const std::string name, const double mass,
                             const int charge, const double width)
    : ParticleType(name, mass, charge), m_width{width} {  // const cast???
}

double ResonanceType::getWidth() const { return m_width; }
const void ResonanceType::print() {
  ParticleType::print();
  std::cout << "Width:" << m_width << std::endl;
}