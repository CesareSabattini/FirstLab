#ifndef RESONANCE_TYPE_H
#define RESONANCE_TYPE_H
#include"ParticleType.hpp"

class ResonanceType: protected ParticleType{
public:
ResonanceType(const double width, const std::string name, const double mass, const int charge);
~ResonanceType() override;
double getWidth() const;
const void print() override;
private:
const double m_width;
};

#endif