#include"ResonanceType.hpp"

ResonanceType::ResonanceType(const double width,const std::string name, const double mass, const int charge): m_width {width}, ParticleType(name, mass, charge) { //const cast???
}

double ResonanceType::getWidth() const{
return m_width;
}
const void ResonanceType::print(){
ParticleType::print();
std::cout<<"Width"<<m_width<<std::endl;
}