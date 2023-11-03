#ifndef RESONANCE_TYPE_H
#define RESONANCE_TYPE_H
#include"ParticleType.hpp"

class ResonanceType: public ParticleType{
public:
ResonanceType( const std::string name, const double mass, const int charge, const double width);
double getWidth() const override ;
const void print() override;
private:
const double m_width;
};

#endif