#ifndef PARTICLE_TYPE_H
#define PARTICLE_TYPE_H
#include<string>
#include<iostream>

class ParticleType{
    public:
ParticleType(const std::string name, const double mass, const int charge);
 std::string getName() const;
 double getMass() const;
 int getCharge() const;
 virtual const void print();
virtual double getWidth()const ;
private:
const std::string m_name;
const double m_mass;
const int m_charge;
};

#endif