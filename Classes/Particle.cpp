#include"Particle.hpp"
#include<cmath>

std::vector<ParticleType*> Particle::m_particle_type;
int Particle::m_nParticleType=0;

Particle::Particle(const std::string name, double impulseX, double impulseY, double impulseZ){
m_index=findParticle(name);
m_nParticleType= m_particle_type.size();


}

int Particle::findParticle(const std::string name){
    for(int i{}; i<=static_cast<int>(m_particle_type.size()); i++){
        if(m_particle_type[i]->getName()==name){
return i;
        }
    }
   
}

int Particle::getIndex() const{
    return m_index;
}

void Particle::addParticleType(std::string name, double mass, double charge, double width){
if(m_nParticleType<m_maxNumParticleType){
    ResonanceType* newType= new  ResonanceType(name, mass, charge, width);
    if(width=0){dynamic_cast<ParticleType*>(newType);}
m_particle_type.push_back(newType);
m_nParticleType=m_particle_type.size();
}
}

const void Particle::addParticleType(ParticleType* particleType){
if(m_nParticleType<m_maxNumParticleType){
m_particle_type.push_back(particleType);
m_nParticleType=m_particle_type.size();
}
};

//unsigned int, const print
void Particle::setIndex(int index){
if(index<=m_nParticleType){
m_index=index;
}
}


void Particle::setIndex(std::string name){
if(findParticle(name)!=-1){
    m_index=findParticle(name);}
}

void Particle::printArray(){
for(int i{}; i<=m_nParticleType; i++){
    std::cout<<"Index:"<<i<<std::endl;
    m_particle_type[i]->print();}
}
std::array<double,3> Particle::getImpulse() const{
    return m_impulseVector;
}

void Particle::print(){
std::cout<<"Index:"<<m_index<<std::endl;
std::cout<<"Name:"<<m_particle_type[m_index]->getName()<<std::endl;
std::cout<<"Impulse: ("<<m_impulseVector[0]<<","<<m_impulseVector[1]<<","<<m_impulseVector[2]<<")"<<std::endl;
}

double Particle::getMass() const{
return m_particle_type[m_index]->getMass();
}


double Particle::getEnergy() const{
double energy{sqrt(pow(m_particle_type[m_index]->getMass(),2)+pow(m_impulseVector[0],2)+pow(m_impulseVector[1],2)+pow(m_impulseVector[2],2))};
return energy;
}

double Particle::getInvariantMass(Particle other) const{
double invariantMass{sqrt(pow(getEnergy()+other.getEnergy(),2)- pow(pow(m_impulseVector[0],2)+pow(m_impulseVector[1],2)+pow(m_impulseVector[2],2)+ pow(other.getImpulse()[0],2)+pow(other.getImpulse()[1],2)+pow(other.getImpulse()[2],2),2) )};
return invariantMass;
}

void Particle::setImpulse(double impulseX, double impulseY, double impulseZ){

m_impulseVector[0]= impulseX;
m_impulseVector[1]= impulseY;
m_impulseVector[2]= impulseZ;

};
